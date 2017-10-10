
from os.path import join, basename, splitext, abspath
import glob

def GetClass(path):
    #allFiles = glob.glob(join(path, "**/*.h"), recursive=True)
    allFiles = glob.glob(join(path, '*.h'))

    files = [f for f in allFiles]
    try:
        basenames = [splitext(basename(f))[0] for f in files]  # File name
    except IndexError:
        return False, False

    return files, basenames

def MakeDeathTest(student_dir, path, config):
    student_dir = abspath(student_dir)
    fixture = 'TEST_F('
    assertion = '\tASSERT_DEATH('
    expectation = ', \"-\");\n'

    with open(join(student_dir,'DeathTest.cpp'), 'w') as wf:

        for p in path:
            wf.write('#include \"' + abspath(p) + '\"\n')


        wf.write("#include \"../../../AutoGradingSystem/src/signal.h\"\n")
        wf.write("#include \"../../../AutoGradingSystem/helper/isomorphic.h\"\n")
        wf.write("#include \"gtest/gtest.h\"\n\n")

        #for l in config['setup']:
        #    wf.write(l + '\n')
        wf.write(config['setup']+'\n')

        for scenario in config['scenarios']:
            this_fixture = fixture + scenario.test_fixture + ', '
            wf.write(this_fixture + scenario.function_name + ')\n{\n::testing::FLAGS_gtest_death_test_style = "threadsafe";\nfprintf(stderr, "FILE LOCATION: %s\n", __FILE__);\n')

            for i in scenario.death_index:
                wf.write(assertion + scenario.functions[int(i)] + expectation)
				wf.write(scenario.function[int(i)] + ';\n')

            wf.write('}\n\n')
