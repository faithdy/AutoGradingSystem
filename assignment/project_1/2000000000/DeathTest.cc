#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/List_2D.h"
#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/Management.h"
#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/Region.h"
#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/List_Circular.h"
#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/Employment.h"
#include "/home/youngjae/Desktop/ASS/assignment/project_1/2000000000/BST.h"
#include "../../../src/signal.h"
#include "../../../hepler/isomorphic.h"
#include "gtest/gtest.h"

using namespace std;

class project_1 : public testing::Test{
    protected:
    virtual void SetUp(){
    }

    char* To_Traversal(Manager m)
    {
        return 'abc';
    }

    template <T>
    T* deserialize(string filename){

        T* result = new T;

        result = open(filename ,'rb');

        return result
    }

}
TEST_F(project_1, scenario_0)
{
	ASSERT_DEATH(M1->run("test.txt"), "segmentation fault");
}

TEST_F(project_1, scenario_1)
{
	ASSERT_DEATH(M1->run("test.txt"), "segmentation fault");
	ASSERT_DEATH(To_Traversal(M1, NULL), "segmentation fault");
}

