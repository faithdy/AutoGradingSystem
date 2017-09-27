#include "/home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test.h"
#include "/home/youngjae/AutoGradingSystem/assignment/project_1/2000000001/test1.h"
#include "../../../src/signal.h"
#include "../../../helper/isomorphic.h"
#include "gtest/gtest.h"

using namespace std;

class project_1 : public testing::Test{
    protected:
    virtual void SetUp(){
    }


    int test(int num){
        num / 0;
        return 0;
    }
};
TEST_F(project_1, scenario_0)
{
	ASSERT_DEATH(test(1), "segmentation fault");
}

TEST_F(project_1, scenario_1)
{
	ASSERT_DEATH(test(1), "segmentation fault");
}

