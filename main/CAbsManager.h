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
            typename U, // child_type
            typename V
        >
        class CAbsManagerTS : // TS -> template Specialization
            public CAbsBasePlaceHolder<T>::CAbsBaseManager,
            public CCustomData<V>
        {
            public:
                using child_type = U;

                template <
                    typename _V = V,
                    typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManagerTS()
                    : CAbsBasePlaceHolder<T>::CAbsBaseManager(), CCustomData<V>()
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManagerTS(const _V& customData)
                    : CAbsBasePlaceHolder<T>::CAbsBaseManager(), CCustomData<V>(customData)
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManagerTS(_V && customData)
                    : CAbsBasePlaceHolder<T>::CAbsBaseManager(), CCustomData<V>(std::move(customData))
                {
                }

                virtual child_type const &getChild(size_t index) const = 0;
                virtual void setChild(size_t index, const child_type &child) = 0;

            protected:
                virtual child_type &getChildRef(size_t index) = 0;

            private:
        };

        template <typename T,typename U = void, typename V = void>
        class CAbsManager :
            public CAbsManagerTS<T, std::pair<U, CAbsBasePlaceHolder<T>*>,V>
        {
        public:
            using child_type = std::pair<U, CAbsBasePlaceHolder<T>*>;

            template <
                typename _V = V,
                typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager() :
                CAbsManagerTS < T, child_type,V>()
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager(const _V& customData)
                : CAbsManagerTS<T, std::pair<U, CAbsBasePlaceHolder<T>* >, V>(customData)
            {
            }

            template <
                typename _V = V,
                typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
            >
            CAbsManager(_V && customData)
                : CAbsManagerTS<T, std::pair<U, CPlaceHolder<T>*>, V>(std::move(customData))
            {
            }

            CAbsBasePlaceHolder<T>* const &getChildPlaceHolder(size_t index) const override
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
            CAbsBasePlaceHolder<T>* &getChildPlaceHolderRef(size_t index) override
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
            public CAbsManagerTS < T, CAbsBasePlaceHolder<T>*,V>
        {
            public:
                using child_type = CAbsBasePlaceHolder<T>*;

                template <
                    typename _V = V,
                    typename std::enable_if< std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager() :
                    CAbsManagerTS < T, child_type, V>()
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager(const _V& customData)
                    : CAbsManagerTS<T, child_type, V>(customData)
                {
                }

                template <
                    typename _V = V,
                    typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
                >
                CAbsManager(_V && customData)
                    : CAbsManagerTS<T, child_type, V>(std::move(customData))
                {
                }

                CAbsBasePlaceHolder<T>* const &getChildPlaceHolder(size_t index) const override
                {
                    return this->getChild(index);
                }

                void setChild(size_t index, const child_type &child) override
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