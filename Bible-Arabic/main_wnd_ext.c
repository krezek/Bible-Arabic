#include "platform.h"

#include <sqlite3.h>
#include <Richedit.h>

#include "main_wnd.h"

struct Testament OldTestament[OT_COUNT] =
{
	{ "genesis", L"التكوين" },
	{ "exodus", L"الخروج" },
	{ "leviticus", L"اللاويين" },
	{ "numbers", L"العدد" },
	{ "deuteronomy", L"التثنية" },
	{ "joshua", L"يشوع" },
	{ "judges", L"القضاة"},
	{ "ruth", L"راعوث" },
	{ "samuel_1", L"صموئيل الأول" },
	{ "samuel_2", L"صموئيل الثاني" }
};

struct Testament NewTestament[NT_COUNT] =
{
	{ "matthew", L"متى" },
	{ "mark", L"مرقس" },
	{ "luke", L"لوقا" },
	{ "john", L"يوحنا" },
	{ "acts", L"أعمال الرسل" },
	{ "romans", L"رومية" }
};

//#define DB_URL "\\Windows\\System32\\bible.db"
#define DB_URL "..\\data\\bible.db"
char g_part_name[100];
int g_chapter_idx = 0;
int g_chapter_count = 0;

void LoadPart(MainWindow* mw, const char* part_name);
void LoadChapter(MainWindow* mw, const char* part_name, int idx);

void remove_marks(sqlite3_context* context, int argc, sqlite3_value** argv);

wchar_t* HindiNumbers(wchar_t* str)
{
	size_t len = wcslen(str);

	for (size_t ix = 0; ix < len; ++ix)
	{
		wchar_t c = str[ix];
		if (c >= L'0' && c <= L'9')
		{
			c -= L'0';
			c += 0x0660;

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
		for (int ix = 0; ix < sizeof(OldTestament) / sizeof(OldTestament[0]); ++ix)
		{
			if (wcscmp(item.pszText, OldTestament[ix].table_arabic) == 0)
			{
				LoadPart(mw, OldTestament[ix].table_english);
				LoadChapter(mw, g_part_name, 1);
				return;
			}
		}

		for (int ix = 0; ix < sizeof(NewTestament) / sizeof(NewTestament[0]); ++ix)
		{
			if (wcscmp(item.pszText, NewTestament[ix].table_arabic) == 0)
			{
				LoadPart(mw, NewTestament[ix].table_english);
				LoadChapter(mw, g_part_name, 1);
				return;
			}
		}
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
	g_chapter_idx = 0;
	g_chapter_count = 0;

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
		SetWindowText(mw->_lb_chapter_count->_baseWindow._hWnd, HindiNumbers(nmbr));
	}

	sqlite3_finalize(res);

	cr.cpMin = 0;
	cr.cpMax = -1;

	SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L"");

	sqlite3_close(bible_db);
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
	wchar_t nmbr[20];

	cr.cpMin = 0;
	cr.cpMax = -1;

	SendMessage(richTextHWND, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(richTextHWND, EM_REPLACESEL, 0, (LPARAM)L"");

	g_chapter_idx = idx;

	_itow(g_chapter_idx, nmbr, 10);
	SetWindowText(mw->_tx_chapter_idx->_baseWindow._hWnd, HindiNumbers(nmbr));

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
		wchar_t nmbr[20];

		_itow(++g_chapter_idx, nmbr, 10);
		SetWindowText(mw->_tx_chapter_idx->_baseWindow._hWnd, HindiNumbers(nmbr));

		LoadChapter(mw, g_part_name, g_chapter_idx);
	}
}

void OnBtnClicked_prev_chapter(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	if (g_chapter_idx > 1)
	{
		HWND richTextHWND = mw->_richEdit->_baseWindow._hWnd;
		wchar_t nmbr[20];

		_itow(--g_chapter_idx, nmbr, 10);
		SetWindowText(mw->_tx_chapter_idx->_baseWindow._hWnd, HindiNumbers(nmbr));

		LoadChapter(mw, g_part_name, g_chapter_idx);
	}
}

