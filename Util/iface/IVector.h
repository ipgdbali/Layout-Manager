#pragma once

#include "IVectorBase.h"

namespace ipgdlib
{
	namespace util
	{

		template <typename TItemType>
		class IVector :
			virtual public IVectorBase,
			virtual public ICollection

		{
			public:
				virtual const TChildType& getItem(size_t index) const = 0;

			protected:
				virtual TChildType& getItemRef() = 0;
		};

	}
}
