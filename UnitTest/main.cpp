#include "pch.h"
#include "CppUnitTest.h"
#include "../main/CLMPadder.h"
#include "../main/CLMAligner.h"
#include "../main/CLMSplitter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::layout;


namespace LayoutManagerTest
{
	TEST_CLASS(LayoutManagerTest)
	{

		public:
			TEST_METHOD(class_CLMPadder)
			{
				CLMPadder<int> root({ 5,5,5,5 }, new CPlaceHolder<int>());
				root.changeRect({ 0,0,99,99 });

				Assert::AreEqual<ipgdlib::geometry::SRect<int>>
					(root.getChildPlaceHolder(0)->getRect(), { 5,5,94,94 });
				Assert::AreEqual<size_t>(root.getChildCount(), 1);
				Assert::AreEqual <bool>(root.getAutoReCalculate(), true);
				Assert::AreEqual <size_t>(root.getChildIndexFromPoint({ 20,20 }), 0);
			}

			TEST_METHOD(class_CLMHorzALigner)
			{
				CLMHorzAligner<int>(eAlignHorz::Stretch, 10, new CPlaceHolder<int>());
			}

			TEST_METHOD(class_CLMVertALigner)
			{
				CLMVertAligner<int>(eAlignVert::Stretch, 10, new CPlaceHolder<int>());
			}

			TEST_METHOD(class_CLMHorzSplitter)
			{
				CLMHorzSplitter<eSplitterKind::eFixedScaled, int>(100, 5,
					{
						new CPlaceHolder<int>(),
						new CPlaceHolder<int>()
					});
			}

			TEST_METHOD(class_CLMVertSplitter)
			{
				CLMVertSplitter<eSplitterKind::eFixedScaled, int>(100, 5,
					{
						new CPlaceHolder<int>(),
						new CPlaceHolder<int>()
					});
			}

	};
}
