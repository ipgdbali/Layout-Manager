#pragma once

namespace ipgdlib
{
	namespace util
	{

		class ICollection
		{
			virtual ~ICollection() {};
			virtual size_t getItemCount() const = 0;
		};

	}
}


