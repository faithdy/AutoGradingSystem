#


from os.path import join, abspath

gtest_dir = 'GTEST_DIR = ../../../AutoGradingSystem/gtest-1.7.0\n'
sig_dir = 'SIG_DIR = ../../../AutoGradingSystem/src\n'
helper_dir = 'HELPER_DIR = ../../../AutoGradingSystem/helper\n'
cpp_flags = 'CPPFLAGS += -isystem $(GTEST_DIR)/include\n'
cxx_flags = 'CXXFLAGS += -g -Wall -Wextra -pthread\n'
test = 'TESTS = UnitTest\n'
gtest_header = 'GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \\\n\t\t$(GTEST_DIR)/include/gtest/internal/*.h\n'
all = 'all : $(TESTS)\n'
clean = 'clean :\n\t\trm -f $(TESTS) gtest_main.a *.o \n\n'



def CreateMakeFile(student_dir, path, classes):


    print("Make Unit test Makefile......\n")

    student_dir = abspath('../' + student_dir)
    path = [abspath('../' + p) for p in path]



    # Make Death test C++ file
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

    for i in range(0, len(classes)):
        cc = path[i].replace('.h','.cpp')
        wf.write(classes[i] + '.o : ' + cc + ' ' + path[i] + ' $(GTEST_HEADERS)\n')
        wf.write('\t$(CXX) $(CPPFALGS) $(CXXFLAGS) -c ' + cc + '\n')

    wf.write('UnitTest.o : ' + join(student_dir, 'UnitTest.cpp') + ' ')

    for p in path:
        wf.write(p + ' ')

    wf.write('$(GTEST_HEADERS)\n\t')
    wf.write('$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ' + join(student_dir, 'UnitTest.cpp') + '\n')


    wf.write('UnitTest : ')
    for Class in classes:
        wf.write(Class + '.o ')
    wf.write(
        "UnitTest.o ../../../AutoGradingSystem/gtest-1.7.0/gtest_main.a\n"
        "\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc $(HELPER_DIR)/isomorphic.h\n")

    wf.close()

