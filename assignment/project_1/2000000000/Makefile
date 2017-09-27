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

List_2D.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_2D.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_2D.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_2D.cc
Management.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Management.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Management.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Management.cc
Region.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Region.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Region.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Region.cc
List_Circular.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_Circular.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_Circular.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_Circular.cc
Employment.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Employment.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Employment.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Employment.cc
BST.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/BST.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/BST.cc
Death_Test.o : /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/DeathTest.cc /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_2D.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Management.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Region.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/List_Circular.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/Employment.h /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c /home/youngjae/AutoGradingSystem/assignment/project_1/2000000000/DeathTest.cc
Death_Test : List_2D.o Management.o Region.o List_Circular.o Employment.o BST.o Death_Test.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc $(HELPER_DIR)/isomorphic.h