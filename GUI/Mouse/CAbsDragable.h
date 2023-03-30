#pragma once

#include "IDragable.h"
#include "../../Util/iface/ICollectionKind.h"
#include "../Region/CAbsRegion.h"

namespace ipgdlib
{
	namespace os
	{

		struct SDragInfo
		{
			CAbsRegion<T>* dragRegion;
			eAffectedAxis affectedAxis;
		};


		template <typename T, bool bDragable>
		class CAbsDragable :
			public IDragable,
			public ICollectionKind

		{
			public:

				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;


				bool isDragable() const override
				{
					return true;
				}

				virtual size_t getDragCount() const = 0;
				virtual const SDragInfo& getDragInfo(size_t index) const = 0;

			protected:
				virtual SDragInfo& getDragInfo()  = 0;

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
