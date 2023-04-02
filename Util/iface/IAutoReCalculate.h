#pragma once

#include "IReCalculate.h"

namespace ipgdlib
{
	namespace util
	{

		class IAutoReCalculate :
			virtual public IReCalculate
		{
		public:
			virtual bool getAutoReCalculate() const = 0;
			virtual void setAutoReCalculate(bool bAutoReCalculate) = 0;

		protected:
			virtual void autoReCalculate() = 0;

		};

	}
}


