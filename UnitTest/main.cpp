#include "pch.h"
#include "CppUnitTest.h"
#include "../main/CLMPadder.h"
#include "../main/CLMAligner.h"
#include "../main/CLMSplitter.h"
#include "../main/CAbsManagerStatic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::layout;


namespace LayoutManagerTest
{
	TEST_CLASS(LayoutManagerTest)
	{

		public:
			TEST_METHOD(class_CPlaceHolder)
			{
				CAbsBasePlaceHolder<int>* pPlaceHolder = new CPlaceHolder<int>();
				Assert::AreEqual<bool>(pPlaceHolder->hasCustomData(), false);
				delete pPlaceHolder;

				pPlaceHolder = new CPlaceHolder<int, int>(10);
				Assert::AreEqual<bool>(pPlaceHolder->hasCustomData(), true);
				Assert::AreEqual<int>(
					dynamic_cast<CPlaceHolder<int,int>*>(pPlaceHolder)->getCustomData(), 
					10
				);
				delete pPlaceHolder;
			}

			TEST_METHOD(class_CLMPadder)
			{
				CLMPadder<int> root({ 5,5,5,5 }, new CPlaceHolder<int,int>(10));

				root.changeRect({ 0,0,99,99 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>
					(root.getChildPlaceHolder(0)->getRect(), { 5,5,94,94 });
				Assert::AreEqual<size_t>(root.getChildCount(), 1);
				Assert::AreEqual<bool>(root.getAutoReCalculate(), true);
				Assert::AreEqual<size_t>(root.getChildIndexFromPoint({ 20,20 }), 0);
				Assert::AreEqual<bool>(root.getChildPlaceHolder(0)->hasCustomData(),true);
				Assert::AreEqual<int>(
					dynamic_cast<CPlaceHolder<int,int>*>(
						root.getChildPlaceHolder(0)
					)->getCustomData(),
					10);
			}

			TEST_METHOD(class_CLMHorzALigner)
			{
				CLMAlignerHorz<int>(eAlignHorz::Stretch, 10, new CPlaceHolder<int,int>(10));
			}

			TEST_METHOD(class_CLMVertALigner)
			{
				CLMAlignerVert<int>(eAlignVert::Stretch, 10, new CPlaceHolder<int,int>(10));
			}

			TEST_METHOD(class_CLMSplitterHorz)
			{
				CLMSplitterHorz<int,eSplitterKind::eFixedScaled>(100, 5,
					{
						new CPlaceHolder<int,int>(10),
						new CPlaceHolder<int,int>(10)
					});
			}

			TEST_METHOD(class_CLMSplitterVert)
			{
				CLMSplitterVert<int, eSplitterKind::eFixedScaled>(100, 5,
					{
						new CPlaceHolder<int,int>(10),
						new CPlaceHolder<int,int>(10)
					});
			}

	};
}
