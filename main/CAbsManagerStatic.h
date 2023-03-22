#pragma once

#include "CAbsManager.h"
#include <array>

namespace ipgdlib
{
    namespace layout
    {

        template <
            typename T,
            size_t n,
            typename U = void,
            typename V = void
        >
        class CAbsManagerStatic :
            public CAbsManager<T,U,V>
        {

        public:
            using child_type = CAbsManager<T, U, V>::child_type;

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const std::array<child_type, n> & childs) :
                CAbsManager<T, U, V>(), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(std::array<child_type, n> && childs) :
                CAbsManager<T, U, V>(), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const _V& customData, const std::array<child_type, n>& childs)
                : CAbsManager<T, U, V>(customData), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const _V& customData, std::array<child_type, n> && childs)
                : CAbsManager<T, U, V>(customData), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(_V && customData, const std::array<child_type, n> & childs)
                : CAbsManager<T, U, V>(std::move(customData)), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerStatic(_V && customData, std::array<child_type, n> && childs)
                : CAbsManager<T, U, V>(std::move(customData)), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
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


