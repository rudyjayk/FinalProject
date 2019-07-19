#include "pch.h"
#include "CppUnitTest.h"
#include "..\\Final Project\Nurse.h"
#include "..\\Final Project\Serviceset.h"
#include "..\\Final Project\Patient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_changOpen_Nurse) //Tests changeOpen function of Nurse class
		{
			Nurse test1(1); 
			test1.changeOpen(false);
			Assert::AreEqual(test1.getOpen(), false);
		}

		TEST_METHOD(Test_operator_overload) //Tests the operator '<'  with patient class
		{
			Patient test2("Rudy",10, 0);
			Patient other("Rob",11, 0);
			
			Assert::AreEqual(test2 < other, true);
		}

		TEST_METHOD(Test_changOpen_Doctor) //Tests the changeOpen method with Doctor class
		{
			Doctor test3(3);
			test3.changeOpen(false);
			Assert::AreEqual(test3.getOpen(), false);
		}

		TEST_METHOD(Test_priorityqueue) //Test the operator overload '<' with the priority queue
		{
			
			std::priority_queue<Patient*> testQueue;

			testQueue.push(new Patient("Bob",5,1));
			testQueue.push(new Patient ("Joe",11,0));

			int test = testQueue.top()->priority_num;

			Assert::AreEqual(test, 11);

		}
	};
}
