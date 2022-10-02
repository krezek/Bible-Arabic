#ifndef _MAIN_WND_H_
#define _MAIN_WND_H_

#include <tree_view.h>

typedef struct
{
	BaseWindow _baseWindow;

	int _client_width, _client_height;

	TreeView* _treeView;
} MainWindow;

ATOM MainWindow_RegisterClass();

MainWindow* MainWindow_init();
void MainWindow_free(MainWindow* mw);

#endif /* _MAIN_WND_H_ */

