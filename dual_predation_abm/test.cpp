#include <stdio.h>
#include<iostream>
#include<string>


class myClass
{
public:
    myClass()
    {

    }
};


int main()
{
    myClass* newNode = new myClass;
    free(newNode);
    free(newNode);

}
