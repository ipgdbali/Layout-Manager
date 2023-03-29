#pragma once

#include "CAbsRegion.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		struct CAbsRegionOperation : 
			public CAbsRegion<T>
		{

			bool isRegionOperation() const override final
			{
				return true;
			}

			virtual size_t getOperandCount() const = 0;
			virtual const CAbsRegion<T>& getOperand(size_t index) const = 0;
			virtual CAbsRegion<T>& getOperand(size_t index) = 0;

		};

	}
}


