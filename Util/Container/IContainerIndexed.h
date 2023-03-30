#pragma once

#include "IContainer.h"
#include "IContainerKind.h"

namespace ipgdlib
{
	namespace util
	{

		template <typename TChildType>
		class IContainerIndexed :
			virtual public IContainer
			virtual public IContainerKind,
		{
			public:
				virtual const TChildType& getChild(size_t index) const = 0;

			protected:
				virtual TChildType& getChildRef(size_t index) = 0;
		};

	}
}
