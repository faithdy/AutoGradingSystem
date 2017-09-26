
from os.path import join, basename, splitext, abspath
import glob

def GetClass(path):
    allFiles = glob.glob(join(path, "**/*.h"), recursive=True)

    files = [f for f in allFiles]
    try:
        basenames = [splitext(basename(f))[0] for f in files]  # File name
    except IndexError:
        return False, False

    return files, basenames

def MakeDeathTest(student_dir, path, config):
    student_dir = abspath(student_dir)
    fixture = 'TEST_F(' + config['name'] + ', '
    assertion = '\tASSERT_DEATH('
    expectation = ', \"segmentation fault\");\n'

    with open(join(student_dir,'DeathTest.cc'), 'w') as wf:

        for p in path:
            wf.write('#include \"' + abspath(p) + '\"\n')

        wf.write("#include \"../../../src/signal.h\"\n")
        wf.write("#include \"../../../hepler/isomorphic.h\"\n")
        wf.write("#include \"gtest/gtest.h\"\n\n")

        #for l in config['setup']:
        #    wf.write(l + '\n')
        wf.write(config['setup']+'\n')

        for scenario in config['scenarios']:
            wf.write(fixture + scenario.function_name + ')\n{\n')

            for i in scenario.death_index:
                wf.write(assertion + scenario.functions[int(i)] + expectation)

            wf.write('}\n\n')

