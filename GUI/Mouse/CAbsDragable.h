#pragma once

#include "IDragable.h"
#include "../Region/CAbsRegion.h"

namespace ipgdlib
{
	namespace os
	{
		template <typename T, bool bDragable>
		class CAbsDragable :
			public IDragable
		{
			public:
				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;

				bool isDragable() const override
				{
					return true;
				}

				virtual size_t getDragCount() const = 0;
				virtual const CAbsRegion<T> &getDragRegion(size_t index) const = 0;
				virtual size_t getDragIndexFromPos(const Point& pos) const = 0;
				virtual eAffectedAxis getDragAffectedAxis(size_t index) const = 0;
				virtual void setDrag(size_t index, const Point& deltaPos) = 0;

		};

		template<typename T>
		class CAbsDragable<T, false> :
			public IDragable
		{
		public:
			bool isDragable() const override
			{
				return false;
			}
		};

	}
}
