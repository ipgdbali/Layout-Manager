#pragma once

#include "CPlaceHolder.h"
#include <utility>

namespace ipgdlib
{
    namespace layout
    {

        template <
            typename T,
            typename U, // child_type
            typename V // CPlaceHolder,V
        >
        class CAbsManagerSelector :
            public CPlaceHolder<T,V>::CAbsBaseManager
        {
        public:
            using child_type = U;

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerSelector()
                : CPlaceHolder<T, _V>::CAbsBaseManager()
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerSelector(const _V& customData)
                : CPlaceHolder<T, _V>::CAbsBaseManager(customData)
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManagerSelector(_V && customData)
                : CPlaceHolder<T, _V>::CAbsBaseManager(std::move(customData))
            {
            }

            virtual child_type const &getChild(size_t index) const = 0;
            virtual void setChild(size_t index, const child_type &child) = 0;

        protected:
            virtual child_type&getChildRef(size_t index) = 0;

        private:
        };

        template <typename T,typename U = void, typename V = void>
        class CAbsManager :
            public CAbsManagerSelector<T, std::pair<U, CPlaceHolder<T,V>*>,V>
        {
        public:
            using child_type = std::pair<U, CPlaceHolder<T,V>*>;

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager() :
                CAbsManagerSelector < T, child_type,V>()
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager(const _V& customData)
                : CAbsManagerSelector<T, std::pair<U, CPlaceHolder<T,V>*>, V>(customData)
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager(_V && customData)
                : CAbsManagerSelector<T, std::pair<U, CPlaceHolder<T>*>, V>(std::move(customData))
            {
            }

            CPlaceHolder<T,V>* const &getChildPlaceHolder(size_t index) const override
            {
                return this->getChild(index).second;
            }

            U const& getChildItem(size_t index) const
            {
                return this->getChild(index).first;
            }

            void setChild(size_t index,const child_type &child) override
            {
                this->setChildPlaceHolder(index, child.second);
                this->setChildItem(index, child.first);
            }

            virtual void setChildItem(size_t index,const U &item)
            {
                this->getChildItemRef(index) = item;
            }

        protected:
            CPlaceHolder<T,V>* &getChildPlaceHolderRef(size_t index) override
            {
                return this->getChildRef(index).second;
            }

            U &getChildItemRef(size_t index)
            {
                return this->getChildRef(index).first;
            }

        };

        template <typename T,typename V>
        class CAbsManager<T,void,V> :
            public CAbsManagerSelector < T, CPlaceHolder<T,V>*,V>
        {
            public:
                using child_type = CPlaceHolder<T,V>*;

                template <
                    typename _V = V,
                    typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager() :
                    CAbsManagerSelector < T, child_type, V>()
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager(const _V& customData)
                    : CAbsManagerSelector<T, child_type, V>(customData)
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager(_V && customData)
                    : CAbsManagerSelector<T, child_type, V>(std::move(customData))
                {
                }

                CPlaceHolder<T,V>* const &getChildPlaceHolder(size_t index) const override
                {
                    return this->getChild(index);
                }

                void setChild(size_t index, const child_type &child) override
                {
                    this->setChildPlaceHolder(index, child);
                }

        protected:
                CPlaceHolder<T,V>* &getChildPlaceHolderRef(size_t index) override
                {
                    return this->getChildRef(index);
                }
        };

    }
}