#include "platform.h"

#include <sqlite3.h>
#include <Richedit.h>

#include "main_wnd.h"

#define DB_URL "../data/bible.db"
char g_part_name[100];
int g_chapter_idx = 0;
int g_chapter_count = 0;

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
		if (wcscmp(item.pszText, L"تكوين") == 0)
			LoadPart(mw, "genesis"); 
		else if (wcscmp(item.pszText, L"متى") == 0)
			LoadPart(mw, "matthew");
		else if (wcscmp(item.pszText, L"مرقس") == 0)
			LoadPart(mw, "mark");
	}
}

void LoadPart(MainWindow* mw, const char* part_name)
{
	sqlite3* bible_db;
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

	rc = sqlite3_open_v2(DB_URL, &bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(bible_db);
		return;
	}

	strcpy(sql, "SELECT max(chapter) FROM ");
	strcat(sql, part_name);

	rc = sqlite3_prepare_v2(bible_db, sql, -1, &res, 0);

	if (rc != SQLITE_OK)
	{
		ShowError(L"Unable to select max chapter!");
		sqlite3_finalize(res);
		sqlite3_close(bible_db);
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

	sqlite3_close(bible_db);

	LoadChapter(mw, g_part_name, g_chapter_idx);
}

void LoadChapter(MainWindow* mw, const char* part_name, int idx)
{
	HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;
	sqlite3* bible_db;
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

	rc = sqlite3_open_v2(DB_URL, &bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(bible_db);
		return;
	}

	rc = sqlite3_prepare_v2(bible_db, sql, -1, &res, 0);

	if (rc != SQLITE_OK)
	{
		ShowError(L"Unable to select data!");
		sqlite3_finalize(res);
		sqlite3_close(bible_db);
		return;
	}

	while (sqlite3_step(res) == SQLITE_ROW)
	{
		const wchar_t* prefix = sqlite3_column_text16(res, 2);
		const wchar_t* suffix = sqlite3_column_text16(res, 3);
		const wchar_t* verse = sqlite3_column_text16(res, 1);
		const wchar_t* body = sqlite3_column_text16(res, 4);
		wchar_t number[20];

		wcscpy(number, verse);
		
		cr.cpMin = -1;
		cr.cpMax = -1;

		if (prefix)
		{
			SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
			SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)prefix);
		}

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)HindiNumbers(number));

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L" ");

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)body);

		if (suffix)
		{
			SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
			SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)suffix);
		}
	}

	sqlite3_finalize(res);
	sqlite3_close(bible_db);
}

void OnBtnClicked_next_chapter(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	if (g_chapter_idx < g_chapter_count)
	{
		HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd; 
		CHARRANGE cr;
		wchar_t nmbr[20];

		cr.cpMin = 0;
		cr.cpMax = -1;

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L"");

		_itow(++g_chapter_idx, nmbr, 10);
		SetWindowText(mw->_lb_chapter_count1->_baseWindow._hWnd, HindiNumbers(nmbr));

		LoadChapter(mw, g_part_name, g_chapter_idx);
	}
}

void OnBtnClicked_prev_chapter(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	if (g_chapter_idx > 1)
	{
		HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;
		CHARRANGE cr;
		wchar_t nmbr[20];

		cr.cpMin = 0;
		cr.cpMax = -1;

		SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
		SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L"");

		_itow(--g_chapter_idx, nmbr, 10);
		SetWindowText(mw->_lb_chapter_count1->_baseWindow._hWnd, HindiNumbers(nmbr));

		LoadChapter(mw, g_part_name, g_chapter_idx);
	}
}
#include <locale.h>
void OnBtnClicked_search(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	sqlite3* bible_db;
	wchar_t wtext[100];
	char text[200];
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	char sql[255];
	_locale_t loc;
	const char* table = "matthew";
	
	GetWindowText(mw->_tx_search->_baseWindow._hWnd, wtext, 100);
	
	if (wcslen(wtext) <= 0)
		return;

	loc = _wcreate_locale(LC_ALL, L"ar_SY.utf8"); 
	_wcstombs_l(text, wtext, 100, loc);
	_free_locale(loc);

	strcpy(sql, "SELECT * FROM ");
	strcat(sql, table);
	strcat(sql, " WHERE ");
	strcat(sql, table);
	strcat(sql, " MATCH \"");
	strcat(sql, text);
	strcat(sql, "\"");

	rc = sqlite3_open_v2(DB_URL, &bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(bible_db);
		return;
	}

	rc = sqlite3_prepare_v2(bible_db, sql, -1, &res, 0);

	if (rc != SQLITE_OK)
	{
		ShowError(L"Unable to select data!");
		sqlite3_finalize(res);
		sqlite3_close(bible_db);
		return;
	}

	while (sqlite3_step(res) == SQLITE_ROW)
	{
		MessageBox(NULL, sqlite3_column_text16(res, 4), L"Hi", MB_OK);
	}

	sqlite3_finalize(res);
	sqlite3_close(bible_db);
}
