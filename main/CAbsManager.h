#pragma once

#include "CPlaceHolder.h"
#include <utility>

namespace ipgdlib
{
    namespace layout
    {

        template <typename T,typename U,typename V>
        class CAbsManagerSelector :
            public CPlaceHolder<T,V>::CAbsBaseManager
        {
        public:
            using child_type = U;
            CAbsManagerSelector() :
                CPlaceHolder<T, V>::CAbsBaseManager()
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
            public CAbsManagerSelector<T, std::pair<U, CPlaceHolder<T>*>,V>
        {
        public:
            using child_type = std::pair<U, CPlaceHolder<T>*>;

            CAbsManager() :
                CAbsManagerSelector < T, child_type,V>()
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
            public CAbsManagerSelector < T, CPlaceHolder<T>*,V>
        {
            public:
                using child_type = CPlaceHolder<T,V>*;

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