#pragma once

#include <Windows.h>
#include "CWndClass.h"

namespace ipgdlib
{
	namespace os
	{
		namespace window
		{

			class CWindow
			{

			public:
				CWindow(IWndClass& wndClass) :
					m_hWnd(NULL), m_WndClass(wndClass)
				{
				}

				HWND CreateWindowEx(
					DWORD     dwExStyle,
					LPCTSTR    lpWindowName,
					DWORD     dwStyle,
					int       X,
					int       Y,
					int       nWidth,
					int       nHeight,
					HWND      hWndParent,
					HMENU     hMenu,
					LPVOID    lpParam
				)
				{
					this->m_hWnd = ::CreateWindowEx(dwExStyle, m_WndClass.getClassName(), lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, m_WndClass.getHInstance(), lpParam);
					return this->m_hWnd;
				};

				bool isNull() const
				{
					return this->m_hWnd == NULL;
				}

				void show(int nCmdShow)
				{
					::ShowWindow(this->m_hWnd, nCmdShow);
				}

				void DestroyWindow()
				{
					if (this->m_hWnd != NULL)
					{
						::DestroyWindow(this->m_hWnd);
						this->m_hWnd = NULL;
					}
				}

			private:
				HWND m_hWnd;
				IWndClass& m_WndClass;

			};


		}
	}
}
