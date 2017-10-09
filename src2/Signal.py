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
                pc = re.findall(r"\b(\w+)::(\w+)\([^{]+;", code, re.S)
                if pc:
                    new_file.write(code + '\n')
                else :
                    nc = re.findall(r"\b(\w+)::(\w+)\([^{]+\{( \w+|\w+)",code,re.S)
                    if  not nc:
                        new_file.write(code)
                        count = 1
                    else :
                        num = code.find("{")
                        new_file.write(code[:num+1] + '\n' + sig + code[num + 1:] + '\n')
            else:
                if count == 0 :
                    new_file.write(code+'\n')
                else :
                    count = 0
                    oc = re.findall(r'\{( \w+|\w+)',code,re.S)
                    if not oc :
                        new_file.write(code+"\n"+sig)
                    else :
                        code = code.replace(oc[0], "")
                        new_file.write(code+"\n" + sig + oc[0] + '\n')

        new_file.close()

findClass(["./Management.cpp"])