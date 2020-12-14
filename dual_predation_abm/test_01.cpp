#include <stdio.h>
#include <iostream>
#include <string>


class base
{
public:
    void set_num(int num)
    {
        this->num = num;
    }
    void set_name(std::string name)
    {
        this->name = name;
    }

    int get_num()
    {
        return this->num;
    }
    std::string get_name()
    {
        return this->name;
    }

private:
    int num;
    std::string name;
};

class derived: public base
{
public:
    derived()
    {
        this->resistant = true;
    }

    bool get_resistant()
    {
        return this->resistant;
    }

private:
    bool resistant;
};

class list
{

};

int main()
{
    derived x;
    x.set_num(1);
    x.set_name("Johnson");
    std::cout << "num: " << x.get_num() << std::endl;
    std::cout << "name: " << x.get_name() << std::endl;
    std::cout << "resistant: " << x.get_resistant() << std::endl;
    // derived* x;
    // x->set_num(1);
    // x->set_name("Johnson");
    // std::cout << "num: " << x->get_num() << std::endl;
    // std::cout << "name: " << x->get_name() << std::endl;
    // std::cout << "resistant: " << x->get_resistant() << std::endl;
}
