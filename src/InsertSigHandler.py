#####################################################################################
# To work the Death Test as well, this file inserts some codes about signal-handler #
# in source codes(.cc) that student posted up to work the Death TEST as well        #
#####################################################################################


# import some libraries
import os
import sys
import Function
import fileinput

Ass_name = sys.argv[1]
Student = sys.argv[2]

print("Insert signal handler....\n")

# load the list for death-test, and then set it in obj
infoName = "/usr/local/Auto_Scoring_System/info/"+sys.argv[1]+"/"+sys.argv[1]+"_info.txt"
obj = []
Function.getList(infoName,obj)
Function.redundancy(obj)
# call 'insertSring'. this function replaces(inserts) top to sig-handler sentence.
for objNum in range(0,len(obj)):
	Function.insertString(obj[objNum],sys.argv[1],sys.argv[2])

Function.insertStringv2(sys.argv[1],sys.argv[2])
