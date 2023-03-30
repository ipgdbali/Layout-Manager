#pragma once

#include "IContainerIndexed.h"
#include <vector>

namespace ipgdlib
{
	namespace util
	{

		template <typename TChildType>
		class CContainerIndexedDynamic:
			virtual public IContainerT< std::vector<TItemType> >,
			virtual public IContainerIndexed<TChildType>
		{
		public:
			CVectorDynamic(std::vector<TChildType> v) : 
				m_Container(std::move(v))
			{
			}

			eContainerKind getContainerKind() const override
			{
				return eContainerKind::Dynamic;
			}

			size_t getChildCount() const override
			{
				return m_Container.size();
			}

			const TChildType& getChild(size_t index) const override
			{
				return m_Container[index];
			}

		protected:

			TChildType& getChildRef(size_t index) override
			{
				return m_Container[index];
			}

			const std::vector<TChildType>& getContainer() const override
			{
				return this->m_Container;
			}

			std::vector<TChildType>& getContainer() override
			{
				return this->m_Container;
			}

		private:
			std::vector<TChildType> m_Container;

		};

	}
}

