#pragma once

#include "..\GUI\CDragManager.h"
#include "..\main\CPlaceHolder.h"
#include "..\main\CLMSplitter.h"
#include <Windows.h>

using namespace ipgdlib::os;
using namespace ipgdlib::layout;
using namespace ipgdlib::geometry;

template <typename T>
class CMyDragManager :
    public CDragManager<T, typename CPlaceHolder<T>::CAbsManager<U> >
{

    public:
        CMyDragManager()
            : CDragManager<T, typename CPlaceHolder<T>::CAbsManager<U>>(),m_Size(0)
        {
        }

    protected:

        bool onDragStart(const SPoint<T>& s, typename CPlaceHolder<T>::CAbsManager<U>* pObj) override
        {
            pObj = findGroup(pObj, s);
            if (pObj)
            {
                this->m_Size = dynamic_cast<CAbsSplitter<T>*>(pObj)->getSize();
                return CDragManager<T, typename CPlaceHolder<T>::CAbsManager<U>>::onDragStart(s, pObj);
            }
            else
                return false;
        }

        void onDragEnd(const SPoint<T>& s, const SPoint<T>& p) override
        {
            switch (this->getObj()->getAxis())
            {
                case eAxis::Horizontal:
                {
                    if (dynamic_cast<CAbsSplitter<T>*>(this->getObj())->getSplitterKind() == eSplitterKind::eFixedScaled)
                        dynamic_cast<CAbsSplitter<T>*>(this->getObj())->setSize(this->m_Size + p.x - s.x);
                    else
                        dynamic_cast<CAbsSplitter<T>*>(this->getObj())->setSize(this->m_Size + s.x - p.x);

                }break;

                case eAxis::Vertical:
                {
                    if (dynamic_cast<CAbsSplitter<T>*>(this->getObj())->getSplitterKind() == eSplitterKind::eFixedScaled)
                        dynamic_cast<CAbsSplitter<T>*>(this->getObj())->setSize(this->m_Size + p.y - s.y);
                    else
                        dynamic_cast<CAbsSplitter<T>*>(this->getObj())->setSize(this->m_Size + s.y - p.y);

                }break;

            }
        }

        bool isSupported(typename CPlaceHolder<T>::CAbsManager<U>* pGroup)
        {
            return (dynamic_cast<CAbsSplitter<T>*>(pGroup)) ? true : false;
        }

        typename CPlaceHolder<T>::CAbsManager<U>* findGroup(typename CPlaceHolder<T>::CAbsManager<U> *pParent,const SPoint<T>& p)
        {
            typename CPlaceHolder<T>::CAbsManager<U>* pRet = nullptr;

            CPlaceHolder<T>* pChild = pParent->getChildPlaceHolderFromPoint(p);
            if (pChild == nullptr)
            {
                if (isSupported(pParent))
                    return pParent;
                else
                    return nullptr;
            }

            while(pChild)
            {
                if (pChild->isManager())
                {
                    pParent = pChild->asGroup();
                    pChild = pParent->getChildPlaceHolderFromPoint(p);
                    pRet = pParent;
                }
                else
                    break;
            }
            if (isSupported(pParent))
                return pRet;
            else
                return nullptr;
        }

    private:
        T m_Size;

};
