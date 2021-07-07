#include <iostream>

typedef unsigned int DWORD;

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

DWORD* GetVfptr(Base* anyChild)
{
    DWORD* _vfptr = *((DWORD**)(anyChild));
    return _vfptr;
}

Base* CreateCustomBaseClass(DWORD* methods) 
{
    Base* cop = (Base*)(&methods);

    return cop;
}


int main()
{
    DWORD* virtualMethods = GetVfptr(new Child());

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

    DWORD* methods = new DWORD[1];
    methods[0] = (DWORD)&PrintName;

    Base* customBase = CreateCustomBaseClass(methods);
    customBase->PrintName();

    return 0;
}
