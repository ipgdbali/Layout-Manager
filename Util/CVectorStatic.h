#pragma once

#include "IVector.h"
#include <array>

namespace ipgdlib
{
	namespace util
	{
		template <typename TItemType,size_t n>
		class CVectorStatic :
			public IVector<TItemType>
		{
			public:
				CVectorStatic(std::array<TItemType,n> init) :
					m_Items(std::move(init))
				{

				}

				eCollectionKind getCollectionKind() const override
				{
					return eCollectionKind::Static;
				}

				size_t getItemCount() const override
				{
					return n;
				}

				const TItemType& getItem(size_t index) const override
				{
					return m_Items[index];
				}

			protected:

				std::array<TItemType,n> &getItems()
				{
					return this->m_Items;
				}

				TItemType& getItemRef(size_t index) override
				{
					return m_Items[index];
				}

			private:
				std::array<TItemType, n> m_Items;

		};

	}
}

