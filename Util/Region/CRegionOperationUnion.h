#pragma once

#include "CAbsRegionOperationBinary.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CRegionOperationUnion :
			public CAbsRegionOperationBinary<T>
		{

			public:
				CRegionOperationUnion(CAbsRegion<T>& lhs,CAbsRegion<T>& rhs) :
					CAbsRegionOperationBinary<T>(lhs,rhs)
				{
				}

				bool isPointInside(const Point& p) const override
				{
					return this->getLhs().isPointInside(p) || this->getRhs().isPointInside(p);
				}
		};

	}
}


