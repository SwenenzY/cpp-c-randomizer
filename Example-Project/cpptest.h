#pragma once
#include "stdafx.h"

void TestVoid1(int TestInt1, std::string TestString1);

namespace TestNamespace {
	bool TestNamespaceVoid1(bool TestBool1);
}

class TestClass {
public:
	static float MyClassVoid1(float MyFlaot1 = 3.f);
	static void  MyClassVoid2(float MyFloat2);
	static void  MyClassVoid3();
private:
	static void MyclassVoid4();
};