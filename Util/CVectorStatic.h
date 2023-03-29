#pragma once

#include "IVector.h"
#include <array>

namespace ipgdlib
{
	namespace util
	{
		template <typename TChildType,size_t n>
		class CVectorStatic :
			public IVector<TChildType>
		{
			public:
				CVectorStatic(std::array<TChildType,n> init) :
					m_Childs(std::move(init))
				{

				}

				eVectorKind getVectorKind() const override
				{
					return eVectorKind::Static;
				}

				size_t getChildCount() const override
				{
					return n;
				}

				const TChildType& getChild(size_t index) const override
				{
					return m_Childs[index];
				}

			protected:

				std::array<TChildType,n> &getChilds()
				{
					return this->m_Childs;
				}

				TChildType& getChildRef(size_t index) override
				{
					return m_Childs[index];
				}

			private:
				std::array<TChildType, n> m_Childs;

		};

	}
}

