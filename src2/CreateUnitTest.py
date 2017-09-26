
from os.path import join, abspath
import re


def MakeUnitTest(student_dir, path, config, faillist):
    student_dir = abspath(student_dir)
    fixture = 'TEST_F(' + config['name'] + ', '
    expection = '\tEXPECT_TRUE('

    with open(join(student_dir,'UnitTest.cc'), 'w') as wf:

        for p in path:
            wf.write('#include \"' + abspath(p) + '\"\n')

        wf.write("#include \"../gtest/gtest.h\"\n\n")
        wf.write("#include \"../helper/isomorphic.h\"\n\n")

        #for l in config['setup']:
        #    wf.write(l + '\n')
        wf.write(config['setup']+'\n')
        for scenario in config['scenarios']:
            if re.sub('[^0-9]', '', scenario.function_name) in faillist:
                continue
            wf.write(fixture + "unit_"+scenario.function_name + ')\n{\n')

            for i in scenario.death_index:
                wf.write(scenario.functions[int(i)]+"\n")
            for i in scenario.function_count:
                if i in scenario.death_index:
                    continue
                wf.write(expection + scenario.functions[int(i)] + ')\n')

            wf.write('}\n\n')
