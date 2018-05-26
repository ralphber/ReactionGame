#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Blink1/Player.h"
#include <string>
#include <chrono>
 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReactionGameTest
{		
	TEST_CLASS(PlayerTests)
	{
	public:
		
		TEST_METHOD(TestConstructionName)
		{
			Player p1{ "Tester" };
			Assert::AreEqual("Tester", p1.get_name().c_str());
		}

		TEST_METHOD(TestConstructionWins)
		{
			Player p1{ "Tester" };
			Assert::AreEqual(0, p1.read_wins());
		}

		TEST_METHOD(TestConstructionDelta)
		{
			Player p1{ "Tester" };
			auto flag = 0;
			std::chrono::system_clock::duration const zero = std::chrono::system_clock::duration::zero();

			if (p1.get_delta() == zero)
			{
				flag = 1;
			}
			Assert::AreEqual(1, flag);
		}

		TEST_METHOD(TestSetName)
		{
			Player p1{ "Tester" };
			p1.set_name("retseT");

			Assert::AreEqual("retseT", p1.get_name().c_str());
		}

		TEST_METHOD(TestAddWin)
		{
			Player p1{ "Tester" };
			p1.add_win();
			Assert::AreEqual(1, p1.read_wins());
		}

		TEST_METHOD(TestSetDelta)
		{
			/*Player p1{ "Tester" };
			duration  delta =  std::chrono::system_clock::now().time_since_epoch();
			p1.set_delta(delta);

			Assert::AreEqual(delta, p1.get_delta());
			*/

			/*
			 * Funktioniert leider nicht. Es ist mir leider nicht gelungen die Variablen vom
			 * Typ duration bzw. duration::rep auf einen anderen Typ zu casten oder die Funktion AreEqual mit duration zum Laufen zu bringen.
			 * Error List:
			 * Severity		Code	Description										File			Line
		 	 * Error		C3690	expected a string literal, but found a user-defined string literal instead		cppunittestassert.h	66
			 */

			Player p1{ "Tester" };
			auto flag = 0;

			std::chrono::system_clock::duration const delta = std::chrono::system_clock::now().time_since_epoch();
			p1.set_delta(delta);

			if (p1.get_delta() == delta)
			{
				flag = 1;
			}

			Assert::AreEqual(1, flag);
		}
	};
}
