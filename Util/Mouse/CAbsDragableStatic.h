#pragma once

#include "../../Util/iface/IContainerKind.h"
#include "CAbsDragable.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T,size_t n>
		class CAbsDragAbleStatic :
			public CAbsDragable<T,true>
		{
		public:
			CAbsDragAbleStatic(std::array<SDragInfo,n> arrDragInfo) :
				CAbsDragable<T, true>(),
				m_arrDragInfo(std::move(arrDragInfo))
			{
			}

			eContainerKind getContainerKind() const override {
				return eContainerKind::Static;
			}
			
			size_t getDragCount() const override {
				return n;
			}

			const SDragInfo& getDragInfo(size_t index) const override {
				return this->m_arrDragInfo[index];
			}

			size_t getDragIndexFromPoint(Point p) {

				for (int li = 0; li < m_arrDragInfo; li++)
					if (m_arrDragInfo[li].dragRegion->isPointInside(p))
						return li;

				return (size_t)-1;
			}

		protected:
			std::array<SDragInfo,n> &getItemsRef() {
				return this->m_arrDragInfo;
			}
			
			SDragInfo& getDragInfoRef(size_t index) override {
				return this->m_arrDragInfo[index];
			}

		protected:

		private:
			std::array<SDragInfo, n> m_arrDragInfo;

		};

	}
}

