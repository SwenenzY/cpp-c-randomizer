#include "stdafx.h"

#define O_O
#define o_o

// CPP
#include "cpptest.h"
int main()
{
    std::string O_O Test o_o = "MyValue";
    std::cout << "MyValue :: " << Test << "\n\n";

    TestVoid1(1, "Hi"); // print 1,2

    std::cout << std::string(TestNamespace::TestNamespaceVoid1(false) ? "true" : "false") << "\n\n"; // test bool element

    std::cout << TestClass::MyClassVoid1(3.f) << "\n\n"; // test class element

    TestClass::MyClassVoid2(1.057f); // test class element private

    TestClass::MyClassVoid3(); // print private element



    getchar(); //
}