
from os.path import join, abspath
import re


def MakeUnitTest(student_dir, path, config, faillist):
    student_dir = abspath('../' + student_dir)
    fixture = 'TEST_F('
    expection = '\tEXPECT_TRUE('


    with open(join(student_dir,'UnitTest.cpp'), 'w') as wf:
        for p in path:
            wf.write('#include \"' + abspath('../' + p) + '\"\n')

        wf.write("#include \"../../../AutoGradingSystem/src/signal.h\"\n")
        wf.write("#include \"../../../AutoGradingSystem/helper/isomorphic.h\"\n")
        wf.write("#include \"gtest/gtest.h\"\n\n")

        #for l in config['setup']:
        #    wf.write(l + '\n')
        wf.write(config['setup']+'\n')
        for scenario in config['scenarios']:
            if faillist == None:
                pass

            elif scenario.function_name in faillist:
                continue

            else:
                this_fixture = fixture + scenario.test_fixture + ', '
                wf.write(this_fixture + "unit_"+scenario.function_name + ')\n{\nfprintf(stderr,"FILE LOCATION: %s\n", __FILE__);\n')

                for i in range(0,len(scenario.functions)):
                    if str(i) in scenario.death_index:
                        wf.write('\t' + scenario.functions[int(i)] + ";\n")
                    else:
                        wf.write(expection + scenario.functions[int(i)] + ');\n')

                wf.write('}\n\n')
