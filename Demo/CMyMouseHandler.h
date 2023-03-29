#pragma once

#include "../main/CPlaceHolder.h"
#include "../GUI/Mouse/CMouseHandler.h"
#include <Windows.h>

using namespace ipgdlib::layout;
using namespace ipgdlib::os;

void draw(HDC hdc, CAbsBasePlaceHolder<int>* pPlaceHolder)
{
	if (pPlaceHolder->isManager())
	{
		CAbsBasePlaceHolder<int>::CAbsBaseManager* manager =
			dynamic_cast<CAbsBasePlaceHolder<int>::CAbsBaseManager*>(pPlaceHolder);
		for (int li = 0; li < manager->getChildCount(); li++)
			draw(hdc,manager->getChildPlaceHolder(li));
	}
	else
	{
		dynamic_cast<CPanelAbs<int>*>(pPlaceHolder)->draw(hdc);
	}
}

void DrawXorBar(HDC hdc, int x1, int y1, int width, int height)
{
	static WORD _dotPatternBmp[8] = { 0x00aa, 0x0055, 0x00aa, 0x0055,
									  0x00aa, 0x0055, 0x00aa, 0x0055 };

	HBITMAP hbm;
	HBRUSH hbr, hbrushOld;

	/* create a monochrome checkered pattern */
	hbm = CreateBitmap(8, 8, 1, 1, _dotPatternBmp);
	hbr = CreatePatternBrush(hbm);

	SetBrushOrgEx(hdc, x1, y1, 0);
	hbrushOld = (HBRUSH)SelectObject(hdc, hbr);

	/* draw the checkered rectangle to the screen */
	PatBlt(hdc, x1, y1, width, height, PATINVERT);

	SelectObject(hdc, hbrushOld);
	DeleteObject(hbr);
	DeleteObject(hbm);
}

template <typename T>
struct SDragItem
{

	CAbsBasePlaceHolder<T> *pPlaceHolder;
	HDC hdc;

	void clear()
	{
		pPlaceHolder = NULL;
		hdc = NULL;
	}
};

template <typename T>
class CMyMouseHandler :
	CMouseHandler<T,SDragItem<T>>
{
public:

	CMyMouseHandler(
		HWND hWnd, 
		HBRUSH bkgd,
		typename CAbsBasePlaceHolder<T>::CAbsBaseManager* pRoot
	) : 
		CMouseHandler<T, SDragItem<T>>({ 0 }, {}),
		m_hWnd(hWnd),
		m_pRoot(pRoot),
		m_Background(bkgd)
	{
	}

	void onLButtonDown(SPoint<T> pos) override
	{
		CMouseHandler<T,SDragItem<T>>::onLButtonDown(std::move(pos));
		CAbsBasePlaceHolder<T>* tmp = findPlaceHolder(pos);

		this->getDragItemRef().pPlaceHolder = tmp;

		if (tmp->isManager())
		{
			this->getDragItemRef().hdc = GetDC(m_hWnd);
		}
		else
		{
			dynamic_cast<CPanelAbs<T>*>(tmp)->onLButtonDown(m_hWnd, pos);
		}
	}

	void onLButtonUp(SPoint<T> pos) override
	{
		if (this->isLButtonDown())
		{
			CAbsBasePlaceHolder<T>* tmp = this->getDragItemRef().pPlaceHolder;
			if (tmp->isManager())
			{
				if (dynamic_cast<CAbsSplitter<T>*>(tmp) != nullptr)
				{
					CAbsSplitter<T>* splitter = dynamic_cast<CAbsSplitter<T>*>(tmp);
					if (splitter->getAffectedAxis() == eAffectedAxis::Horizontal)
					{
						if (splitter->getSplitterKind() == eSplitterKind::eFixedScaled)
							splitter->setSize(splitter->getSize() + (pos.x - this->getLButtonDownPosition().x));
						else
							splitter->setSize(splitter->getSize() + (this->getLButtonDownPosition().x - pos.x));
					}
					else
					{
						if (splitter->getSplitterKind() == eSplitterKind::eFixedScaled)
							splitter->setSize(splitter->getSize() + (pos.y - this->getLButtonDownPosition().y));
						else
							splitter->setSize(splitter->getSize() + (this->getLButtonDownPosition().y - pos.y));
					}

					RECT r = 
					{ 
						tmp->getRect().left,
						tmp->getRect().top,
						tmp->getRect().right,
						tmp->getRect().bottom 
					};

					HDC hdc = this->getDragItemRef().hdc;
					FillRect(hdc, &r, this->m_Background);
					draw(hdc,tmp);
					ReleaseDC(this->m_hWnd, this->getDragItemRef().hdc);
					this->getDragItemRef().clear();
				}
			}
			else
			{
				dynamic_cast<CPanelAbs<T>*>(tmp)->onLButtonUp(m_hWnd, pos);
			}
		}
		CMouseHandler<T,SDragItem<T>>::onLButtonUp(std::move(pos));
	}

	void onMouseMove(SPoint<T> pos) override
	{
		if (this->isLButtonDown())
		{
			CAbsBasePlaceHolder<T>* tmp = this->getDragItemRef().pPlaceHolder;
			if (tmp->isManager())
			{

			}
			else
			{
				dynamic_cast<CPanelAbs<T>*>(tmp)->onMouseMove(m_hWnd, pos);
			}
		}
	}

protected:

	typename CAbsBasePlaceHolder<T>* findPlaceHolder(SPoint<T> pos)
	{
		CAbsBasePlaceHolder<T>* tmp = m_pRoot;
		bool bFoundPlaceHolder = false;

		while(tmp->isPointInside(pos))
		{
			if (tmp->isManager())
			{
				bFoundPlaceHolder = false;
				typename CAbsBasePlaceHolder<T>::CAbsBaseManager* tmp2 = dynamic_cast<typename CAbsBasePlaceHolder<T>::CAbsBaseManager*>(tmp);
				for (size_t li = 0; li < tmp2->getChildCount(); li++)
				{
					if (tmp2->getChildPlaceHolder(li)->isPointInside(pos))
					{
						tmp = tmp2->getChildPlaceHolder(li);
						bFoundPlaceHolder = true;
						break;
					}
				}

				if (!bFoundPlaceHolder)
					break;
			}
			else
			{
				break;
			}
		}
		return tmp;
	}

private:


	typename CAbsBasePlaceHolder<T>::CAbsBaseManager* m_pRoot;
	HWND m_hWnd;
	HBRUSH m_Background;

};

