#pragma once

#include "IPanelManager.h"
#include <Windows.h>

template <typename T>
class CPanelManager :
    public IPanelManager<T>
{

    public:
        ~CPanelManager()
        {
            DeleteObject(this->m_BackGroundBrush);
        }

        CPanelManager(int topSpace,const LOGBRUSH &logBrush) :
            m_TopSpace(topSpace),m_BackGroundBrush(nullptr)
        {
            m_BackGroundBrush = CreateBrushIndirect(&logBrush);
        }

        RECT onCalcClientRect(const ipgdlib::geometry::SRect<T>& r) override
        {
            RECT ret = { (LONG)r.left,(LONG)r.top + m_TopSpace + 1,(LONG)r.right,(LONG)r.bottom };
            return ret;
        }

        void onDrawNonClient(HDC hdc,const RECT& r) override
        {
            FillRect(hdc,&r,this->m_BackGroundBrush);
        }

    protected:

    private:
        HBRUSH m_BackGroundBrush;
        int m_TopSpace;
};

