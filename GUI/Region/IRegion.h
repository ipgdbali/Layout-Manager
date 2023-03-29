#pragma once

#include "../../Geometry/SRect.h"

namespace ipgdlib
{
	namespace os
	{

		using namespace ipgdlib::util;

		template <typename T>
		class IRegion
		{
			public:
				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;

				virtual ~IRegion() {};

				virtual bool isPointInside(const Point& p) const = 0;
		};

	}
}

