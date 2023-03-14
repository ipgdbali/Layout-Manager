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
    public CDragManager<T, typename CPlaceHolder<T>::CAbsBaseManager >
{

    public:
        CMyDragManager()
            : CDragManager<T, typename CPlaceHolder<T>::CAbsBaseManager>(),m_Size(0)
        {
        }

    protected:

        bool onDragStart(const SPoint<T>& s, typename CPlaceHolder<T>::CAbsBaseManager* pObj) override
        {
        }

        void onDragEnd(const SPoint<T>& s, const SPoint<T>& p) override
        {
        }

        typename CPlaceHolder<T>::CAbsManager* findGroup(typename CPlaceHolder<T>::CAbsManager<U> *pParent,const SPoint<T>& p)
        {
        }

    private:
        T m_Size;

};
