#pragma once

#include "CAbsManager.h"

namespace ipgdlib
{
	namespace layout
	{

		template <typename T, typename TChildItem = void,typename TCustomData = void>
		class CAbsManagerDynamic :
			public CAbsManager<T, TCustomData, TChildItem>
		{

        public:
			using child_item_type = CAbsManager<T,TCustomData, TChildItem>::child_item_type;

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< 
                    std::is_same<_TCustomData, void>::value, 
                    bool 
                >::type = true
            >
            CAbsManagerDynamic(std::vector<child_item_type> childs) : 
                CAbsManager<T, TCustomData, TChildItem>(),
                m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(
                        this->getChildPlaceHolder(li)
                    );
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< 
                    !std::is_same<_TCustomData, void>::value, 
                    bool 
                >::type = true
            >
            CAbsManagerDynamic(
                _TCustomData customData, 
                std::vector<child_item_type> childs
            ) : 
                CAbsManager<T, TCustomData, TChildItem>(std::move(customData)), 
                m_Childs(std::move(childs))
            {
                for (size_t li = 0; li < childs.size(); li++)
                    CAbsManager<T, TCustomData, TChildItem>::setChildParent(
                        this->getChildPlaceHolder(li)
                    );
            }

            eCollectionKind getCollectionKind() const override
            {
                return eCollectionKind::Dynamic;
            }

            size_t getChildCount() const override
            {
                return m_Childs.size();
            }

            child_item_type const& getChild(size_t index) const override
            {
                return this->m_Childs[index];
            }

        protected:

            std::vector<child_item_type> &getVector()
            {
                return this->m_Childs;
            }


            child_item_type& getChildRef(size_t index) override
            {
                return this->m_Childs[index];
            }

        private:
            std::vector<child_item_type> m_Childs;

		};


	}
}
