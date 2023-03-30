#include "../Util/Win32/CWndApp.h"
#include "../Util/Win32/CWndClass.h"
#include <Windows.h>
#include <tchar.h>

using namespace ipgdlib::os::window;

static LRESULT Wndproc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{

		case WM_DESTROY:
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

	wndClass.Register((HBRUSH)COLOR_WINDOWTEXT + 1);
	wndMain.CreateWindowEx(0, _T("My Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0);
	wndMain.show(nShowCmd);
	return (int)myApp.run();

};