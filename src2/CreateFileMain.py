
from os.path import join, basename, splitext, isdir, abspath
from os import getcwd
import glob
import configparser
import sys
import Scenario
import CreateDeathTest as CDT
import CreateDeathMakeFile as CDMF

#project_name = sys.argv[1]
project_name = 'project_1'

pwd = getcwd()

student_dir = join(r'../assignment',project_name)
info_dir = join(r'../info', project_name)
config_path = join(info_dir, project_name + '.conf')


def GetConfig(path):
    cfg = configparser.ConfigParser()
    cfg.read(path)

    name = cfg.get('Project', 'name')
    setup = cfg.get('Project', 'setup')
    scenario_count = cfg.get('Project', 'scenario_count')

    scenarios = []

    for i in range(int(scenario_count)):
        scen = Scenario.Scenario('scenario_' + str(i))
        scen.SetScenario(cfg)
        scenarios.append(scen)

    with open(join(info_dir,setup), 'r') as setup:
        setup_file = setup.read()

    config = {
        'name' : name,
        'setup' : setup_file,
        'scenario_count' : scenario_count,
        'scenarios' : scenarios
    }

    return config


def GetStudentList(path):
    files = glob.glob(join(path,'*'))
    dirs = [f for f in files if isdir(f)]

    return dirs


def GetStudentClass(path):
    headers = glob.glob(join(path, "**/*.h"), recursive=True)
    basenames = [splitext(basename(header))[0] for header in headers]  # File name

    return headers, basenames

student_list = GetStudentList(student_dir)

config = GetConfig(config_path)

for student_path in student_list:
    filepaths, classes = CDT.GetClass(student_path)

    if filepaths == False:
        continue

    CDT.MakeDeathTest(student_path, filepaths, config)

    CDMF.CreateMakeFile(student_path, filepaths, classes)

    #bash commnad(make)
    #bash(gcc deathtest.)
    #bash(./deathtest -- xml)

    #faillist = parsing(xml)

    #makeunittest(faillist)