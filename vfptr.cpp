#include <iostream>

typedef unsigned long QWORD;

class Base 
{
public:
    virtual void PrintName()
    {
        std::cout << "Base" << std::endl;
    }
    virtual void PrintMessage(const char* message)
    {
        std::cout << message << std::endl;
    }
};

struct Child : Base
{
public:
    void PrintName()
    {
        std::cout << "Child" << std::endl;
    }
};

void PrintName()
{
    std::cout << "Funny" << std::endl;
}

QWORD* GetVfptr(Base* anyChild)
{
    QWORD* _vfptr = *((QWORD**)(anyChild));
    return _vfptr;
}

Base* CreateCustomBaseClass(QWORD* methods) 
{
    Base* copy = (Base*)(&methods);

    return copy;
}


int main()
{
    QWORD* virtualMethods = GetVfptr(new Child());

    auto printName = (void(*)())(virtualMethods[0]);
    auto printMessage = (void(*)(const char* msg))(virtualMethods[1]);

    printName();

    const char* message = "MessageExample";
    //printMessage(message); noob way 8)
    __asm 
    {
        mov eax, dword ptr[message]
        push eax
        mov eax, dword ptr[printMessage]
        call eax
    }

    QWORD* methods = new QWORD[1];
    methods[0] = (QWORD)&PrintName;

    Base* customBase = CreateCustomBaseClass(methods);
    customBase->PrintName();

    return 0;
}
