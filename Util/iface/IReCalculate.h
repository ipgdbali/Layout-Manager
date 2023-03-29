#pragma once

namespace ipgdlib
{
	namespace util
	{

		struct IReCalculate
		{
			virtual ~IReCalculate() {};
			virtual void reCalculate() = 0;
		};

	}

}

