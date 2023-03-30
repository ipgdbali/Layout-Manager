#pragma once

#include "../../Util/Geometry/SRect.h"

namespace ipgdlib
{
	namespace os
	{

		using namespace ipgdlib::geometry;

		template <typename T>
		class CAbsRegion
		{
			public:
				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;

				virtual ~CAbsRegion() 
				{
				}

				virtual bool isRegionOperation() const
				{
					return false;
				}

				virtual bool isPointInside(const Point& p) const = 0;
		};

	}
}

