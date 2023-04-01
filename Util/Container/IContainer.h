#pragma once

namespace ipgdlib
{
	namespace container
	{

		struct IContainer
		{

			virtual ~IContainer() {};
			virtual size_t getChildCount() const = 0;
		
		};

	}
}


