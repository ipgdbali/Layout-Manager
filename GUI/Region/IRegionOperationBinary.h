#pragma once

#include "IRegionOperation.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		struct IRegionOperationBinary :
			public IRegionOperation<T>
		{

			virtual const IRegion<T>& getOperandLhs() const = 0;
			virtual IRegion<T>& getOperandLhs() = 0;

			virtual const IRegion<T>& getOperandRhs() const = 0;
			virtual IRegion<T>& getOperandRhs() = 0;

		};

	}
}


