#include <iostream>
#include <functional>

typedef std::function<void ()> Fn;

class Father
{
    protected:
        int msg;
        
    public:
        Father(int m): msg(m) {}
        
        virtual void f()
        {
            std::cout << "Hello" << std::endl;
            std::cout << msg << std::endl;
        }
        Fn get()
        {
            return std::bind(&Father::f, this);
        }
};

class Son: public Father
{
    public:
        Son(int m): Father(m) {}
        
        void f()
        {
            std::cout << "Hi" << std::endl;
            std::cout << msg << std::endl;
        }
};

int main()
{
    Father f(1);
    f.get()();
    Father *s = new Son(2);
    s -> get()();
    delete s;
}
