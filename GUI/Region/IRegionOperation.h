#pragma once

#include "IRegion.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		struct IRegionOperation : 
			public IRegion<T>
		{

			virtual size_t getOperandCount() const = 0;

			virtual const IRegion<T>& getOperand(size_t index) const = 0;
			virtual IRegion<T>& getOperand(size_t index) = 0;

		};

	}
}


