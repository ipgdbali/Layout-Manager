#pragma once

#include "CAbsRegionOperationUnary.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CRegionOperationIntersection :
			public CAbsRegionOperationUnary<T>
		{

		public:
			CRegionOperationIntersection(CAbsRegion<T>& opr) :
				CAbsRegionOperationUnary<T>(opr)
			{
			}

			bool isPointInside(const Point& p) const override
			{
				return !this->getOperand().isPointInside(p);
			}

		};

	}
}


