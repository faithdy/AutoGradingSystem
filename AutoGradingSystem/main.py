from os import getcwd, chdir, mkdir, chmod, rename, remove
from os.path import join, isdir, exists, splitext, basename
import sys

from multiprocessing import Process
from collections import OrderedDict
import glob
import configparser
import argparse
import json

import src.MakeFile as mf
import src.RunTest as rt
import src.DeathTest as dt
import src.UnitTest as ut
import src.Compatibility as compat
from src.Scenario import Scenario

#과제 이름
project_name = sys.argv[1]


'''
채점 모듈 옵션 파일 불러오기(프로젝트 이름.json)

사용자는 웹(과제 등록 - 모듈)에서 모듈을 선택할 수 있습니다.
호환성 검사 : OS 또는 인코딩 호환을 일관되게 맞추어 줍니다.
빌드 테스트 : 학생의 main 실행 파일이 생성되는지 확인합니다.
객체 기반 테스트 : OOT 테스팅을 실행합니다.
데스 테스트 : 데스 테스트를 통해 학습자의 치명적 에러를 방지하고 확인합니다.
유닛 테스트 : 반환 값, 표준 출력을 결과와 비교합니다. 
'''
with open(join('../public/' + project_name + '/info/', project_name + '.json')) as data_file:
    process_steps = json.load(data_file)

JsonCompatibility = process_steps['compatibility']
JsonRunTest = process_steps['compile']
JsonDeathTest = death = process_steps['death']
JsonUnitTest = process_steps['unit']
JsonOopTest = process_steps['oop']

'''
순서fh
해당 과제의 학습자 제출 디렉터리
학습자의 채점 결과 및 로그 디렉터리
해당 과제의 SetUp 디렉터리 (설정 파일, 테스 SetUp() 코드...)
해당 과제의 설정(configure) 파일
'''
student_dir = join(r'../public', project_name + '/data')
student_result_dir = join(r'../public', project_name + '/result')
info_dir = join(r'../public', project_name + '/info')
config_path = join(info_dir, project_name + '.conf')


'''
인자로 들어온 학생 디렉터리의 header 파일의 경로와 basename을 반환
'''
def GetClass(path):
    allFiles = glob.glob(join(path, '*.h'))

    files = [f for f in allFiles]
    try:
        basenames = [splitext(basename(f))[0] for f in files]  # File name
    except IndexError:
        return False, False

    return files, basenames


'''
해당 과제의 configure 파일로부터
과제의 이름, 테스의 SetUp() 코드 경로, 테스트 시나리오를 불러옴
'''
def GetConfig(path):
    cfg = configparser.ConfigParser()
    cfg.read(path)

    name = cfg.get('Project', 'name')
    death_setup = cfg.get('Project', 'death_setup')
    unit_setup = cfg.get('Project', 'unit_setup')
    scenario_count = cfg.get('Project', 'scenario_count') #테스트할 시나리오 갯수

    scenarios = []

    #각 테스트 시나리오는 Scenario 객체로 관리
    for i in range(int(scenario_count)):
        scen = Scenario('scenario_' + str(i))
        scen.SetScenario(cfg)
        scenarios.append(scen)

    #데스 테스트와 유닛 테스트의 파일 열
    with open(join(info_dir,death_setup), 'r') as setup:
        death_setup_file = setup.read()

    with open(join(info_dir,unit_setup), 'r') as setup:
        unit_setup_file = setup.read()


    #최종 설정들은 딕셔너리로 관리
    config = {
        'name' : name,
        'death_setup' : death_setup_file,
        'unit_setup': unit_setup_file,
        'scenario_count' : scenario_count,
        'scenarios' : scenarios
    }

    return config


'''
해당 과제를 제출한 모든 학습자의 디렉터리 경로를 얻
이때 웹에서 특정 학생을 선택한다면
--student IDs
의 인자로 받아 특정 학생의 디렉터리만 반환
'''
def GetStudentList(path, IDs):
    files = glob.glob(join(path, '*'))
    dirs = [f for f in files if isdir(f)]

    if IDs != None:
        for id in IDs:  # Extract selected student
            dirs = [f for f in dirs if id in f]

    return dirs


