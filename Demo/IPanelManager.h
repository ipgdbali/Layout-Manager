#pragma once

#include "../Util/Geometry/SRect.h"

template <typename T>
struct IPanelManager
{
	virtual ~IPanelManager() {};
	virtual RECT onCalcClientRect(const ipgdlib::geometry::SRect<T> &r) = 0;
	virtual void onDrawNonClient(HDC hdc,const RECT& r) = 0;
};

