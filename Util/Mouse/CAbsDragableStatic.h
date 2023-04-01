#pragma once

#include "../Container/IContainerKind.h"
#include "CAbsDragable.h"

namespace ipgdlib
{
	namespace os
	{

		template <
			typename T,
			typename U,
			size_t n
		>
		class CAbsDragAbleStatic :
			public CAbsDragable<T,U>
		{
		public:
			CAbsDragAbleStatic(bool def, std::array<SDragInfo<T>, n> dragInfo) :
				CAbsDragable<T, U>(def),
				m_Collection(std::move(dragInfo))
			{
			}

			CAbsDragAbleStatic(bool def) :
				CAbsDragable<T, U>(def),
				m_Collection()
			{
			}

			ipgdlib::container::eContainerKind getContainerKind() const override {
				return ipgdlib::container::eContainerKind::Static;
			}
			
			size_t getDragCount() const override {
				return n;
			}

			const SDragInfo<T>& getDragInfo(size_t index) const override {
				return this->m_Collection[index];
			}

			size_t getDragIndexFromPoint(ipgdlib::geometry::SPoint<U> p) {

				for (int li = 0; li < m_Collection; li++)
					if (m_Collection[li].dragRegion->isPointInside(p))
						return li;

				return (size_t)-1;
			}

		protected:
			std::array<SDragInfo<T>,n> &getCollectionRef() {
				return this->m_Collection;
			}
			
			SDragInfo<T>& getDragInfoRef(size_t index) override {
				return this->m_Collection[index];
			}

		protected:

		private:
			std::array<SDragInfo<T>, n> m_Collection;

		};

	}
}

