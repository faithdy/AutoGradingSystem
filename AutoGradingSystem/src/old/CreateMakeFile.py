from os.path import join, abspath




EXEC = 'EXEC = run\n'
CC = 'CC= g++\n'
all = '\nRUN : $(OBJECTS)\n'
clean = 'clean :\n\t\trm -f $(OBJECTS) *.o \n\n'
flag = 'FLAG = -std=c++11 -g \n'
sig_dir = 'SIG_DIR = ../../../AutoGradingSystem/src\n'

def CreateMakeFile(student_dir, path, classes):

    print("Make Student Makefile......\n")

    student_dir = abspath(student_dir)
    path = [abspath(p) for p in path]


    wf = open(join(student_dir, 'Makefile'), 'w')


    wf.write(EXEC)
    wf.write(CC)
    wf.write(flag)
    wf.write(sig_dir)

    wf.write('OBJECTS = ')
    wf.write('main.o ')
    for Class in classes:
        wf.write(Class + '.o ')

    wf.write(all)
    wf.write('\t$(CC) $(FALGS)  -o ' + "RUN"  + ' $^ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc  \n')
    wf.write('main.o :' + student_dir + '/main.cpp \n')
    wf.write('\t$(CC) $(FALGS)  -c '+student_dir+'/main.cpp \n')
    for i in range(0, len(classes)):
        cc = path[i].replace('.h','.cpp')
        wf.write(classes[i] + '.o : ' + cc + ' ' + path[i] + '\n')
        wf.write('\t$(CC) $(FALGS)  -c ' + cc + '\n')

    wf.write(clean)
    wf.close()

if __name__ == "__main__":
    CreateMakeFile();

