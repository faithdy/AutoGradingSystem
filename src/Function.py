def getList(fileName, obj):
	with open(fileName) as f:
		_lines = f.readlines()
		_lines = list(map(lambda s: s.strip("\n"), _lines))

		i=0
		for i in range(i,len(_lines)):
			if 'Function' in _lines[i]:
				i = i + 1
				break
		for j in range(i,len(_lines)):
			temp = _lines[j].translate(None, "[]").split('},{')
			if len(temp) == 1:
				continue
			elif temp[2] == "X":
				Fname = temp[0].translate(None,"{")
				Class = temp[7].translate(None,"}")
				obj.append({'Fname' : Fname, 'Class' : Class})

def redundancy(obj):
	# this function does redundancy to avoid duplicatation
	i=0
	while(i<len(obj)-1):
		j=i+1
		cnt=0
		while(j<len(obj)):
			if(obj[i]==obj[j]):
				obj.pop(j)
				continue
			else:
			 	j=j+1
		i=i+1

def insertString(obj,Ass_name,Student):
	# set string about signal handler and Class, Fname in the obj
	declareVar	 = "struct sigaction sa;"
	setSigAction	 = "set_sigaction(sa);"
	setAlarm	 = "alarm(3);"
	Class = obj['Class']
	Fname = obj['Fname']

# set the target string and the name of the file to open/write string
	# and then, set the include string
	target = Class+"::"+Fname
	openFileString = "/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class+".cc"
	writeFileString = "/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class+".cc"

	# concatenate string
	string = "{" +"\n\t" + declareVar + "\n\t" + setSigAction + "\n\t" + setAlarm + "\n"
	# first of all, we open the file 'openFileString' with read-only.
	# next, read all the lines, and then we assign them to lines.
	# last of all, close the file.
	rf = open(openFileString, "r")
	lines = rf.readlines()
	rf.close()

	# for the loop, set the control variable i and flag as both '0'.
	i = 0
	flag = 0

	# first of all, we open the file 'writeFileString' with write-only.
	# next, do the *routine* with some loop statements
	# last of all, close the file.
	wf = open(writeFileString, "w")

	#sentence including signal file
	includeString = "#include \"/usr/local/Auto_Scoring_System/src/signal.h\""
	# it starts the routine that replaces '{' from 'string' in 'lines', if need.
	for line in lines:
		if "signal.h" in line:
			print(includeString+" is already registered")
		else:
			wf.write(includeString+"\n")
		break

	for line in lines:	
		if target in line:
			j=i
			while(1):
				# remove the space character
				buf = lines[j]
				buf.replace(" ","")

				# case by '{' in comment '//'
				if buf[0]=='/' and buf[1]=='/':
					wf.write(lines[j])
					j=j+1
					flag +=1
				# case by '{' in comment '/*'
				elif buf[0]=='/' and buf[1]=='*':
					wf.write(lines[j])
					j=j+1
					flag +=1

				# case by replacing the line
				elif '{' in lines[j]:
					wf.write(lines[j].replace('{', string))
					break

				# case by no replacing the line
				else:
					wf.write(lines[j])
					j=j+1
					flag +=1
		else:
	     		# to avoid duplicating the same string, continue as flag count.
			if flag>0:
				flag-=1
			else:
				wf.write(line)
		i=i+1

	wf.close()

def insertStringv2(Ass_name,Student):
	Class = "Manager"
	Fname = "~Manager"

# set the target string and the name of the file to open/write string
	# and then, set the include string
	target = Class+"::"+Fname
	openFileString = "/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class+".cc"
	writeFileString = "/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class+".cc"

	# concatenate string
	string_2 = "{ return;\n" #JUST ASSIGNMENT 1 FOR DESTRUCTION
	# first of all, we open the file 'openFileString' with read-only.
	# next, read all the lines, and then we assign them to lines.
	# last of all, close the file.
	rf = open(openFileString, "r")
	lines = rf.readlines()
	rf.close()

	# for the loop, set the control variable i and flag as both '0'.
	i = 0
	flag = 0

	# first of all, we open the file 'writeFileString' with write-only.
	# next, do the *routine* with some loop statements
	# last of all, close the file.
	wf = open(writeFileString, "w")

	#sentence including signal file
	includeString = "#include \"/usr/local/Auto_Scoring_System/src/signal.h\""
	# it starts the routine that replaces '{' from 'string' in 'lines', if need.
	for line in lines:
		if "signal.h" in line:
			print(includeString+" is already registered")
		else:
			wf.write(includeString+"\n")
		break

	for line in lines:	
		if target in line:
			j=i
			while(1):
				# remove the space character
				buf = lines[j]
				buf.replace(" ","")

				# case by '{' in comment '//'
				if buf[0]=='/' and buf[1]=='/':
					wf.write(lines[j])
					j=j+1
					flag +=1
				# case by '{' in comment '/*'
				elif buf[0]=='/' and buf[1]=='*':
					wf.write(lines[j])
					j=j+1
					flag +=1

				# case by replacing the line
				elif '{' in lines[j]:
					wf.write(lines[j].replace('{', string_2))
					break

				# case by no replacing the line
				else:
					wf.write(lines[j])
					j=j+1
					flag +=1
		else:
	     		# to avoid duplicating the same string, continue as flag count.
			if flag>0:
				flag-=1
			else:
				wf.write(line)
		i=i+1

	wf.close()

