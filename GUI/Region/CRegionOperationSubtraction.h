#pragma once

#include "CAbsRegionOperationBinary.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CRegionOperationSubtraction :
			public CAbsRegionOperationBinary<T>
		{

		public:
			CRegionOperationSubtraction(CAbsRegion<T>& lhs, CAbsRegion<T>& rhs) :
				CAbsRegionOperationBinary<T>(lhs, rhs)
			{
			}

			bool isPointInside(const Point& p) const override
			{
				return this->getLhs().isPointInside(p) && !this->getRhs().isPointInside(p);
			}

		};

	}
}