'''
실제 학생별로 동작되는 프로세스
학생 과제 디렉터리와 설정을 인자로 받는다.
이 단계에서 학생코드의 호환성을 위해 변형하기 전
원본을 보존하기 위해 bak 디렉터리 생성 후 저장
학생 결과가 저장될 result/학생 디렉터리 생성

각 단계의 실패란, 테스트 실행파일 또는 결과 파일이 생성되지 않았음을 의미.
'''
def main_process(student_path, config, assistant_filepaths, assistant_classes):
    isFirst = False
    compile_err_json = OrderedDict()

    bak = join(student_path,'bak')
    result = join(student_path, '../../result/' + basename(student_path))

    #처음 실행될 경우에만 bak, result 폴더 생성
    if not exists(bak) :
        print("Make %s directory......" %bak)
        mkdir(bak)
        if not exists(result) :
            mkdir(result)
        chmod(bak, 0o777)
        isFirst = True

    #학생의 Header 파일 경로 및 Header의 basename(class)를 불러옴
    filepaths, classes = GetClass(student_path)

    #파일이 없는 경후 프로세스를 종료한다.
    if filepaths == False:
        return

    #학생의 컴파일 및 빌드를 위한 Makefile을 생성한다.
    #빌드 테스트, 데스 테스트, 유닛 테스트를 위한 통합 Makefile 생성
    mf.CreateMakeFile(student_path, filepaths, classes, assistant_filepaths, assistant_classes)

    # 호환성 검사(처음만 실행)
    # 인코딩 변환, 개행(Carriage Return), Bomb 제거
    if JsonCompatibility == True:
        compat.MatchCompatibility(filepaths, student_path, isFirst)

    # 빌드 테스트
    # 빌드 테스트 실패시 빌드 테스트 단계에서 실패함을 log 파일에 명시
    if JsonRunTest == True:
        isNextStep = rt.RunTest(student_path)
        if isNextStep == False:
            compile_err_json["err"] = "compile"
            with open(join(result, 'err_compile.json'), 'w', encoding='utf-8') as err_json:
                json.dump(compile_err_json, err_json, ensure_ascii=False, indent='\t')
            return False;

    # 데스 테스트
    # 데스 테스트 실패시 데 테스트 단계에서 실패함을 log 파일에 명시
    if JsonDeathTest == True:
        isNextStep, fail_scenario = dt.DeathTest(student_path, filepaths, config)
        if isNextStep == False:
            compile_err_json["err"] = "death"
            with open(join(result, 'err_death.json'), 'w', encoding='utf-8') as err_json:
                json.dump(compile_err_json, err_json, ensure_ascii=False, indent='\t')
            return False

    # 유닛 테스트
    # 유닛 테스트 실패시 유닛 테스트 단계에서 실패함을 log 파일에 명시
    if JsonUnitTest == True:
        isNextStep = ut.UnitTest(student_path, filepaths, config, fail_scenario)
        if isNextStep == False:
            compile_err_json["err"] = "unit"
            with open(join(result, 'err_unit.json'), 'w', encoding='utf-8') as err_json:
                json.dump(compile_err_json, err_json, ensure_ascii=False, indent='\t')


'''
main 함수
학생 전체 또는 특정 학생에 대해 
에러에 독립적이기 위해 multiprocessing 통해
병렬적으로 프로세스를 실행
'''
if __name__ == "__main__":

    #특정 학생을 입력받기 위해
    #argparser를 사용하여 입력
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--student',
        type=str,

        default=None,
        nargs='+',
        help='Select specific students'
    )
    FLAGS, unparsed = parser.parse_known_args()
    selected_student = FLAGS.student

    #해당 과제를 제출한 학생들의 리스트를 불러
    student_list = GetStudentList(student_dir, selected_student)

    # 조교의 Header 파일 경로 및 Header의 basename(class)를 불러옴
    assistant_filepaths, assistant_classes = GetClass(info_dir)

    mf.AssistantCreateMakeFile(info_dir, assistant_filepaths, assistant_classes)

    #해당 과제의 설정을 딕셔너리 형태로 불러온다
    config = GetConfig(config_path)

    procs = []

    #학생 별로 독립적인 프로세스에서 main_process를 실행시켜 채점
    for i in range(len(student_list)):
        procs.append(Process(target=main_process, args=(student_list[i], config, assistant_filepaths, assistant_classes)));

    for p in procs:
        print('excute process')
        print(p)
        p.start()
