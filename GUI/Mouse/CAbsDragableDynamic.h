#pragma once

#include "../../Util/iface/IContainerKind.h"
#include "CAbsDragable.h"
#include <vector>

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CAbsDragAbleDynamic :
			public CAbsDragable<T, true>,
		{
		public:

			CAbsDragAbleDynamic(std::vector<SDragInfo> vDragInfo) :
				CAbsDragable<T, true>(),m_vDragInfo(std::move(vDragInfo))
			{
			}

			eContainerKind getContainerKind() const override {
				return eContainerKind::Dynamic;
			}

			size_t getDragCount() const override {
				return this->m_vDragInfo.size();
			}

			const SDragInfo &getDragInfo(size_t index) const override {
				return this->m_vDragInfo[index];
			}

			size_t getDragIndexFromPoint(Point p) {

				for (int li = 0; li < m_vDragInfo; li++)
					if (m_vDragInfo[li].dragRegion->isPointInside(p))
						return li;

				return (size_t)-1;
			}

		protected:
			std::array<SDragInfo,n> &getItemsRef() {
				return this->m_vDragInfo;
			}

			SDragInfo & getDragInfoRef(size_t index) override {
				return this->m_vDragInfo[index];
			}

		private:
			std::vector<SDragInfo> m_vDragInfo;

		};

	}
}

