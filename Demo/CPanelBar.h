#pragma once


#include "CPanelAbs.h"


template <typename T>
class CPanelBar :
	public CPanelAbs<T>
{
public:
	using Rect = ipgdlib::geometry::SRect<T>;
	using Point = ipgdlib::geometry::SPoint<T>;

	void draw(HDC hdc) override
	{
		FillRect(hdc, &this->getClientRect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
	}

	void onLButtonDown(HWND hWnd,Point pos) override
	{
		HDC dc = GetDC(hWnd);
		FillRect(dc, &this->getClientRect(), (HBRUSH)GetStockObject(BLACK_BRUSH));
		ReleaseDC(hWnd,dc);
	}

	void onLButtonUp(HWND hWnd,Point pos) override
	{
		HDC dc = GetDC(hWnd);
		FillRect(dc, &this->getClientRect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
		ReleaseDC(hWnd, dc);
	}

	void onMouseMove(HWND hWnd, Point pos) override
	{
	}

	void onChangeRect(Rect& r, Rect && nr) override
	{
		CPanelAbs<T>::onChangeRect(r, std::move(nr));
		this->setClientRect(nr);
	}
};

