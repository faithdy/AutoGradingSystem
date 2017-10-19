from os import getcwd, chdir, mkdir, chmod, rename, remove
from os.path import join, isdir, exists, splitext, basename
import sys

from multiprocessing import Process
import glob
import configparser
import argparse

import src.MakeFile as mf
import src.RunTest as rt
import src.DeathTest as dt
import src.UnitTest as ut
import src.Compatibility as compat
import src.Scenario
from src.Scenario import Scenario

#project_name = "project_1"
project_name = sys.argv[1]

JsonCompatibility = True
JsonRunTest = True
JsonDeathTest = True
JsonUnitTest = True

student_dir = join(r'../public', project_name + '/data')
student_result_dir = join(r'../public', project_name + '/result')
info_dir = join(r'../public', project_name + '/info')
config_path = join(info_dir, project_name + '.conf')

def GetClass(path):
    #allFiles = glob.glob(join(path, "**/*.h"), recursive=True)
    allFiles = glob.glob(join(path, '*.h'))

    files = [f for f in allFiles]
    try:
        basenames = [splitext(basename(f))[0] for f in files]  # File name
    except IndexError:
        return False, False

    return files, basenames


def GetConfig(path):
    cfg = configparser.ConfigParser()
    cfg.read(path)

    name = cfg.get('Project', 'name')
    death_setup = cfg.get('Project', 'death_setup')
    unit_setup = cfg.get('Project', 'unit_setup')
    scenario_count = cfg.get('Project', 'scenario_count')

    scenarios = []

    for i in range(int(scenario_count)):
        scen = Scenario('scenario_' + str(i))
        scen.SetScenario(cfg)
        scenarios.append(scen)

    with open(join(info_dir,death_setup), 'r') as setup:
        death_setup_file = setup.read()

    with open(join(info_dir,unit_setup), 'r') as setup:
        unit_setup_file = setup.read()


    config = {
        'name' : name,
        'death_setup' : death_setup_file,
        'unit_setup': unit_setup_file,
        'scenario_count' : scenario_count,
        'scenarios' : scenarios
    }

    return config


def GetStudentList(path, IDs):
    files = glob.glob(join(path, '*'))
    dirs = [f for f in files if isdir(f)]

    if IDs != None:
        for id in IDs:  # Extract selected student
            dirs = [f for f in dirs if id in f]

    return dirs



def main_process(student_path, config):
    isFirst = False

    bak = join(student_path,'bak')

    if not exists(bak) :
        print("Make %s directory......" %bak)
        mkdir(bak)
        result = join(student_path, '../../result/'+basename(student_path))
        if not exists(result) :
            mkdir(result)
        chmod(bak, 0o777)
        isFirst = True

    filepaths, classes = GetClass(student_path)

    if filepaths == False:
        return

    mf.CreateMakeFile(student_path, filepaths, classes)

    # Compatibility Test
    if JsonCompatibility == True:
        compat.MatchCompatibility(filepaths, student_path, isFirst)
    # CompileTest
    if JsonRunTest == True:
        isNextStep = rt.RunTest(student_path)
        if isNextStep == False:
            return False;

    if JsonDeathTest == True:
        isNextStep, fail_scenario = dt.DeathTest(student_path, filepaths, config)
        if isNextStep == False:
            return False

    if JsonUnitTest == True:
        isNextStep = ut.UnitTest(student_path, filepaths, config, fail_scenario)


if __name__ == "__main__":
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

    student_list = GetStudentList(student_dir, selected_student)

    config = GetConfig(config_path)

    procs = []

    for i in range(len(student_list)):
        procs.append(Process(target=main_process, args=(student_list[i], config)));

    for p in procs:
        print('excute process')
        print(p)
        p.start()