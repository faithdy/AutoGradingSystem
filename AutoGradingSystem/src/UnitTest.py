#

import subprocess
from os import chdir, path, getcwd

result_dir = '../../result'

from os.path import join, basename, abspath

def UnitTest(student_dir, path, config, faillist):
    MakeUnitTest(student_dir, path, config, faillist)
    UnitFlag = ExecTest(student_dir)
    return UnitFlag

'''
유닛 테스트를 위한 모듈
학생의 클래스를 이용하여 유닛 테스트 코드(구글 테스트) 컴파일 및 빌드
Make 동작 시 stderr를 redirection하여 log(Make_UnitTest.log)로 남긴다.
정상적으로 동작 시 테스트 결과인 UnitReport.xml 파일 생성
UnitReport.xml 생성 시 True, 없을 시 False 반환
'''
def ExecTest(student_path):
    origin_path = getcwd();

    chdir(student_path)
    student_result_dir = path.join(result_dir, basename(student_path))
    xml_path = path.join(student_result_dir, "UnitReport.xml")
    xml_path = abspath(xml_path)


    subprocess.call('make unit 2>' + student_result_dir + '/Make_UnitTest.log;', shell=True)#컴파일 및 빌드
    subprocess.call('./UnitTest --gtest_output=\"xml:' + xml_path+ '"', shell=True)         #Unit Test 실행


    if path.exists(xml_path):
        chdir(origin_path)
        return True
    else:
        chdir(origin_path)
        return False

'''
Unit Test를 위한 테스트 코드(UnitTest.cpp) 생성
Test Fixture를 사용하여 Test suite 생성
Assertion은 EXPECT_TRUE를 사용한 반환 값 비교
Scenario 객체로 부터 Test Case 작성
'''
def MakeUnitTest(student_dir, path, assistant_path, config, faillist):
    student_dir = abspath(student_dir)
    fixture = 'TEST_F('
    expection = '\tEXPECT_TRUE('

    with open(join(student_dir,'UnitTest.cpp'), 'w') as wf:
        for p in path:
            wf.write('#include \"' + abspath(p) + '\"\n')

        for p in assistant_path:
            wf.write('#include \"' + abspath(p) + '\"\n')

        wf.write("#include \"../../../../AutoGradingSystem/src/include/signal.h\"\n")
        wf.write("#include \"../../../../AutoGradingSystem/src/include/oop/isomorphic.h\"\n")
        wf.write("#include \"gtest/gtest.h\"\n\n")

        wf.write(config['unit_setup']+'\n')
        for scenario in config['scenarios']:
            if faillist == None:
                pass

            elif scenario.function_name in faillist:
                continue

            else:
                this_fixture = fixture + scenario.test_fixture + ', '
                wf.write(this_fixture + "unit_"+scenario.function_name + ')\n{\n')

                for i in range(0,len(scenario.functions)):
                    if str(i) in scenario.death_index:
                        wf.write('\t' + scenario.functions[int(i)] + ";\n")
                    else:
                        wf.write(expection + scenario.functions[int(i)] + ');\n')

                wf.write('}\n\n')
