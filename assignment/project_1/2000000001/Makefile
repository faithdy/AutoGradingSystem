GTEST_DIR = ../../../gtest-1.7.0
SIG_DIR = ../../../src
HELPER_DIR = ../helper
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = DeathTest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
all : $(TESTS)
clean :
		rm -f $(TESTS) gtest_main.a *.o 

test.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test.cc
test1.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test1.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test1.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test1.cc
Death_Test.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/DeathTest.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test1.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/DeathTest.cc
Death_Test : test.o test1.o Death_Test.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc $(HELPER_DIR)/isomorphic.h