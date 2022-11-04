#include "platform.h"


#include "main_wnd.h"

void OnBtnClicked_read(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	MessageBox(mw->_baseWindow._hWnd, L"Experimental", L"Experimental", MB_OK);
}
