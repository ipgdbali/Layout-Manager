#pragma once


#include "CPanelAbs.h"


template <typename T>
class CPanelBar :
	public CPanelAbs<T>
{
public:
	using Rect = ipgdlib::geometry::SRect<T>;

	void draw(HDC hdc) override
	{
		FillRect(hdc, &this->getClientRect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
	}

	void onLButtonDown(HWND hWnd,const T& x, const T& y) override
	{
		HDC dc = GetDC(hWnd);
		FillRect(dc, &this->getClientRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
		ReleaseDC(hWnd,dc);
	}

	void onLButtonUp(HWND hWnd,const T& x, const T& y) override
	{
		HDC dc = GetDC(hWnd);
		FillRect(dc, &this->getClientRect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
		ReleaseDC(hWnd, dc);
	}

	void onMouseMove(HWND hWnd, const T& x, const T& y) override
	{
	}

	void onChangeRect(Rect& r, Rect && nr) override
	{
		CPanelAbs<T>::onChangeRect(r, std::move(nr));
		this->setClientRect(nr);
	}
};

