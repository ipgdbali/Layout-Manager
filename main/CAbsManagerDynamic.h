#pragma once

#include "CAbsManager.h"

namespace ipgdlib
{
	namespace layout
	{

		template <typename T, typename U = void>
		class CAbsManagerDynamic :
			public CAbsManager<T, U>
		{

        public:
			using child_type = CAbsManager<T, U>::child_type;

            CAbsManagerDynamic(const std::vector<child_type>& pPlaceHolders)
                : CAbsManager<T, U>(), m_Childs()
            {

                m_Childs.resize(pPlaceHolders.size());

                for (size_t li = 0; li < pPlaceHolders.size(); li++)
                    CAbsManager<T, U>::setChild(li, pPlaceHolders[li]);

            }

            size_t getChildCount() const override
            {
                return m_Childs.size();
            }

            child_type const& getChild(size_t index) const override
            {
                return this->m_Childs[index];
            }

        protected:

            child_type& getChildRef(size_t index) override
            {
                return this->m_Childs[index];
            }

        private:
            std::vector<child_type> m_Childs;

		};


	}
}