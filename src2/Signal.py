import re, shutil, codecs

def findClass(filepath):
    count = 0

    sig = "struct sigaction sa;\nset_sigaction(sa);\nalarm(3);\n"
    for f in filepath :
        shutil.copy(f, f.replace(".cpp",".cpp.bak"))
        fi = codecs.open(f, 'r', encoding='utf8')
        read_file=fi.read()
        fi.close()
        new_file = codecs.open(f,'w',encoding='utf8')
        for line in read_file.split("\n"):
            re.sub(r'\s+', ' ',line)
            code = re.compile("//.*").sub("", line)
            mc = re.findall(r"\b(\w+)::(\w+)\([^{]+",code,re.S)
            if mc :
                pc = re.findall(r"\b(\w+)::(\w+)\([^{]+(\)\)|[;])", code, re.S)
                if pc:
                    new_file.write(code + '\n')
                else :
                    qc = re.findall(r"\b(\w+)::(\w+)\([^{]+(\)|\{)", code, re.S)
                    if not qc:
                        new_file.write(code + '\n')
                        count = 2
                    else :
                        nc = re.findall(r"\b(\w+)::(\w+)\([^{]+\{( \w+|\w+|	\w+)",code,re.S)
                        if  not nc:
                            k = len(code)
                            j = code.find("}")+1
                            if k>=j and j != 0:
                                num = code.find("{")
                                new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
                            else :
                                new_file.write(code)
                                count = 1
                        else :
                            num = code.find("{")
                            new_file.write(code[:num+1] + '\n' + sig + code[num + 1:] + '\n')
            else:
                if count == 0 :
                    new_file.write(code+'\n')
                elif count == 1 :
                    count = 0
                    oc = re.findall(r'\{( \w+|\w+|	\w+)',code,re.S)
                    if not oc :
                        if code.find("{") == -1 :
                            new_file.write("\n"+sig+"\n"+code+ '\n')
                        else:
                            if bool(re.match(r"( \w+|\w+|	\w+)",code)) :
                                new_file.write("\n" + sig + "\n" + code + '\n')
                            else :
                                new_file.write("\n" + code + "\n" + sig)
                    else :
                        num = code.find("{")
                        new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')
                else :
                    count = 1
                    oc = re.findall(r'\{( \w+|\w+|	\w+)', code, re.S)
                    if not oc:
                        if (len(code) >= code.find("{") + 1) and (code.find("{") != -1)  :
                            count = 0
                            num = code.find("{")
                            new_file.write(code[:num + 1] + '\n' + sig + '\n')
                        else :
                            new_file.write(code + '\n')
                    else:
                        count = 0
                        num = code.find("{")
                        new_file.write(code[:num + 1] + '\n' + sig + code[num + 1:] + '\n')



        new_file.close()

findClass(["./List_Circular.cpp"])