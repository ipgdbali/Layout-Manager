#pragma once

#include "CAbsBaseManager.h"
#include "CPlaceHolder.h"
#include <utility>

namespace ipgdlib
{
    namespace layout
    {

        template <
            typename T,
            typename TCustomData, // Custom Data 
            typename TChildItem  // child_item_type
        >
        class CAbsManagerTS : // TS -> template Specialization
            public CAbsBasePlaceHolder<T>::CAbsBaseManager,
            public CCustomData<TCustomData>
        {
            public:
                using child_item_type = TChildItem;

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CAbsManagerTS() : 
                    CAbsBasePlaceHolder<T>::CAbsBaseManager(), 
                    CCustomData<TCustomData>()
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        !std::is_same<_TCustomData, void>::value,
                        bool 
                    >::type = true
                >
                CAbsManagerTS(const _TCustomData & customData) :
                    CAbsBasePlaceHolder<T>::CAbsBaseManager(), 
                    CCustomData<TCustomData>(customData)
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        !std::is_same<_TCustomData, void>::value,
                        bool 
                    >::type = true
                >
                CAbsManagerTS(_TCustomData && customData) : 
                    CAbsBasePlaceHolder<T>::CAbsBaseManager(), 
                    CCustomData<TChildItem>(std::move(customData))
                {
                }

                virtual child_item_type const &getChild(size_t index) const = 0;
                virtual void setChild(size_t index, const child_item_type &child) = 0;

            protected:
                virtual child_item_type &getChildRef(size_t index) = 0;

            private:
        };

        template <typename T,typename TCustomData = void, typename TChildItem = void>
        class CAbsManager :
            public CAbsManagerTS<T, TCustomData, std::pair<TChildItem, CAbsBasePlaceHolder<T>*>>
        {
        public:
            using child_item_type = std::pair<TChildItem, CAbsBasePlaceHolder<T>*>;

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManager() :
                CAbsManagerTS < T,TCustomData, child_item_type>()
            {
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManager(const _TCustomData& customData)
                : CAbsManagerTS<T, std::pair<TCustomData, CAbsBasePlaceHolder<T>* >, TCustomData>(customData)
            {
            }

            template <
                typename _TCustomData = TCustomData,
                typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
            >
            CAbsManager(_TCustomData && customData)
                : CAbsManagerTS<T, std::pair<TCustomData, CPlaceHolder<T>*>, TCustomData>(std::move(customData))
            {
            }

            CAbsBasePlaceHolder<T>* const &getChildPlaceHolder(size_t index) const override
            {
                return this->getChild(index).second;
            }

            TChildItem const& getChildItem(size_t index) const
            {
                return this->getChild(index).first;
            }

            void setChild(size_t index,const child_item_type &child) override
            {
                this->setChildPlaceHolder(index, child.second);
                this->setChildItem(index, child.first);
            }

            virtual void setChildItem(size_t index,const TChildItem &item)
            {
                this->getChildItemRef(index) = item;
            }

        protected:
            CAbsBasePlaceHolder<T>* &getChildPlaceHolderRef(size_t index) override
            {
                return this->getChildRef(index).second;
            }

            TChildItem &getChildItemRef(size_t index)
            {
                return this->getChildRef(index).first;
            }

        };

        template <typename T,typename TCustomData>
        class CAbsManager<T,TCustomData, void> :
            public CAbsManagerTS < T,TCustomData, CAbsBasePlaceHolder<T>*>
        {
            public:
                using child_item_type = CAbsBasePlaceHolder<T>*;

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< std::is_same<_TCustomData, void>::value, bool >::type = true
                >
                CAbsManager() :
                    CAbsManagerTS < T, TCustomData, child_item_type>()
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
                >
                CAbsManager(const _TCustomData& customData)
                    : CAbsManagerTS<T, TCustomData, child_item_type>(customData)
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< !std::is_same<_TCustomData, void>::value, bool >::type = true
                >
                CAbsManager(_TCustomData && customData)
                    : CAbsManagerTS<T, child_item_type, TCustomData>(std::move(customData))
                {
                }

                CAbsBasePlaceHolder<T>* const &getChildPlaceHolder(size_t index) const override
                {
                    return this->getChild(index);
                }

                void setChild(size_t index, const child_item_type &child) override
                {
                    this->setChildPlaceHolder(index, child);
                }

        protected:
                CAbsBasePlaceHolder<T>* &getChildPlaceHolderRef(size_t index) override
                {
                    return this->getChildRef(index);
                }
        };

    }
}