#

import subprocess
from os import chdir, path, getcwd

result_dir = '../../result'

from os.path import join, basename, abspath

def UnitTest(student_dir, path, config, faillist):
    MakeUnitTest(student_dir, path, config, faillist)
    UnitFlag = ExecTest(student_dir)
    return UnitFlag

def ExecTest(student_path):
    origin_path = getcwd();

    chdir(student_path)
    student_result_dir = path.join(result_dir, basename(student_path))
    xml_path = path.join(student_result_dir, "UnitReport.xml")
    xml_path = abspath(xml_path)


    subprocess.call('make unit>>' + student_result_dir + '/Make_UnitTest.log;', shell=True)
    subprocess.call('./UnitTest --gtest_output=\"xml:' + xml_path+ '"', shell=True)


    if path.exists(xml_path):
        chdir(origin_path)
        return True
    else:
        chdir(origin_path)
        return False


def MakeUnitTest(student_dir, path, config, faillist):
    student_dir = abspath(student_dir)
    fixture = 'TEST_F('
    expection = '\tEXPECT_TRUE('


    with open(join(student_dir,'UnitTest.cpp'), 'w') as wf:
        for p in path:
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
