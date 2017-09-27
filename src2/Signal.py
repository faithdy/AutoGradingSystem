import re, shutil, codecs

def findClass(filepath):
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
