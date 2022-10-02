#ifndef _TREE_VIEW_H_
#define _TREE_VIEW_H_

#include <base_wnd.h>

typedef struct
{
	BaseWindow _baseWindow;
} TreeView;

TreeView* TreeView_init();
void TreeView_free(TreeView* wnd);

#endif /* _TREE_VIEW_H_ */
