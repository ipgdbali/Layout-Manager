#pragma once
namespace ipgdlib
{
	namespace util
	{

		struct INullable
		{
			virtual bool isNull() const = 0;
		};

	}
}

