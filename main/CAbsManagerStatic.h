#pragma once

#include "CAbsManager.h"
#include <array>

namespace ipgdlib
{
    namespace layout
    {

        template <typename T,size_t n,typename U = void>
        class CAbsManagerStatic :
            public CAbsManager<T,U>
        {

        public:
            using child_type = CAbsManager<T, U>::child_type;

            CAbsManagerStatic(const std::array<child_type, n> &pPlaceHolder) :
                CAbsManager<T,U>(),m_Childs({})
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U>::setChild(li, pPlaceHolder[li]);
            }

            size_t getChildCount() const override
            {
                return n;
            }

            child_type const &getChild(size_t index) const override
            {
                return this->m_Childs[index];
            }

        protected:

            child_type &getChildRef(size_t index) override
            {
                return this->m_Childs[index];
            }

        private:
            std::array<child_type, n> m_Childs;
        };

    }
}


