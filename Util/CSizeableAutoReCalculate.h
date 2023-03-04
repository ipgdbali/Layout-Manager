#pragma once

#include "../Util/CSizeable.h"
#include "../Util/IAutoReCalculate.h"


namespace ipgdlib
{
	namespace util
	{

		template <typename T>
		class CSizeableAutoReCalculate :
			public ipgdlib::util::CSizeable<T>,
			virtual public ipgdlib::util::IAutoReCalculate
		{
		public:
			CSizeableAutoReCalculate(const T& size) :
				ipgdlib::util::CSizeable<T>(size)
			{
			}

			void setSize(const T& size) override
			{
				ipgdlib::util::CSizeable<T>::setSize(size);
				this->autoReCalculate();
			}

		};

	}
}
