#pragma once

#include "IVectorBase.h"

namespace ipgdlib
{
	namespace util
	{

		template <typename TChildType>
		class IVector :
			public IVectorBase
		{
			public:
				virtual const TChildType& getChild(size_t index) const = 0;

			protected:
				virtual TChildType& getChildRef() = 0;
		};

	}
}