wchar_t* get_table_arabic_name(const char* table)
{
	for (int ix = 0; ix < sizeof(OldTestament) / sizeof(OldTestament[0]); ++ix)
	{
		if (strcmp(table ,OldTestament[ix].table_english) == 0)
		{
			return OldTestament[ix].table_arabic;
		}
	}

	for (int ix = 0; ix < sizeof(NewTestament) / sizeof(NewTestament[0]); ++ix)
	{
		if (strcmp(table, NewTestament[ix].table_english) == 0)
		{
			return NewTestament[ix].table_arabic;
		}
	}
	
	return L"";
}

void search(MainWindow* mw, WPARAM wParam, LPARAM lParam, const char* table, const char* text)
{
	sqlite3* bible_db;
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	char sql[255];
	
	strcpy(sql, "SELECT * FROM ");
	strcat(sql, table);
	strcat(sql, " WHERE remove_marks(body) like remove_marks(\'%");
	strcat(sql, text);
	strcat(sql, "%\')");

	rc = sqlite3_open_v2(DB_URL, &bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		ShowError(L"Can't open database file!");
		sqlite3_close(bible_db);
		return;
	}

	if (sqlite3_create_function(bible_db, "remove_marks", 1, SQLITE_UTF8, NULL, &remove_marks, NULL, NULL) != SQLITE_OK)
	{
		ShowError(L"Unable to create db function remove_marks!");
		sqlite3_close(bible_db);
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
		wchar_t buff[100];
		LV_ITEM lvI;

		wcscpy(buff, get_table_arabic_name(table));
		wcscat(buff, L" ");
		wcscat(buff, sqlite3_column_text16(res, 0));
		wcscat(buff, L"/");
		wcscat(buff, sqlite3_column_text16(res, 1));


		lvI.mask = LVIF_TEXT;
		lvI.state = 0;
		lvI.stateMask = 0;

		lvI.iItem = 0;
		lvI.iSubItem = 0;
		lvI.pszText = LPSTR_TEXTCALLBACK;
		lvI.cchTextMax = 200;

		ListView_InsertItem(mw->_lv_result->_baseWindow._hWnd, &lvI);

		ListView_SetItemText(mw->_lv_result->_baseWindow._hWnd,
			0,
			0,
			HindiNumbers(buff));

		ListView_SetItemText(mw->_lv_result->_baseWindow._hWnd,
			0,
			1,
			(wchar_t*)sqlite3_column_text16(res, 4));
	}

	sqlite3_finalize(res);
	sqlite3_close(bible_db);
}

void OnBtnClicked_search(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	_locale_t loc;
	wchar_t wtext[100];
	char text[200];

	ListView_DeleteAllItems(mw->_lv_result->_baseWindow._hWnd);
	GetWindowText(mw->_tx_search->_baseWindow._hWnd, wtext, 100);

	if (wcslen(wtext) <= 0)
		return;

	loc = _wcreate_locale(LC_ALL, L"ar_SY.utf8");
	_wcstombs_l(text, wtext, 100, loc);
	_free_locale(loc);

	for (int ix = 0; ix < sizeof(OldTestament) / sizeof(OldTestament[0]); ++ix)
	{
		search(mw, wParam, lParam, OldTestament[ix].table_english, text);
	}

	for (int ix = 0; ix < sizeof(NewTestament) / sizeof(NewTestament[0]); ++ix)
	{
		search(mw, wParam, lParam, NewTestament[ix].table_english, text);
	}

}

void OnTXChaper_enter(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	wchar_t buff[50];
	GetWindowText(mw->_tx_chapter_idx->_baseWindow._hWnd, buff, 50);
	size_t len = wcslen(buff);

	for (size_t ix = 0; ix < len; ++ix)
	{
		wchar_t c = buff[ix];
		if (c >= 0x0660 && c <= 0x0669)
		{
			c -= 0x0660;
			c += L'0';
			buff[ix] = c;
		}
	}

	int idx = _wtoi(buff);

	if (g_chapter_count && idx && idx <= g_chapter_count)
	{
		LoadChapter(mw, g_part_name, idx);
	}
}
