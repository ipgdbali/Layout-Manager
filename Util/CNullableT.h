#pragma once

#include "INullable.h"

namespace ipgdlib
{
	namespace util
	{

		template <bool bNull>
		class CNullableT :
			virtual public INullable
		{

			public:
				bool isNull() const override
				{
					return bNull;
				}

		};

	}
}


