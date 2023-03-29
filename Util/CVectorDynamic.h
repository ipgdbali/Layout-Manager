#pragma once

#include "IVector.h"
#include <vector>

namespace ipgdlib
{
	namespace util
	{

		template <typename TChildType>
		class CVectorDynamic :
			public IVector<TChildType>
		{
		public:
			CVectorDynamic(std::vector<TChildType> v) : 
				m_Childs(std::move(v))
			{
			}

			eVectorKind getVectorKind() const override
			{
				return eVectorKind::Dynamic;
			}

			size_t getChildCount() const override
			{
				return m_Childs.size();
			}

			const TChildType& getChild(size_t index) const override
			{
				return m_Childs[index];
			}

		protected:

			TChildType& getChildRef(size_t index) override
			{
				return m_Childs[index];
			}

			std::vector<TChildType>& getChilds()
			{
				return this->m_Childs;
			}


		private:
			std::vector<TChildType> m_Childs;

		};

	}
}

