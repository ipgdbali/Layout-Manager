#pragma once

#include "CAbsRegionOperation.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CAbsRegionOperationBinary :
			public CAbsRegionOperation<T>
		{

		public:
			CAbsRegionOperationBinary(CAbsRegion<T>& lhs, CAbsRegion<T>& rhs) :
				m_Lhs(lhs),m_Rhs(rhs)
			{
			}

			size_t getOperandCount() const override
			{
				return 2;
			}

			const CAbsRegion<T>& getOperand(size_t index) const override
			{
				switch (index)
				{
					case 0: return this->m_Lhs; break;
					case 1: return this->m_Rhs; break;
					default: throw std::invalid_argument("Index Out of Bound"); break;
				}
			}
			
			CAbsRegion<T>& getOperand(size_t index) override
			{

				switch (index)
				{
					case 0: return this->m_Lhs; break;
					case 1: return this->m_Rhs; break;
					default: throw std::invalid_argument("Index Out of Bound"); break;
				}
			}

			const CAbsRegion<T>& getLhs() const
			{
				return this->m_Lhs;
			}

			CAbsRegion<T>& getLhs()
			{
				return this->m_Lhs;
			}

			const CAbsRegion<T>& getRhs() const
			{
				return this->m_Rhs;
			}

			CAbsRegion<T>& getRhs() 
			{
				return this->m_Rhs;
			}

		protected:

		private:
			CAbsRegion<T>& m_Lhs;
			CAbsRegion<T>& m_Rhs;
		};

	}
}


