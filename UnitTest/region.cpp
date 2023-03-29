#include "pch.h"
#include "CppUnitTest.h"
#include "../GUI/Region/CRegionRectangle.h"
#include "../GUI/Region/CRegionOperationSubtraction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace RegionTest
{
	TEST_CLASS(RegionTest)
	{

	public:

		TEST_METHOD(class_CRegionRectangle)
		{
			ipgdlib::os::CRegionRectangle<int> rRect({ 10,10,100,100 });

			Assert::AreEqual<bool>(rRect.isRegionOperation(), false);
			Assert::AreEqual<bool>(rRect.isPointInside({ 10,10 }), true);
			Assert::AreEqual<bool>(rRect.isPointInside({ 100,100 }), true);
		}

		TEST_METHOD(class_Substraction)
		{
			ipgdlib::os::CRegionRectangle<int> rRect1({ 10,10,100,100 });
			ipgdlib::os::CRegionRectangle<int> rRect2({ 30,30,40,40 });

			ipgdlib::os::CRegionOperationSubtraction<int> rSub(rRect1,rRect2);

			Assert::AreEqual<bool>(rSub.isRegionOperation(), true);
			Assert::AreEqual<bool>(rSub.isPointInside({ 35,35 }), false);
			Assert::AreEqual<bool>(rSub.isPointInside({ 50,50 }), true);

		}


	};
}
