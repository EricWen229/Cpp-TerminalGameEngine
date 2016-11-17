#include<iostream>
#include<cstring>
#include "Reflection.h"
using namespace std;

class A : public Object
{
        DECLARE_CLASS(A)
    public :
        A()
        {
            cout<<hex<<(long)this<<" A constructor!"<<endl;
        }
        ~A()
        {
            cout<<hex<<(long)this<<" A destructor!"<<endl;
        }
};
IMPLEMENT_CLASS(A)

class B : public Object
{
        DECLARE_CLASS(B)
    public :
        B()
        {
            cout<<hex<<(long)this<<" B constructor!"<<endl;
        }
        ~B()
        {
            cout<<hex<<(long)this<<" B destructor!"<<endl;
        }
};
IMPLEMENT_CLASS(B)

int main()
{
    Object *p = Object::CreateObject("A");
    delete p;
    return 0;
}
