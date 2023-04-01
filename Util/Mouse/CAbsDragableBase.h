#pragma once

#include "IDragable.h"
#include "../Container/IContainerKind.h"
#include "../iface/IAffectedAxis.h"
#include "../Region/CAbsRegion.h"
#include <vector>

using namespace ipgdlib::util;

namespace ipgdlib
{
	namespace os
	{
		template <typename T>
		struct SDragInfo
		{
			CAbsRegion<T>* dragRegion;
			eAffectedAxis affectedAxis;
			std::vector<size_t> affectedPlaceHolderIndex;
		};

		template <typename T, bool bDragable>
		class CAbsDragableBase :
			virtual public IDragable,
			virtual public ipgdlib::container::IContainerKind
		{
			public:

				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;

				CAbsDragableBase(bool def) :
					m_isDragEnabled(def)
				{
				}

				bool isDragable() const override
				{
					return true;
				}

				bool isDragEnabled() const
				{
					return m_isDragEnabled;
				}

				void setDragEnabled(bool enable)
				{
					this->m_isDragEnabled = enable;
				}

				virtual size_t getDragCount() const = 0;
				virtual const SDragInfo<T>& getDragInfo(size_t index) const = 0;

			protected:
				virtual SDragInfo<T>& getDragInfoRef(size_t index)  = 0;

			private:
				bool m_isDragEnabled;
		};

		template<typename T>
		class CAbsDragableBase<T, false> :
			virtual public IDragable
		{
		public:
			bool isDragable() const override
			{
				return false;
			}
		};

	}
}
