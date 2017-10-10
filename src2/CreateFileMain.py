
from os.path import join, basename, splitext, isdir, abspath, exists, isfile
from os import getcwd, chdir, mkdir, chmod, rename, remove
from xml.etree.ElementTree import parse
from multiprocessing import Process
import glob
import configparser
import argparse
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
import CreateMakeFile as MT
import chardet
import time

project_name = "project_1"

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


def GetStudentList(path, IDs):
    files = glob.glob(join(path, '*'))
    dirs = [f for f in files if isdir(f)]

    if IDs != None:
        for id in IDs:  # Extract selected student
            dirs = [f for f in dirs if id in f]

    return dirs



def PublicReplace(headers, student_path, isFirst):
    for header in headers:
        #shutil.copy(header, join('./bak', header.replace(".h",".bak")))
        if isFirst == True:
            shutil.copy(header, join(student_path,'bak'))
            f = codecs.open(header, 'r', encoding='utf8')
            read_file = f.read()
            f.close()
            new_file = codecs.open(header,'w', encoding='utf8')
            for line in read_file.split("\n"):
                new_file.write(line.replace('private', 'public')+'\n')
            new_file.close()

def InsertSignal(filepath, student_path, isFirst):

    #filepath =  [f.replace('.h', '.cc') for f in filepath]
    count = 0
    sig = "struct sigaction sa;\nset_sigaction(sa);\nalarm(3);\n"
    header = '#include "../../../AutoGradingSystem/src/signal.h"\n'

    for f in filepath :
        #shutil.copy(f, f.replace(".cc",".cc.bak"))
        if isFirst == True:
            fh = open(f, mode="rb")
            fl   = fh.read()
            fh.close()
            k = chardet.detect(fl)['encoding']
            if  k != 'ascii' :
                rename(f, f+'.cc')
                subprocess.call('iconv -f ' + k + ' -t UTF8 '+f +'.cc > ' +f ,shell=True)
                time.sleep(5)
                remove(f+'.cc')
            shutil.copy(f, join(student_path,'bak'))
            fi = codecs.open(f, 'r', encoding='utf8')
            read_file=fi.read()
            fi.close()
            new_file = codecs.open(f,'w',encoding='utf8')
            new_file.write(header)
            read_file = re.compile("(?s)/\*.*?\*/").sub("", read_file)
            for line in read_file.split("\n"):
                re.sub(r'\s+', ' ',line)
                code = re.compile("//.*").sub("", line)
                mc = re.findall(r"\b(\w+)::(\w+)\([^{]+",code,re.S)
                if mc :
                    pc = re.findall(r"\b(\w+)::(\w+)\([^{]+(\)\)|[;])", code, re.S)
                    if pc :
                        new_file.write(code + '\n')
                    else :
                        nc = re.findall(r"\b(\w+)::(\w+)\([^{]+\{( \w+|\w+|	\w+)",code,re.S)
                        if  not nc:
                            new_file.write(code)
                            count = 1
                        else :
                            num = code.find("{")
                            new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
                            #code = code.replace(nc[2],"")
                            #new_file.write(code+'\n'+sig+nc[2]+'\n')
                else:
                    if count == 0 :
                        new_file.write(code+'\n')
                    else:
                        count = 0
                        oc = re.findall(r'\{( \w+|\w+|	\w+)', code, re.S)
                        if not oc:
                            if (code.find("{") == -1):
                                new_file.write("\n" + sig + "\n" + code + '\n')
                            else:
                                if bool(re.match(r"( \w+|\w+|	\w+)", code)):
                                    new_file.write("\n" + sig + "\n" + code + '\n')
                                else:
                                    new_file.write("\n" + code + "\n" + sig)
                        else:
                            num = code.find("{")
                            new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')

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

def RemoveCR(filepaths):
    for f in filepaths:
        subprocess.call('sed -i -e \'s/\r$//\' '+f, shell=True)

def main_process(student_path, config):
    isFirst = False

    bak = join(student_path,'bak')

    if not exists(bak):
        print("Make %s directory......" %bak)
        mkdir(bak)
        chmod(bak, 0o777)
        isFirst = True

    filepaths, classes = CDT.GetClass(student_path)

    if filepaths == False:
        return




    cppfilepaths = [f.replace('.h','.cpp') for f in filepaths]

    MT.CreateMakeFile(student_path, filepaths, classes)

    PublicReplace(filepaths, student_path, isFirst)
    InsertSignal(cppfilepaths, student_path, isFirst)
    RemoveCR(cppfilepaths)

    chdir(student_path)
    subprocess.call('make', shell=True)
    chdir('../../../AutoGradingSystem/src2')

    if isfile(student_path+'/RUN') :
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

    origin_wd = getcwd()
    procs = []

    for i in range(len(student_list)):
        procs.append(Process(target=main_process, args=(student_list[i], config)));

    for p in procs:
        print('excute process')
        print(p)
        p.start()


'''
for student_path in student_list:
    chdir(origin_wd)
    filepaths, classes = CDT.GetClass(student_path)
    cppfilepaths = [f.replace('.h','.cpp') for f in filepaths]
    PublicReplace(filepaths)
    #Signal.findClass(cppfilepaths)


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
'''



