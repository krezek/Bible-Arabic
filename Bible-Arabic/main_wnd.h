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

typedef struct
{
	BaseWindow _baseWindow;

	int _client_width, _client_height;
	
	StatusBar* _statusBar;
	TreeView* _treeView;
	TabControl* _tabControl;
	RichEdit* _richEdit;
	Label* _lb_chapter;
	Label* _lb_chapter_count1;
	Label* _lb_chapter_count2;
	TextEdit* _tx_search;
	ListView* _lv_result;
} MainWindow;

ATOM MainWindow_RegisterClass();

MainWindow* MainWindow_init();
void MainWindow_free(MainWindow* mw);

#endif /* _MAIN_WND_H_ */

