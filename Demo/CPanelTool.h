#pragma once
#include "CPanelAbs.h"

template <typename T>
class CPanelTool :
	public CPanelAbs<T>
{
public:
	using Rect = ipgdlib::geometry::SRect<T>;
	using Point = ipgdlib::geometry::SPoint<T>;

	static IPanelManager<T>* Default;

	using Rect = ipgdlib::geometry::SRect<T>;

	void draw(HDC hdc) override
	{
		Default->onDrawNonClient(hdc, this->getRect());
		this->onDrawClient(hdc);
	}

	void onLButtonDown(HWND hWnd, Point pos) override
	{
	}

	void onLButtonUp(HWND hWnd, Point pos) override
	{

	}

	void onMouseMove(HWND hWnd, Point pos) override
	{
	}

protected:
	virtual void onDrawClient(HDC hdc)
	{
		RECT r = this->getClientRect();
		FillRect(hdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//DrawFrameControl(hdc, &r, DFC_CAPTION, DFCS_CAPTIONCLOSE);
	}

	void onChangeRect(Rect& r, Rect && nr) override
	{
		CPanelAbs<T>::onChangeRect(r, std::move(nr));
		this->setClientRect(Default->onCalcClientRect(nr));
	}

};

