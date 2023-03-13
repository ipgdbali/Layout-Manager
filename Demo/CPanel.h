#pragma once

#include "..\main\CPlaceHolder.h"
#include <Windows.h>

using namespace ipgdlib::layout;

class CPanel :
    public CPlaceHolder<size_t>
{
public:
    CPanel() :
        CPlaceHolder<size_t>(), m_ClientRect({0})
    {
    }

    RECT getClientRect() const
    {
        return this->m_ClientRect;
    }

    void draw(const PAINTSTRUCT& ps)
    {

    }

    protected:
        virtual void drawClient(const PAINTSTRUCT &ps)
        {
            FillRect(ps.hdc, &this->m_ClientRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
        }

    private:
        RECT m_ClientRect;
};

