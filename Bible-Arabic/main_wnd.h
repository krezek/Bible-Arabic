#ifndef _MAIN_WND_H_
#define _MAIN_WND_H_

#include <layout_mgr.h>
#include <statusbar.h>
#include <tree_view.h>
#include <tab_control.h>
#include <rich_edit.h>
#include <label.h>
#include <text_edit.h>
#include <list_view.h>
#include <button.h>

typedef struct
{
	BaseWindow _baseWindow;

	int _client_width, _client_height;
	
	LayoutManager* _lm_main;
	LayoutManager* _lm_tab_bible;
	LayoutManager* _lm_tab_bible_bottom;
	LayoutManager* _lm_tab_search;

	StatusBar* _statusBar;
	TreeView* _treeView;
	TabControl* _tabControl;
	RichEdit* _richEdit;
	Label* _lb_chapter;
	TextEdit* _tx_chapter_idx;
	Label* _lb_chapter_count;
	TextEdit* _tx_search;
	ListView* _lv_result;
	Button* _bt_next_chapter;
	Button* _bt_prev_chapter;
	Button* _bt_search;
} MainWindow;

struct Testament
{
	char* table_english;
	wchar_t* table_arabic;
};

#define OT_COUNT 10
#define NT_COUNT 16

extern struct Testament OldTestament[OT_COUNT];
extern struct Testament NewTestament[NT_COUNT];

ATOM MainWindow_RegisterClass();

MainWindow* MainWindow_init();
void MainWindow_free(MainWindow* mw);

#endif /* _MAIN_WND_H_ */

