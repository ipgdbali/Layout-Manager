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
			/*
			TEST_METHOD(class_CLMHorzALigner)
			{
				CLMAlignerHorz<int>(eAlignHorz::Stretch, 10, new CPlaceHolder<int,int>(10));
			}

			TEST_METHOD(class_CLMVertALigner)
			{
				CLMAlignerVert<int>(eAlignVert::Stretch, 10, new CPlaceHolder<int,int>(10));
			}
			*/

			TEST_METHOD(class_CLMSplitterHorz_FixedScaled)
			{

				CAbsBasePlaceHolder<int> *phA = new CPlaceHolder<int>();
				CAbsBasePlaceHolder<int> *phB = new CPlaceHolder<int>();

				CLMSplitterHorz<int,eSplitterKind::eFixedScaled> splitter(100, 5,{phA,phB});

				splitter.changeRect({ 0,0,499,499});
				Assert::AreEqual<void*>(splitter.getFixedPlaceHolder(), phA);
				Assert::AreEqual<void*>(splitter.getScaledPlaceHolder(), phB);

				Assert::AreEqual<int>(splitter.getDragCount(), 1);

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,99,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
					)->getRect(), {100,0,104,499});
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 105,0,499,499 });

				splitter.setDrag(0, { 5,0 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,104,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
						)->getRect(), { 105,0,109,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 110,0,499,499 });

				splitter.setDrag(0, { -5,0 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,99,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
						)->getRect(), { 100,0,104,499 }
				);
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 105,0,499,499 });
			}

			TEST_METHOD(class_CLMSplitterHorz_ScaledFixed)
			{

				CAbsBasePlaceHolder<int>* phA = new CPlaceHolder<int>();
				CAbsBasePlaceHolder<int>* phB = new CPlaceHolder<int>();

				CLMSplitterHorz<int, eSplitterKind::eScaledFixed> splitter(100, 5, { phA,phB });

				splitter.changeRect({ 0,0,499,499 });
				Assert::AreEqual<void*>(splitter.getFixedPlaceHolder(), phB);
				Assert::AreEqual<void*>(splitter.getScaledPlaceHolder(), phA);

				Assert::AreEqual<int>(splitter.getDragCount(), 1);
				
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 400,0,499,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
					)->getRect(), { 395,0,399,499 }
				);
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,394,499 });
				
				splitter.setDrag(0, { 5,0 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,399,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
						)->getRect(), { 400,0,404,499 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 405,0,499,499 });


				splitter.setDrag(0, { -5,0 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phB->getRect(), { 400,0,499,499 });
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(
					dynamic_cast<CRegionRectangle<int>*>(
						splitter.getDragInfo(0).dragRegion
						)->getRect(), { 395,0,399,499 }
				);
				Assert::AreEqual<ipgdlib::geometry::SRect<int>>(phA->getRect(), { 0,0,394,499 });
			}

			/*
			TEST_METHOD(class_CLMSplitterVert)
			{
				CLMSplitterVert<int, eSplitterKind::eFixedScaled>(true,100, 5,
					{
						new CPlaceHolder<int,int>(10),
						new CPlaceHolder<int,int>(10)
					});
			}
			*/
	};
}
