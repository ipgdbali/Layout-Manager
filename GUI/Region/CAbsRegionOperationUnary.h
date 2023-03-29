#pragma once

#include "CAbsRegionOperation.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CAbsRegionOperationUnary :
			public CAbsRegionOperation<T>
		{

			CAbsRegionOperation(CAbsRegion<T> opr) :
				m_Opr(opr)
			{
			}

			size_t getOperandCount() const override
			{
				return 1;
			}

			const CAbsRegion<T>& getOperand(size_t index) const override
			{
				if (index == 0)
					return this->m_Opr;
				else
					throw std::invalid_argument("Index Out of Bound");
			}

			CAbsRegion<T>& getOperand(size_t index) override
			{
				if (index == 0)
					return this->m_Opr;
				else
					throw std::invalid_argument("Index Out of Bound");
			}

			const CAbsRegion<T>& getOperand() const
			{
				return this->m_Opr;
			}

			CAbsRegion<T>& getOperand()
			{
				return this->m_Opr;
			}

		private:
			CAbsRegion<T>& m_Opr;

		};

	}
}