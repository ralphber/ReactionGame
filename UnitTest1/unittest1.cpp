#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Blink1/Player.h"
 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RreactionGameTest
{		
	TEST_CLASS(PlayerTests)
	{
	public:
		
		TEST_METHOD(TestConstruction)
		{
			Player p1{ "Tester" };
			Assert::AreEqual("Tester", p1.get_name().c_str());
		}

	};
}