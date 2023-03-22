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
            typename TCustomData = void,
            typename TChildItem = void
        >
        class CAbsManagerStatic :
            public CAbsManager<T,TCustomData,TChildItem>
        {

        public:
            using child_item_type = CAbsManager<T, TCustomData, TChildItem>::child_item_type;

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const std::array<child_item_type, n> & childs) :
                CAbsManager<T, TCustomData, TChildItem>(), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(std::array<child_item_type, n> && childs) :
                CAbsManager<T, TCustomData, TChildItem>(), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const _TCustomData& customData, const std::array<child_item_type, n>& childs)
                : CAbsManager<T, TCustomData, TChildItem>(customData), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(const _TCustomData& customData, std::array<child_item_type, n> && childs)
                : CAbsManager<T, TCustomData, TChildItem>(customData), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(_TCustomData && customData, const std::array<child_item_type, n> & childs)
                : CAbsManager<T, TCustomData, TChildItem>(std::move(customData)), m_Childs(childs)
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManagerStatic(_TCustomData && customData, std::array<child_item_type, n> && childs)
                : CAbsManager<T, TCustomData, TChildItem>(std::move(customData)), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < n; li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(this->getChildPlaceHolder(li));
            }

            size_t getChildCount() const override
            {
                return n;
            }

            child_item_type const &getChild(size_t index) const override
            {
                return this->m_Childs[index];
            }

        protected:

            child_item_type &getChildRef(size_t index) override
            {
                return this->m_Childs[index];
            }

        private:
            std::array<child_item_type, n> m_Childs;
        };

    }
}


