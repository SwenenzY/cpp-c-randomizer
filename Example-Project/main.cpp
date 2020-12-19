#include "stdafx.h"

// CPP
#include "cpptest.h"
int main()
{

    TestVoid1(1, "Hi"); // print 1,2

    std::cout << std::string(TestNamespace::TestNamespaceVoid1(false) ? "true" : "false") << "\n\n"; // test bool element

    std::cout << TestClass::MyClassVoid1(3.f) << "\n\n"; // test class element

    TestClass::MyClassVoid2(1.057f); // test class element private

    TestClass::MyClassVoid3(); // print private element

    getchar(); //
}
