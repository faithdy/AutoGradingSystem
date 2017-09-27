
from os.path import join, basename, splitext, isdir, abspath
from os import getcwd, chdir
from xml.etree.ElementTree import parse
import glob
import configparser
import re
import sys
import subprocess
import codecs
import shutil
import Scenario
import CreateDeathTest as CDT
import CreateDeathMakeFile as CDMF
import CreateUnitMakeFile as CUMF
import CreateUnitTest as CUT

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
            new_file.write(line.replace('private', 'public')+'\n')
        new_file.close()

def InsertSignal(filepath):

    filepath =  [f.replace('.h', '.cc') for f in filepath]
    count = 0
    sig = "struct sigaction sa;\nset_sigaction(sa);\nalarm(3);\n"
    for f in filepath :
        shutil.copy(f, f.replace(".cc",".cc.bak"))
        fi = codecs.open(f, 'r', encoding='utf8')
        read_file=fi.read()
        fi.close()
        new_file = codecs.open(f,'w',encoding='utf16')
        for line in read_file.split("\n"):
            re.sub(r'\s+', ' ',line)
            mc = re.findall(r"\b(\w+)::(\w+)\([^{]+",line,re.S)
            if mc :
                nc = re.findall(r"\b(\w+)::(\w+)\([^{]+\{( \w+|\w+)",line,re.S)
                if  not nc:
                    new_file.write(line)
                    count = 1
                else :
                    line = line.replace(nc[2],"")
                    new_file.write(line+'\n'+sig+nc[2]+'\n')
            else:
                if count == 0 :
                    new_file.write(line+'\n')
                else :
                    count = 0
                    oc = re.findall(r'\{( \w+|\w+)',line,re.S)
                    if not oc :
                        new_file.write(line+"\n"+sig)
                    else :
                        line = line.replace(oc[0], "")
                        new_file.write(line+"\n" + sig + oc[0] + '\n')

        new_file.close()


def GetDeathFailList(student_path, xml):
    student_path = abspath('../' + student_path)
    tree = parse(join(student_path,xml))
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


student_list = GetStudentList(student_dir)

config = GetConfig(config_path)

origin_wd = getcwd()
for student_path in student_list:
    chdir(origin_wd)
    filepaths, classes = CDT.GetClass(student_path)
    PublicReplace(filepaths)
    #InsertSignal(filepaths)


    if filepaths == False:
        continue

    CDT.MakeDeathTest(student_path, filepaths, config)

    CDMF.CreateMakeFile(student_path, filepaths, classes)

    chdir(student_path)
    subprocess.call('make', shell=True)
    subprocess.call('./DeathTest --gtest_output=\"xml:./DeathReport.xml\"', shell=True)
    try:
        fail_scenario = GetDeathFailList(student_path, 'DeathReport.xml')
        CUT.MakeUnitTest(student_path, filepaths, config, fail_scenario)
    except:
        print("No DeathReport\n")

    CUMF.CreateMakeFile(student_path, filepaths, classes)
    subprocess.call('make', shell=True)
    subprocess.call('./UnitTest --gtest_output=\"xml:./UnitReport.xml\"', shell=True)




