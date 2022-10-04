#include "platform.h"

#include <sqlite3.h>
#include <Richedit.h>

#include "main_wnd.h"

sqlite3* g_bible_db;

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
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;

	rc = sqlite3_open_v2("../data/bible.db", &g_bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(g_bible_db);
		return;
	}

	char* sql = "SELECT * FROM matthew";

	rc = sqlite3_prepare_v2(g_bible_db, sql, -1, &res, 0);

	if (rc == SQLITE_OK)
	{
		sqlite3_bind_int(res, 1, 3);
	}
	else 
	{
		ShowError(L"Unable to select data from matthew!");
		sqlite3_finalize(res);
		sqlite3_close(g_bible_db);
		return;
	}

	while (sqlite3_step(res) == SQLITE_ROW) 
	{
		CHARRANGE cr;
		cr.cpMin = -1;
		cr.cpMax = -1;

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)sqlite3_column_text16(res, 4));
	}

	sqlite3_finalize(res);

	sqlite3_close(g_bible_db);
}