#pragma once

#include "IReCalculate.h"

namespace ipgdlib
{
	namespace util
	{

		struct IAutoReCalculate :
			virtual public IReCalculate
		{

			virtual bool getAutoReCalculate() const = 0;
			virtual void setAutoReCalculate(bool bAutoReCalculate) = 0;

		protected:
			virtual void autoReCalculate() = 0;

		};

	}
}


