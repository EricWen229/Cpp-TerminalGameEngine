#include <string>
#include <iostream>

#define cast_down(from, to) \
    if ((from).getClassName() == "Father") \
        auto to = dynamic_cast<Father&>(from); \
    else if ((from).getClassName() == "Son") \
        auto to = dynamic_cast<Son&>(from);


class Father
{
    public:
        virtual std::string &&getClassName()
        {
            return std::move(std::string("Father"));
        }
        void say()
        {
            std::cout << "I'm father!" << std::endl;
        }
};

class Son: public Father
{
    public:
        virtual std::string &&getClassName()
        {
            return std::move(std::string("Son"));
        }
        void say()
        {
            std::cout << "I'm son!" << std::endl;
        }
};

int main()
{
    Father *f = new Son;
    cast_down(*f, s);
    (*f).say();
    /* s.say(); */
}
