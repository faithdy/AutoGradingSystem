import shutil, codecs
import subprocess
from os import rename, remove, path
import chardet
import re
import time
from os.path import join

def MatchCompatibility(filepaths, student_path, isFirst):
    if isFirst == True:
        ChangeEncoding(filepaths, student_path)
        BreakEncapsulation(filepaths, student_path)

        cppfilepaths = [f.replace('.h', '.cpp') for f in filepaths]
        InsertSignal(cppfilepaths)
        RemoveCR(cppfilepaths)
        RemoveBOMB(cppfilepaths)

def ChangeEncoding(filepaths, student_path):
    cppfilepaths = [f.replace('.h', '.cpp') for f in filepaths]

    for cppfile in cppfilepaths:
        with open(cppfile, mode="rb") as cp:
            file = cp.read()

        encoding = chardet.detect(file)['encoding']

        shutil.copy(cppfile, join(student_path,'bak'))
        if not 'ascii' in encoding and not 'utf-8' in encoding  :
            subprocess.call('iconv -f ' + encoding + ' -t utf-8 ' + cppfile + ' --output ' + cppfile, shell=True)
       

    for header in filepaths:
        with open(header, mode="rb") as hd:
            file = hd.read()

        encoding = chardet.detect(file)['encoding']

        shutil.copy(header, join(student_path,'bak'))
        if not 'ascii' in encoding and not 'utf-8' in encoding  :
            subprocess.call('iconv -f ' + encoding + ' -t utf-8 ' + header + ' --output ' + header, shell=True)

def RemoveCR(cppfilepaths):
    for cppfile in cppfilepaths:
        subprocess.call('sed -i -e \'s/\r$//\' ' + cppfile, shell=True)

def RemoveBOMB(cppfilepaths):
    for cppfile in cppfilepaths:
        subprocess.call("perl -C -pi -e \'s/\\x{feff}//g\' " + cppfile, shell=True)

def BreakEncapsulation(filepath, student_path):
    for header in filepath:
        shutil.copy(header, join(student_path, 'bak'))
        f = codecs.open(header, 'r', encoding='utf8')
        read_file = f.read()
        f.close()

        new_file = codecs.open(header, 'w', encoding='utf8')

        for line in read_file.split("\n"):
            new_file.write(line.replace('private', 'public') + '\n')
        new_file.close()

def InsertSignal(filepath):

    count = 0
    sig = "struct sigaction sa;\nset_sigaction(sa);\nalarm(3);\n"
    header = '#include '+'"../../../../AutoGradingSystem/src/include/signal.h"'

    for f in filepath :
        fi = codecs.open(f, 'r', encoding='utf8')
        read_file=fi.read()
        change_file = read_file.replace('nullptr','NULL')
        fi.close()
        new_file = codecs.open(f,'w',encoding='utf8')
        new_file.write(header+'\n')
        read_file = re.compile("(?s)/\*.*?\*/").sub("", read_file)
        for line in change_file.split("\n"):
            re.sub(r'\s+', ' ', line)
            code = re.compile("//.*").sub("", line)
            a = re.findall(r"str(\w+)_s",code,re.S) 
            if re.findall(r"str(\w+)_s",code,re.S) :
                for i in range(len(a)) :
                    code = code.replace(a[i]+"_s",a[i])
                    if a[i] == 'tok' :
                        check = re.findall(r",.*,(.*)\)",code,re.S)
                        if check :
                            if len(check[0]) == check[0].find(')')+1 :
                                code = code.replace(","+check[0].replace(')',''),"")
                            else :
                                code = code.replace(","+check[0],"")
                    else:
                        check = re.findall(r",.*\,",code,re.S)
                        if check :
                            code = code.replace(check[0],",")
            mc = re.findall(r"\b(\w+)::(\w+)\([^{]+", code, re.S)
            if mc:
                pc = re.findall(r"\b(\w+)::(\w+)\([^{]+(\)\)|[;])", code, re.S)
                if pc:
                    new_file.write(code + '\n')
                else:
                    qc = re.findall(r"\b(\w+)::(\w+)\([^{]+(\)|\{)", code, re.S)
                    if not qc:
                        new_file.write(code + '\n')
                        count = 2
                    else:
                        nc = re.findall(r"\b(\w+)::(\w+)\([^{]+\{( \w+|\w+|	\w+)", code, re.S)
                        if not nc:
                            k = len(code)
                            j = code.find("}") + 1
                            if k >= j and j!=0:
                                num = code.find("{")
                                new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
                            else:
                                new_file.write(code)
                                count = 1
                        else:
                            num = code.find("{")
                            new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
            else:
                if count == 0:
                    new_file.write(code + '\n')
                elif count == 1:
                    count = 0
                    oc = re.findall(r'\{( \w+|\w+|	\w+)', code, re.S)
                    if not oc:
                        if code.find("{") == -1:
                            new_file.write("\n" + sig + "\n" + code + '\n')
                        else:
                            if bool(re.match(r"( \w+|\w+|	\w+)", code)):
                                new_file.write("\n" + sig + "\n" + code + '\n')
                            else:
                                new_file.write("\n" + code + "\n" + sig)
                    else:
                        num = code.find("{")
                        new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
                else:
                    count = 1
                    oc = re.findall(r'\{( \w+|\w+|	\w+)', code, re.S)
                    if not oc:
                        if (len(code) >= code.find("{") + 1) and (code.find("{") != -1) :
                            count = 0
                            num = code.find("{")
                            new_file.write(code[:num + 1] + '\n' + sig + '\n')
                        else:
                            new_file.write(code + '\n')
                    else:
                        count = 0
                        num = code.find("{")
                        new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')

        new_file.close()
       
