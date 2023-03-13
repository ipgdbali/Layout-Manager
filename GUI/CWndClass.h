#pragma once

#include <Windows.h>
namespace ipgdlib
{
	namespace os
	{
		namespace window
		{

			class IWndClass
			{
			public:
				virtual ~IWndClass() {};
				virtual HINSTANCE getHInstance() const = 0;
				virtual LPCTSTR getClassName() const = 0;
			};

			class CWndClassGlobal :
				virtual public IWndClass
			{
			public:
				CWndClassGlobal(HINSTANCE hInstance, LPCTSTR className) :
					m_hInstance(hInstance), m_ClassName(className)
				{
				}

				HINSTANCE getHInstance() const override
				{
					return this->m_hInstance;
				}

				LPCTSTR getClassName() const override
				{
					return this->m_ClassName;
				}

			private:
				HINSTANCE m_hInstance;
				LPCTSTR m_ClassName;
			};

			class CWndClassLocal :
				virtual public IWndClass
			{
			public:

				virtual ~CWndClassLocal()
				{
					UnregisterClass(m_WC.lpszClassName, m_WC.hInstance);
				}

				CWndClassLocal(HINSTANCE hInstance, LPCTSTR className, WNDPROC wndProc) :
					m_WC({ 0 }), m_Atom(0)
				{
					m_WC.cbSize = sizeof(WNDCLASSEX);
					m_WC.lpszClassName = className;
					m_WC.hInstance = hInstance;
					m_WC.lpfnWndProc = wndProc;
				}

				ATOM Register(
					HBRUSH hbrBackground = (HBRUSH)COLOR_WINDOW + 1,
					UINT style = 0,
					int cbClsExtra = 0,
					int cbWndExtra = 0,
					LPCTSTR lpszMenuName = NULL,
					HCURSOR hCursor = NULL,
					HICON hIcon = NULL,
					HICON hIconSm = NULL
				)
				{
					m_WC.hbrBackground = hbrBackground;
					m_WC.style = style;
					m_WC.cbClsExtra = cbClsExtra;
					m_WC.cbWndExtra = cbWndExtra;
					m_WC.lpszMenuName = lpszMenuName;

					if (m_WC.hCursor == NULL)
						m_WC.hCursor = LoadCursor(NULL, IDC_ARROW);

					if (m_WC.hIcon == NULL)
					{
						if (m_WC.hIconSm == NULL)
							m_WC.hIcon = m_WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
						else
							m_WC.hIcon = m_WC.hIconSm;
					}
					else
					{
						if (m_WC.hIconSm == NULL)
							m_WC.hIconSm = m_WC.hIcon;
					}

					m_Atom = RegisterClassEx(&m_WC);
					return m_Atom;
				}

				HINSTANCE getHInstance() const override
				{
					return m_WC.hInstance;
				}

				LPCTSTR getClassName() const override
				{
					return m_WC.lpszClassName;
				}

				const WNDCLASSEX& getWndClass()
				{
					return this->m_WC;
				}

			private:
				WNDCLASSEX m_WC;
				ATOM m_Atom;
			};

		}
	}
}
