#pragma once

#include "iface/IAutoReCalculate.h"

namespace ipgdlib
{
	namespace util
	{

		class CAbsAutoReCalculate :
			virtual public IAutoReCalculate
		{
		public:
			CAbsAutoReCalculate(bool bAutoReCalculate = true) :
				m_bAutoReCalculate(bAutoReCalculate)
			{
			}

			bool getAutoReCalculate() const override
			{
				return this->m_bAutoReCalculate;
			}

			void setAutoReCalculate(bool bAutoReCalculate) override
			{
				this->m_bAutoReCalculate = bAutoReCalculate;
			}

		protected:
			void autoReCalculate() override
			{
				if (this->m_bAutoReCalculate)
					this->reCalculate();
			}

		private:
			bool m_bAutoReCalculate;
		};

	}
}

