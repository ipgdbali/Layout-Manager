#pragma once

#include <Windows.h>
#include "CWndClass.h"
#include "CWindow.h"

namespace ipgdlib
{
    namespace os
    {
        namespace window
        {

            class CWndApp
            {

            public:

                CWndApp(CWindow& wnd) :
                    m_Window(wnd)
                {
                }

                virtual WPARAM run()
                {
                    MSG msg = { 0 };
                    BOOL bRet;

                    while (bRet = GetMessage(&msg, 0, 0, 0) != 0)
                    {
                        if (bRet == -1)
                        {
                        }
                        else
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                    return msg.wParam;
                }

            private:
                CWindow& m_Window;
            };


        }
    }
}
