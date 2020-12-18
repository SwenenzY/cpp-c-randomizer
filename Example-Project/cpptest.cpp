#include "cpptest.h"

float MyClassFloat1 = 1333.f;

void TestVoid1(int TestInt1, std::string TestString1) {
	std::cout << "TestInt1 : " << TestInt1 << "\n\n";
	std::cout << "TestString1 : " << TestString1 << "\n\n";
}

bool TestNamespace::TestNamespaceVoid1(bool TestBool1)
{
	return TestBool1;
}

float TestClass::MyClassVoid1(float MyFlaot1)
{
	if (MyFlaot1 == 3.f)
		return MyFlaot1;
	return 0.0f;
}

void TestClass::MyClassVoid2(float MyFloat2)
{
	MyClassFloat1 = MyFloat2;
}

void TestClass::MyClassVoid3()
{
	TestClass::MyclassVoid4();
}

void TestClass::MyclassVoid4()
{
	 
	std::cout << MyClassFloat1 << "\n\n";
}
