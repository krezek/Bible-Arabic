#include "platform.h"

#include <tree_view.h>

static BOOL Create(BaseWindow* _this);

TreeView* TreeView_init()
{
    TreeView* wnd = (TreeView*)malloc(sizeof(TreeView));
    assert(wnd != NULL);

    BaseWindow_default((BaseWindow*)wnd);

    //wnd->_baseWindow._HandleMessageFunc = HandleMessage;
    wnd->_baseWindow._CreateFunc = Create;

    return wnd;
}

void TreeView_free(TreeView* wnd)
{
    free(wnd);
}

static BOOL Create(BaseWindow* _this)
{
    HWND hWnd = CreateWindowEx(0,
        WC_TREEVIEW,
        (PCTSTR)NULL,
        WS_VISIBLE | WS_CHILD | TVS_HASLINES | WS_BORDER | WS_CLIPSIBLINGS,
        0, 0, 0, 0,
        _this->_hWndParent,
        _this->_id,
        NULL,
        NULL);
    assert(hWnd != NULL);

    _this->_hWnd = hWnd;

    return _this->_hWnd ? TRUE : FALSE;
}
