#pragma once

#include "CAbsRegion.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CRegionRectangle :
			public CAbsRegion<T>
		{
			public:
				using Rect = ipgdlib::geometry::SRect<T>;
				using Point = ipgdlib::geometry::SPoint<T>;
				
				CRegionRectangle(Rect r) :
					m_Rect(std::move(r))
				{
				}

				const Rect& getRect() const
				{
					return this->m_Rect;
				}

				bool isPointInside(const Point& p) const override
				{
					return this->m_Rect.isPointInRect(p);
				}
			
			private:
				Rect m_Rect;
		};

	}
}

