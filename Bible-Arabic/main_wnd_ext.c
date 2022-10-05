#include "platform.h"

#include <sqlite3.h>
#include <Richedit.h>

#include "main_wnd.h"

sqlite3* g_bible_db;
char g_part_name[100];
int g_chapter_idx;
int g_chapter_count;

void LoadPart(MainWindow* mw, const char* part_name);
void LoadChapter(MainWindow* mw, const char* part_name, int idx);

wchar_t* HindiNumbers(wchar_t* str)
{
	size_t len = wcslen(str);

	for (int ix = 0; ix < len; ++ix)
	{
		wchar_t c = str[ix];
		if (c >= L'0' && c <= L'9')
		{
			c -= L'0';
			c += 0x660;

			str[ix] = c;
		}
	}

	return str;
}

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
			LoadPart(mw, "matthew");
	}
}

void LoadPart(MainWindow* mw, const char* part_name)
{
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	char sql[255];
	CHARRANGE cr;
	wchar_t nmbr[20];
	HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;

	strcpy(g_part_name, part_name);
	g_chapter_idx = 1;
	g_chapter_count = 0;

	_itow(g_chapter_idx, nmbr, 10);
	SetWindowText(mw->_lb_chapter_count1->_baseWindow._hWnd, HindiNumbers(nmbr));
	
	_itow(g_chapter_count, nmbr, 10);
	SetWindowText(mw->_lb_chapter_count2->_baseWindow._hWnd, HindiNumbers(nmbr));

	rc = sqlite3_open_v2("../data/bible.db", &g_bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(g_bible_db);
		return;
	}

	strcpy(sql, "SELECT max(chapter) FROM ");
	strcat(sql, part_name);

	rc = sqlite3_prepare_v2(g_bible_db, sql, -1, &res, 0);

	if (rc == SQLITE_OK)
	{
		sqlite3_bind_int(res, 1, 3);
	}
	else
	{
		ShowError(L"Unable to select max chapter!");
		sqlite3_finalize(res);
		sqlite3_close(g_bible_db);
		return;
	}

	if (sqlite3_step(res) == SQLITE_ROW)
	{
		g_chapter_count = sqlite3_column_int(res, 0);
		
		_itow(g_chapter_count, nmbr, 10);
		SetWindowText(mw->_lb_chapter_count2->_baseWindow._hWnd, HindiNumbers(nmbr));
	}

	sqlite3_finalize(res);

	cr.cpMin = 0;
	cr.cpMax = -1;

	SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L"");

	LoadChapter(mw, g_part_name, g_chapter_idx);

	sqlite3_close(g_bible_db);
}

void LoadChapter(MainWindow* mw, const char* part_name, int idx)
{
	HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;
	char buff[20];
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	char sql[255];
	CHARRANGE cr;

	strcpy(sql, "SELECT * FROM ");
	strcat(sql, part_name);
	strcat(sql, " WHERE chapter = ");
	strcat(sql, _itoa(g_chapter_idx, buff, 10));

	rc = sqlite3_prepare_v2(g_bible_db, sql, -1, &res, 0);

	if (rc == SQLITE_OK)
	{
		sqlite3_bind_int(res, 1, 3);
	}
	else
	{
		ShowError(L"Unable to select data!");
		sqlite3_finalize(res);
		sqlite3_close(g_bible_db);
		return;
	}

	while (sqlite3_step(res) == SQLITE_ROW)
	{
		cr.cpMin = -1;
		cr.cpMax = -1;

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)sqlite3_column_text16(res, 4));
	}

	sqlite3_finalize(res);
}