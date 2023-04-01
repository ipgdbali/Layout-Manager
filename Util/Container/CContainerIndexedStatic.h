#pragma once

#include "IContainerIndexed.h"
#include <array>

namespace ipgdlib
{
	namespace container
	{

		template <typename TChildType,size_t n>
		class CContainerIndexedStatic :
			virtual public IContainerT<std::array<TChildType,n>>,
			virtual public IContainerIndexed<TChildType>
		{

			public:
				IContainerIndexedStatic(std::array<TChildType,n> init) :
					m_Container(std::move(init))
				{
				}

				eContainerKind getContainerKind() const override
				{
					return eContainerKind::Static;
				}

				size_t getChildCount() const override
				{
					return n;
				}

				const TChildType& getChild(size_t index) const override
				{
					return m_Container[index];
				}

			protected:

				const std::array<TChildType, n>& getContainer() const override
				{
					return this->m_Container;
				}

				std::array<TChildType,n> &getContainer() override
				{
					return this->m_Container;
				}

				TChildType& getItemRef(size_t index) override
				{
					return m_Container[index];
				}

			private:
				std::array<TChildType, n> m_Container;

		};

	}
}

