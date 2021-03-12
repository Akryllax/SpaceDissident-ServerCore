#include "test_library.h"
#include <iostream>

using namespace std;

TestLibrary::TestLibrary(void)
{
}

TestLibrary::~TestLibrary(void)
{
}

void TestLibrary::hello()
{
    cout << "Hello World of DLL" << endl;
}

void TestLibrary::helloStatic()
{
    cout << "Hello World of DLL static" << endl;
}