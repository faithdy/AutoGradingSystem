using namespace std;

class project_1 : public testing::Test{
    protected:
    virtual void SetUp(){
    }

  int test(int a){
    struct sigaction sa;
    set_sigaction(sa);
    alarm(3);

    int b;
    b = a/0;
    return 0;
  }

  int test2(int a)
  {
    struct sigaction sa;
    set_sigaction(sa);
    alarm(3);

    while(1);
    return 0;
  }

};