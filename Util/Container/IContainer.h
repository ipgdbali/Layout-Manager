#pragma once

namespace ipgdlib
{
	namespace util
	{

		struct IContainer
		{
			virtual ~IContainer() {};
			virtual size_t getChildCount() const = 0;
		};

	}
}


