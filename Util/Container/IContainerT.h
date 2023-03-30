#pragma once

#include "IContainer.h"

namespace ipgdlib{

	namespace util {

		template <typename TContainer>
		class IContainerT :
			virtual public IContainer
		{
			protected:
				virtual const TContainer& getContainer() const = 0;
				virtual TContainer& getContainer() = 0;
		};

	}
}
