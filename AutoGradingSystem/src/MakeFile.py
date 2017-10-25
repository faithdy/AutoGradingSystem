from os.path import join, abspath

gtest_dir = 'GTEST_DIR = ../../../../AutoGradingSystem/src/gtest-1.7.0\n'
sig_dir = 'SIG_DIR = ../../../../AutoGradingSystem/src/include\n'
helper_dir = 'HELPER_DIR = ../../../../AutoGradingSystem/src/include/oop\n'
cpp_flags = 'CPPFLAGS += -isystem $(GTEST_DIR)/include\n'
cxx_flags = 'CXXFLAGS += -g -Wall -Wextra -pthread\n'
test = 'COMPILE = CompileTest\nDEATH = DeathTest\nUNIT = UnitTest\n'
gtest_header = 'GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \\\n\t\t$(GTEST_DIR)/include/gtest/internal/*.h\n'
all = 'compile : $(COMPILE)\ndeath : $(DEATH)\nunit : $(UNIT)\n'
clean = 'clean :\n\t\trm -f $(COMPILE) gtest_main.a *.o\n\t\trm -f $(DEATH) gtest_main.a *.o\n\t\trm -f $(UNIT) gtest_main.a *.o \n\n'


'''
Makefile을 만들기 위한 모듈
각 학생 폴더에 접근하여 빌드테스트, 데스테스트, 유닛테스트를 위한
하나의 MakeFile을 생성한다.
'''


# MakeFile 생성성
def CreateMakeFile(student_dir, path, classes):


    print("Make Makefile......\n")

    student_dir = abspath(student_dir)
    path = [abspath(p) for p in path]



    # 빋드 테스트, 데스테스트, 유닛테스트를 위한 MakeFile 생
    wf = open(join(student_dir, 'Makefile'), 'w')

    wf.write(gtest_dir)
    wf.write(sig_dir)
    wf.write(helper_dir)
    wf.write(cpp_flags)
    wf.write(cxx_flags)
    wf.write(test)
    wf.write(gtest_header)
    wf.write(all)
    wf.write(clean)
    wf.write('main.o :' + student_dir + '/main.cpp \n')
    wf.write('\t$(CXX) $(CPPFALGS) $(CXXFLAGS) -w -c ' + student_dir + '/main.cpp\n')

    for i in range(0, len(classes)):
        cc = path[i].replace('.h','.cpp')
        wf.write(classes[i] + '.o : ' + cc + ' ' + path[i] + ' $(GTEST_HEADERS)\n')
        wf.write('\t$(CXX) $(CPPFALGS) $(CXXFLAGS) -w -c ' + cc + '\n')

    wf.write('DeathTest.o : ' + join(student_dir, 'DeathTest.cpp') + ' ')

    for p in path:
        wf.write(p + ' ')

    wf.write('$(GTEST_HEADERS)\n\t')
    wf.write('$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -c ' + join(student_dir, 'DeathTest.cpp') + '\n')

    wf.write('UnitTest.o : ' + join(student_dir, 'UnitTest.cpp') + ' ')

    for p in path:
        wf.write(p + ' ')

    wf.write('$(GTEST_HEADERS)\n\t')
    wf.write('$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -c ' + join(student_dir, 'UnitTest.cpp') + '\n')


    wf.write('CompileTest : ')
    for Class in classes:
        wf.write(Class + '.o ')
    wf.write(
        "main.o\n"
        "\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -w -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc\n")

    wf.write('DeathTest : ')
    for Class in classes:
        wf.write(Class + '.o ')
    wf.write(
        "DeathTest.o ../../../../AutoGradingSystem/src/gtest-1.7.0/gtest_main.a\n"
        "\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -w -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc $(HELPER_DIR)/isomorphic.h\n")

    wf.write('UnitTest : ')
    for Class in classes:
        wf.write(Class + '.o ')
    wf.write(
        "UnitTest.o ../../../../AutoGradingSystem/src/gtest-1.7.0/gtest_main.a\n"
        "\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -w -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc $(HELPER_DIR)/isomorphic.h\n")

    wf.close()
