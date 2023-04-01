#pragma once
namespace ipgdlib
{
	namespace util
	{

		struct INullable
		{
			virtual ~INullable() = 0;
			virtual bool isNull() const = 0;
		};

	}
}

