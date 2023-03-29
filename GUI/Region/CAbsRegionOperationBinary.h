#pragma once

#include "IRegionOperationBinary.h"

namespace ipgdlib
{
	namespace os
	{

		template <typename T>
		class CRegionOperationSubtraction :
			public IRegionOperationBinary<T>
		{

		public:
			CRegionOperationSubtraction(const IRegion<T>& lhs, const IRegion<T>& rhs) :
				m_Lhs(lhs), m_Rhs(rhs)
			{
			}

			const IRegion<T>& getLhs() const override
			{
				return this->m_Lhs;
			}

			const IRegion<T>& getRhs() const override
			{
				return this->m_Rhs;
			}

			bool isPointInside(const Point& p) const override
			{
				return m_Lhs.isPointInside(p) && !m_Rhs.isPointInside(p);
			}

		protected:

		private:
			const IRegion<T>& m_Lhs;
			const IRegion<T>& m_Rhs;
		};

	}
}


