#pragma once

#include "CAbsManager.h"

namespace ipgdlib
{
	namespace layout
	{

		template <typename T, typename U = void,typename V = void>
		class CAbsManagerDynamic :
			public CAbsManager<T, U, V>
		{

        public:
			using child_type = CAbsManager<T, U,V>::child_type;

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(const std::vector<child_type>& childs)
                : CAbsManager<T,U,V>(), m_Childs(childs)
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(std::vector<child_type> && childs)
                : CAbsManager<T, U, V>(), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(const _V& customData, const std::vector<child_type>& childs)
                : CAbsManager<T, U, V>(customData), m_Childs(childs)
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(const _V& customData, std::vector<child_type>&& childs)
                : CAbsManager<T, U, V>(customData), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(_V & customData, const std::vector<child_type> & childs)
                : CAbsManager<T, U, V>(customData), m_Childs(childs)
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerDynamic(_V && customData, std::vector<child_type> && childs)
                : CAbsManager<T, U, V>(std::move(customData)), m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, U, V>::setChildParent(this->getChildPlaceHolder(li));
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
