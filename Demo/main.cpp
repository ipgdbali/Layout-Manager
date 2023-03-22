#include "../GUI/CWndApp.h"
#include "../GUI/CWndClass.h"
#include "../main/CPlaceHolder.h"
#include "../main/CAbsManager.h"
#include "../main/CLMPadder.h"
#include "../main/CLMAligner.h"
#include "../main/CLMSplitter.h"
#include "../main/CLMDivider.h"

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <memory>
#include <strsafe.h>
#include "CPanelManager.h"
#include "CPanelAbs.h"
#include "CPanelBar.h"
#include "CPanelTool.h"
#include "CMouseHandler.h"

using namespace ipgdlib::layout;
using namespace ipgdlib::os::window;

#define CLASS_NAME _T("My Class")

CAbsBasePlaceHolder<int>::CAbsBaseManager * pRoot;
CMouseHandler<int> *pMouseHandler;
IPanelManager<int> *CPanelTool<int>::Default = nullptr;


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
			WNDCLASSEX wc;
			GetClassInfoEx(GetModuleHandle(NULL), CLASS_NAME, &wc);
			CPanelTool<int>::Default = new CPanelManager<int>(25,{ BS_SOLID ,RGB(200,200,200)});
			
			pRoot = new CLMSplitterVert<int, eSplitterKind::eFixedScaled>(30, 5,
				{
					new CPanelBar<int>(),
					new CLMSplitterVert<int,eSplitterKind::eScaledFixed>(30,5,
						{
							new CLMPadder<int,bool>(false,{5,0,5,0},
								new CLMSplitterHorz<int,eSplitterKind::eFixedScaled>(250,5,
									{
										new CLMSplitterVert<int,eSplitterKind::eFixedScaled>(250,5,
											{
												new CPanelTool<int>(),
												new CPanelTool<int>()
											}),
										new CLMSplitterHorz<int,eSplitterKind::eScaledFixed>(250,5,
											{
												new CPanelBar<int>(),
												new CLMDividerVert<int>(5,
													{
														{2,new CPanelTool<int>()},
														{3,new CPanelBar<int>()},
														{2,new CPanelTool<int>()}
													})
											})
									})
							),
							new CPanelBar<int>()
						})
				});

			pMouseHandler = new CMouseHandler<int>(hWnd, wc.hbrBackground,pRoot);

			return 0;
		}
		
		case WM_LBUTTONDOWN:
		{
			pMouseHandler->onLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}break;

		case WM_LBUTTONUP:
		{
			pMouseHandler->onLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}break;

		case WM_MOUSEMOVE:
		{
			pMouseHandler->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}break;

		case WM_SIZE:
		{
			pRoot->changeRect({ 0,0,(size_t)LOWORD(lParam) - 1,(size_t)HIWORD(lParam) - 1 });
			InvalidateRect(hWnd, NULL, true);
			return 0;
		}break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			draw(pRoot, ps.hdc);
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
	CWndClassLocal wndClass(hInstance, CLASS_NAME, Wndproc);
	CWindow wndMain(wndClass);
	CWndApp myApp(wndMain);

	wndClass.Register((HBRUSH)CreateSolidBrush(0x996b5d));
	wndMain.CreateWindowEx(0, _T("My Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0);
	wndMain.show(nShowCmd);
	return (int)myApp.run();
};