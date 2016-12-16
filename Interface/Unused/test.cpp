#include <iostream>
#include <memory>
using namespace std;

class Abstract
{
    public:
        virtual void show() = 0;
};

class Imp: public Abstract
{
    public:
        void show()
        {
            cout << "Hi!" << endl;
        };
};

unique_ptr<Abstract> &&func()
{
    return move(unique_ptr<Abstract>(new Imp));
}

int main()
{
    unique_ptr<Abstract> p = func();
    p -> show();
}
