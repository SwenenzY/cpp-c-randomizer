#pragma once
#include "stdafx.h"

void O_O TestVoid1 o_o (int TestInt1, std::string TestString1);

namespace TestNamespace {
	bool O_O TestNamespaceVoid1 o_o (bool TestBool1);
}

class O_O TestClass o_o {
public:
	static float O_O MyClassVoid1 o_o (float MyFlaot1 = 3.f);
	static void  O_O MyClassVoid2 o_o (float MyFloat2);
	static void  O_O MyClassVoid3 o_o ();
private:
	static void O_O MyclassVoid4 o_o ();
};
