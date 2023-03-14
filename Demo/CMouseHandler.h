#pragma once

#include "../main/CPlaceHolder.h"
#include <Windows.h>

using namespace ipgdlib::layout;

void draw(CPlaceHolder<int>* pPlaceHolder, HDC hdc)
{
	if (pPlaceHolder->isManager())
	{
		CPlaceHolder<int>::CAbsBaseManager* manager =
			dynamic_cast<CPlaceHolder<int>::CAbsBaseManager*>(pPlaceHolder);
		for (int li = 0; li < manager->getChildCount(); li++)
			draw(manager->getChildPlaceHolder(li), hdc);
	}
	else
	{
		dynamic_cast<CPanelAbs<int>*>(pPlaceHolder)->draw(hdc);
	}
}


template <typename T>
class CMouseHandler
{
public:

	CMouseHandler(HWND hWnd, HBRUSH bkgd,typename CPlaceHolder<T>::CAbsBaseManager* pRoot)
		: m_hWnd(hWnd),m_pRoot(pRoot),m_X(0),m_Y(0),m_Background(bkgd)
	{
	}

	bool isLButtonDown() const
	{
		return this->m_pDragPlaceHolder != nullptr;
	}

	CPlaceHolder<T> *getLButtonDownPlaceHolder() const
	{
		return this->m_pDragPlaceHolder;
	}

	void onLButtonDown(T x, T y)
	{
		CPlaceHolder<T>* tmp = findPlaceHolder(x, y);
		this->setLButtonDown(tmp,x,y);

		this->m_pDragPlaceHolder = tmp;
		if (tmp->isManager())
		{
		}
		else
		{
			dynamic_cast<CPanelAbs<T>*>(tmp)->onLButtonDown(m_hWnd, x, y);
		}
	}

	void onLButtonUp(const T &x, const T &y)
	{
		if (this->isLButtonDown())
		{
			CPlaceHolder<T>* tmp = this->getLButtonDownPlaceHolder();
			if (tmp->isManager())
			{
				if (dynamic_cast<CAbsSplitter<T>*>(tmp) != nullptr)
				{
					CAbsSplitter<T>* splitter = dynamic_cast<CAbsSplitter<T>*>(tmp);
					if (splitter->getAffectedAxis() == eAffectedAxis::Horizontal)
					{
						if (splitter->getSplitterKind() == eSplitterKind::eFixedScaled)
							splitter->setSize(splitter->getSize() + (x - m_X));
						else
							splitter->setSize(splitter->getSize() + (m_X - x));
					}
					else
					{
						if (splitter->getSplitterKind() == eSplitterKind::eFixedScaled)
							splitter->setSize(splitter->getSize() + (y - m_Y));
						else
							splitter->setSize(splitter->getSize() + (m_Y - y));
					}

					HDC hdc = GetDC(m_hWnd);
					RECT r = 
					{ 
						tmp->getRect().left,
						tmp->getRect().top,
						tmp->getRect().right,
						tmp->getRect().bottom 
					};
					FillRect(hdc, &r, m_Background);
					draw(tmp,hdc);
					ReleaseDC(m_hWnd,hdc);
				}
			}
			else
			{
				dynamic_cast<CPanelAbs<T>*>(tmp)->onLButtonUp(m_hWnd, x, y);
			}
		}
		this->clearLButtonDown();
	}

	void onMouseMove(T x, T y)
	{
		if (this->isLButtonDown())
		{
			CPlaceHolder<T>* tmp = this->getLButtonDownPlaceHolder();
			if (tmp->isManager())
			{
			}
			else
			{
				dynamic_cast<CPanelAbs<T>*>(tmp)->onMouseMove(m_hWnd, x, y);
			}
		}
	}

protected:
	void setLButtonDown(CPlaceHolder<T> *pPlaceHolder,T x,T y)
	{
		this->m_pDragPlaceHolder = pPlaceHolder;
		this->m_X = x;
		this->m_Y = y;
	}

	void clearLButtonDown()
	{
		this->m_pDragPlaceHolder = nullptr;
	}

	typename CPlaceHolder<T>* findPlaceHolder(T x, T y)
	{
		CPlaceHolder<T>* tmp = m_pRoot;
		bool bFoundPlaceHolder = false;

		while(tmp->isPointInside({ x,y }))
		{
			if (tmp->isManager())
			{
				bFoundPlaceHolder = false;
				typename CPlaceHolder<T>::CAbsBaseManager* tmp2 = dynamic_cast<typename CPlaceHolder<T>::CAbsBaseManager*>(tmp);
				for (size_t li = 0; li < tmp2->getChildCount(); li++)
				{
					if (tmp2->getChildPlaceHolder(li)->isPointInside({ x,y }))
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
	typename CPlaceHolder<T>::CAbsBaseManager* m_pRoot;
	HWND m_hWnd;
	CPlaceHolder<T>* m_pDragPlaceHolder;
	T m_X;
	T m_Y;
	HBRUSH m_Background;
};

