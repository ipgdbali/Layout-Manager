#include "../GUI/CWndApp.h"
#include "../GUI/CWndClass.h"
#include "../main/CPlaceHolder.h"
#include "../main/CAbsManager.h"
#include "../main/CLMPadder.h"
#include "../main/CLMAligner.h"
#include "../main/CLMSplitter.h"
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <memory>
#include <strsafe.h>

using namespace ipgdlib::layout;
using namespace ipgdlib::os::window;

CPlaceHolder<size_t>::CAbsBaseManager * pRoot;

class CMyPlaceHolder :
	public CPlaceHolder<size_t>
{
	static size_t counter;
public:
	using Rect = typename CPlaceHolder<size_t>::Rect;

	CMyPlaceHolder() :
		CPlaceHolder<size_t>(), m_Instance(++counter)
	{
	}

	size_t getInstance() const
	{
		return this->m_Instance;
	}
protected:

private:
	size_t m_Instance;
};

size_t CMyPlaceHolder::counter = 0;

void draw(CPlaceHolder<size_t>* pPlaceHolder, PAINTSTRUCT& ps)
{
	if (pPlaceHolder->isManager())
	{
		CPlaceHolder<size_t>::CAbsBaseManager * manager = 
			dynamic_cast<CPlaceHolder<size_t>::CAbsBaseManager*>(pPlaceHolder);
		for (int li = 0; li < manager->getChildCount(); li++)
			draw(manager->getChildPlaceHolder(li), ps);
	}
	else
	{
		RECT r = {
			pPlaceHolder->getRect().left,
			pPlaceHolder->getRect().top,
			pPlaceHolder->getRect().right + 1,
			pPlaceHolder->getRect().bottom + 1
		};

		FillRect(ps.hdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
	}
}

static LRESULT Wndproc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{

		case WM_CREATE:
		{
			pRoot = new CLMVertSplitter<size_t, eSplitterKind::eFixedScaled>(30, 5,
				{
					new CPlaceHolder<size_t>(),
					new CLMVertSplitter<size_t,eSplitterKind::eScaledFixed>(30,5,
						{
							new CLMHorzSplitter<size_t,eSplitterKind::eFixedScaled>(250,5,
								{
									new CPlaceHolder<size_t>(),
									new CLMHorzSplitter<size_t,eSplitterKind::eScaledFixed>(250,5,
										{
											new CPlaceHolder<size_t>(),
											new CPlaceHolder<size_t>()
										})
								}),
							new CPlaceHolder<size_t>()
						})
				});
			return 0;
		}

		case WM_SIZE:
		{
			pRoot->changeRect({ 0,0,(size_t)LOWORD(lParam) - 1,(size_t)HIWORD(lParam) - 1 });
			InvalidateRect(hWnd, NULL, true);
			return 0;
		}break;

		case WM_MOUSEMOVE:
		{
		}break;

		case WM_LBUTTONDOWN:
		{
		}break;

		case WM_LBUTTONUP:
		{
		}break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			draw(pRoot, ps);
			EndPaint(hWnd, &ps);
			return 0;
		}break;

		case WM_DESTROY:
			delete pRoot;
			PostQuitMessage(0);
			return 0;

		default: return DefWindowProc(hWnd, msg, wParam, lParam);
	};
}

int _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	CWndClassLocal wndClass(hInstance, _T("MY_CLASS"), Wndproc);
	CWindow wndMain(wndClass);
	CWndApp myApp(wndMain);

	wndClass.Register((HBRUSH)CreateSolidBrush(0x996b5d));
	wndMain.CreateWindowEx(0, _T("My Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0);
	wndMain.show(nShowCmd);
	return myApp.run();
};