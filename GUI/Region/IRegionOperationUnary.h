#pragma once

#include "IRegionOperation.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		struct IRegionOperationUnary :
			public IRegionOperation<T>
		{

			virtual const IRegion<T>& getOperand() const = 0;
			virtual IRegion<T>& getOperand() = 0;

		};

	}
}


