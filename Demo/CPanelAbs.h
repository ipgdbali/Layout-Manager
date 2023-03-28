#pragma once

#include "..\main\CPlaceHolder.h"
#include <Windows.h>
#include "IPanelManager.h"

using namespace ipgdlib::layout;

template <typename T>
class CPanelAbs :
    public CPlaceHolder<T>
{
public:
    using Rect = ipgdlib::geometry::SRect<T>;
    using Point = ipgdlib::geometry::SPoint<T>;

    CPanelAbs() :
        CPlaceHolder<T>(), m_ClientRect({0})
    {
    }

    const RECT &getClientRect() const
    {
        return this->m_ClientRect;
    }

    virtual void draw(HDC hdc) = 0;
    virtual void onLButtonDown(HWND hWnd,Point pos) = 0;
    virtual void onLButtonUp(HWND hWnd, Point pos) = 0;
    virtual void onMouseMove(HWND hWnd, Point pos) = 0;

protected:
    void setClientRect(const RECT& r)
    {
        this->m_ClientRect = r;
    }
    private:
        RECT m_ClientRect;
};

