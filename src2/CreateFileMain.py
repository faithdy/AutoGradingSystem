
from os.path import join, basename, splitext, isdir, abspath
from os import getcwd, chdir
from xml.etree.ElementTree import parse
import glob
import configparser
import sys
import subprocess
import codecs
import shutil
import Scenario
import CreateDeathTest as CDT
import CreateDeathMakeFile as CDMF

#project_name = sys.argv[1]
project_name = 'project_1'

pwd = getcwd()

student_dir = join(r'../../assignment',project_name)
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

def PublicReplace(headers):
    for header in headers:
        shutil.copy(header, header.replace(".h",".bak"))
        f = codecs.open(header, 'r', encoding='utf8')
        read_file = f.read()
        f.close()
        new_file = codecs.open(header,'w', encoding='utf8')
        for line in read_file.split("\n"):
            new_file.write(line.replace('private', 'public'))
        new_file.close()

def GetDeathFailList(student_dir,xml):
    student_dir = abspath(student_dir)
    tree = parse(student_dir,xml)
    root = tree.getroot()
    arr = []

    for test in root.iter("testcase") :
        if test.find("failure") is None :
            arr.append(test.attrib["name"])

    return arr


student_list = GetStudentList(student_dir)

config = GetConfig(config_path)

origin_wd = getcwd()
for student_path in student_list:
    chdir(origin_wd)
    filepaths, classes = CDT.GetClass(student_path)
    PublicReplace(filepaths)


    if filepaths == False:
        continue

    CDT.MakeDeathTest(student_path, filepaths, config)

    CDMF.CreateMakeFile(student_path, filepaths, classes)

    print(student_path)


    chdir(student_path)
    subprocess.call('make', shell=True)
    subprocess.call('./DeathTest --gtest_output=\"xml:./DeathReport.xml\"', shell=True)
    fail_scenario = GetDeathFailList(student_dir, './DeathReport.xml')


    #faillist = parsing(xml)

    #makeunittest(faillist)