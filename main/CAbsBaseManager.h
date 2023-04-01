#pragma once

#include "CAbsBasePlaceHolder.h"
#include "../Util/CAbsAutoReCalculate.h"
#include "../Util/Container/IContainerKind.h"
#include "../Util/iface/IAffectedAxis.h"
#include "../Util/Mouse/IDragable.h"
#include <vector>

namespace ipgdlib
{
	namespace layout
	{

        using namespace ipgdlib::container;

        template <typename T>
        class CAbsBasePlaceHolder<T>::CAbsBaseManager :
            public CAbsBasePlaceHolder<T>,
            public CAbsAutoReCalculate,
            public CIndexedChild::CIndexedChildMutator,
            virtual public ipgdlib::os::IDragable,
            public IContainerKind,
            public IAffectedAxis
        {

        public:
            using Rect = CAbsBasePlaceHolder<T>::Rect;
            using Point = CAbsBasePlaceHolder<T>::Point;

            CAbsBaseManager() :
                CAbsBasePlaceHolder<T>(), 
                CAbsAutoReCalculate(),
                CIndexedChild::CIndexedChildMutator()
            {
            }

            bool isManager() const override final
            {
                return true;
            }

            size_t getChildIndexFromPoint(const Point& p) const
            {
                for (size_t li = 0; li < this->getChildCount(); li++)
                    if (this->getChildPlaceHolder(li)->getRect().isPointInside(p))
                        return li;

                return (size_t)-1;
            }

            virtual size_t getChildCount() const = 0;

            virtual CAbsBasePlaceHolder<T>* const & getChildPlaceHolder(size_t index) const = 0;

            virtual void setChildPlaceHolder(size_t index, CAbsBasePlaceHolder<T>* const pChildPlaceHolder){

                if (pChildPlaceHolder)
                {

                    CAbsBasePlaceHolder<T>* &pInternal = this->getChildPlaceHolderRef(index);
                    if (pInternal != nullptr)
                    {
                        clearChildParent(pInternal);
                        pChildPlaceHolder->changeRect(pInternal->getRect());
                    }
                    pInternal = pChildPlaceHolder;
                    setChildParent(pInternal);
                
                }
            }

        protected:
            virtual CAbsBasePlaceHolder<T>* &getChildPlaceHolderRef(size_t index) = 0;

            void onChangeRect(Rect & oRect, Rect && nRect) override
            {
                CAbsBasePlaceHolder<T>::onChangeRect(oRect, std::move(nRect));
                this->reCalculate();
            }

            void clearChildParent(CAbsBasePlaceHolder<T>* pChildPlaceHolder)
            {
                pChildPlaceHolder->setParent(nullptr);
            }

            void setChildParent(CAbsBasePlaceHolder<T>* pChildPlaceHolder)
            {
                pChildPlaceHolder->setParent(this);
            }

        private:

        };

	}
}