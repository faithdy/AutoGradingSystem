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