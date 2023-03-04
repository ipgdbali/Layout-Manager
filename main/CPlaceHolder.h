#pragma once

#include "./../Geometry/SRect.h"
#include "../Util/CAbsAutoReCalculate.h"
#include <vector>

namespace ipgdlib
{
    namespace layout
    {

        template <typename T>
        class CPlaceHolder        
        {

        public:
            using Rect = ipgdlib::geometry::SRect<T>;
            using Point = ipgdlib::geometry::SPoint<T>;

            class CAbsBaseManager;

            CPlaceHolder() :
                m_Rect({ 0 }), m_Parent(nullptr)
            {
            }

            bool isPointInside(const Point& p) const
            {
                this->m_Rect.isPointInRect(p);
            }

            virtual bool isManager() const
            {
                return false;
            }

            const Rect &getRect() const
            {
                return this->m_Rect;
            }

            void changeRect(const Rect& r)
            {
                this->onChangeRect(this->m_Rect, r);
            }

            bool hasParent() const
            {
                return this->m_Parent != nullptr;
            }

            CAbsBaseManager* const &getParent() const
            {
                return this->m_Parent;
            }

        protected:
            virtual void onChangeRect(Rect& r, const Rect& nr)
            {
                r = nr;
            }

            void setParent(CAbsBaseManager *const parent)
            {
                this->m_Parent = parent;
            }

        private:
            Rect m_Rect;
            CAbsBaseManager *m_Parent;

        };

        template <typename T>
        class CPlaceHolder<T>::CAbsBaseManager :
            public CPlaceHolder<T>,
            public ipgdlib::util::CAbsAutoReCalculate
        {
        public:
            using Rect = CPlaceHolder<T>::Rect;
            using Point = CPlaceHolder<T>::Point;

            CAbsBaseManager() :
                CPlaceHolder<T>(),CAbsAutoReCalculate()
            {
            }

            bool isManager() const override
            {
                return true;
            }

            size_t getChildIndexFromPoint(const Point& p) const
            {
                for (size_t li = 0; li < this->getChildCount(); li++)
                    if (this->getChildPlaceHolder(li)->getRect().isPointInRect(p))
                        return li;

                return (size_t)-1;
            }

            virtual size_t getChildCount() const = 0;

            virtual CPlaceHolder<T> *const &getChildPlaceHolder(size_t index) const = 0;
            
            virtual void setChildPlaceHolder(size_t index, CPlaceHolder<T>* const pPlaceHolder)
            {
                if (pPlaceHolder)
                {
                    CPlaceHolder<T>* &pInternal = this->getChildPlaceHolderRef(index);
                    if (pInternal != nullptr)
                    {
                        clearChildParent(pInternal);
                        pPlaceHolder->changeRect(pInternal->getRect());
                    }
                    pInternal = pPlaceHolder;
                    setChildParent(pInternal);
                }
            }

            bool setChildPlaceHolders(const std::vector<CPlaceHolder<T>*> &pPlaceHolders)
            {
                if (pPlaceHolders->size() == this->getChildCount())
                {
                    for (size_t li = 0; li < this->getChildCount(); li++)
                        this->setChildPlaceHolder(li, pPlaceHolders[li]);
                    return true;
                }
                else
                    return false;
            }

        protected:
            virtual CPlaceHolder<T>* &getChildPlaceHolderRef(size_t index) = 0;

            void onChangeRect(Rect& oRect, const Rect& nRect) override
            {
                CPlaceHolder<T>::onChangeRect(oRect, nRect);
                this->reCalculate();
            }

        private:
            void clearChildParent(CPlaceHolder<T>* pPlaceHolder)
            {
                pPlaceHolder->setParent(nullptr);
            }

            void setChildParent(CPlaceHolder<T>* pPlaceHolder)
            {
                pPlaceHolder->setParent(this);
            }

        };

    };
};