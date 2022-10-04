#include "platform.h"

#include "main_wnd.h"

void LoadMatthew(MainWindow* mw);

void OnDBClick_treeView(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	TVITEM item;
	TCHAR buffer[128];

	HWND treeViewHWND = mw->_treeView->_baseWindow._hWnd;
	HTREEITEM hSelectedItem = TreeView_GetSelection(treeViewHWND);

	item.hItem = hSelectedItem;
	item.mask = TVIF_TEXT;
	item.cchTextMax = 128;
	item.pszText = buffer;
	if (TreeView_GetItem(treeViewHWND, &item))
	{
		if (wcscmp(item.pszText, L"متى") == 0)
			LoadMatthew(mw);
	}
}

void LoadMatthew(MainWindow* mw)
{
	MessageBox(NULL, L"Matthew", L"", MB_OK);
}