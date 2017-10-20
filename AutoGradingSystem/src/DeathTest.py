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

def ExecTest(student_path):
    origin_path = getcwd();


    chdir(student_path)
    student_result_dir = join(result_dir, basename(student_path))
    xml_path = join(student_result_dir, "DeathReport.xml")
    xml_path = abspath(xml_path)


    subprocess.call('make death 2>' + student_result_dir + '/Make_DeathTest.log;', shell=True)
    subprocess.call('./DeathTest --gtest_output=\"xml:' + xml_path +'"', shell=True)
    print(xml_path)

    if exists(xml_path):
        faillist = GetDeathFailList(xml_path)
        chdir(origin_path)
        return True, faillist
    else:
        chdir(origin_path)
        return False, None


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
