#pragma once

namespace ipgdlib
{
	namespace util
	{

		template <typename T>
		struct ISizeable
		{
			virtual ~ISizeable() {};
			virtual T getSize() const = 0;
			virtual void setSize(T) = 0;
		};

	}

}


