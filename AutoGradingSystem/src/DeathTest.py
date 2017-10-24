#

import subprocess
import re
from os import chdir, getcwd
from os.path import join, exists, abspath
from xml.etree.ElementTree import parse

result_dir = '../../result'

from os.path import join, basename, abspath

def DeathTest(student_dir, path, config):
    MakeDeathTest(student_dir, path, config)
    DeathFlag = ExecTest(student_dir)
    return DeathFlag

'''
데스 테스트를 위한 모듈
학생의 클래스를 이용하여 데스 테스트 코드(구글 테스트) 컴파일 및 빌드
Make 동작 시 stderr를 redirection하여 log(Make_DeathTest.log)로 남긴다.
정상적으로 동작 시 테스트 결과인 DeathReport.xml 파일 생성
DeathReport.xml 생성 시 True, 없을 시 False 반환
'''
def ExecTest(student_path):
    origin_path = getcwd();


    chdir(student_path)
    student_result_dir = join(result_dir, basename(student_path))
    xml_path = join(student_result_dir, "DeathReport.xml")
    xml_path = abspath(xml_path)


    subprocess.call('make death 2>' + student_result_dir + '/Make_DeathTest.log;', shell=True)
    subprocess.call('./DeathTest --gtest_output=\"xml:' + xml_path +'"', shell=True)

    if exists(xml_path):
        faillist = GetDeathFailList(xml_path)
        chdir(origin_path)
        return True, faillist
    else:
        chdir(origin_path)
        return False, None

'''
데스 테스트를 위한 테스트 코드(DeathTest.cpp) 생성
Test Fixture를 사용하여 Test suite 생성
Assertion은 EXPECT_DEATH를 사용하여 새로운 프로세스를 fork
생성된 독립적인 프로세스에서 signal 비교를 통해 try/catch로 잡을 수 없는 에러를 확인
signal handler는 signal.h에 정의
Scenario 객체로 부터 테스트 케이즈 작성
'''
def MakeDeathTest(student_dir, path, config):

    student_dir = abspath(student_dir)
    fixture = 'TEST_F('
    assertion = '\tEXPECT_DEATH(alarm(1);'
    expectation = ', \"-\");\n'

    with open(join(student_dir,'DeathTest.cpp'), 'w') as wf:

        for p in path:
            wf.write('#include \"' + abspath(p) + '\"\n')


        wf.write("#include \"../../../../AutoGradingSystem/src/include/signal.h\"\n")
        wf.write("#include \"../../../../AutoGradingSystem/src/include/oop/isomorphic.h\"\n")
        wf.write("#include \"gtest/gtest.h\"\n\n")

        wf.write(config['death_setup']+'\n')

        for scenario in config['scenarios']:
            this_fixture = fixture + scenario.test_fixture + ', '
            wf.write(this_fixture + scenario.function_name + ')\n{\n::testing::FLAGS_gtest_death_test_style = "threadsafe";\n')
            wf.write(assertion)
            for i in scenario.death_index:
                wf.write(scenario.functions[int(i)]+';')

            wf.write(expectation)
            wf.write('}\n\n')

'''
데스 테스트에서 치명적 에러를 발생시킨 케이스는 유닛 테스트의 종료를 유발
데스 테스트 결과인 DeathReport.xml 에서 정상 적인 성공은
failed to die를 출력함. 따라서 failed to die인 테스트 케이스만
유닛 테스트에게 통보
'''
def GetDeathFailList(xml_path):
    tree = parse(abspath(xml_path))
    root = tree.getroot()
    arr = []

    for test in root.iter("testcase") :
        if test.find("failure") is None :
            arr.append(test.attrib["name"])
        else :
            for fail in test.iter("failure") :
                if bool(re.search('failed to die',fail.attrib["message"])) is False :
                    arr.append(test.attrib["name"])
    return arr
