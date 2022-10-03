#include "platform.h"

#include <Richedit.h>
#include <rich_edit.h>

static BOOL Create(BaseWindow* _this);

RichEdit* RichEdit_init()
{
    RichEdit* wnd = (RichEdit*)malloc(sizeof(RichEdit));
    assert(wnd != NULL);

    BaseWindow_default((BaseWindow*)wnd);

    //wnd->_baseWindow._HandleMessageFunc = HandleMessage;
    wnd->_baseWindow._CreateFunc = Create;

    return wnd;
}

void RichEdit_free(RichEdit* wnd)
{
    free(wnd);
}

static BOOL Create(BaseWindow* _this)
{
    HWND hWnd = CreateWindowEx(
        0,
        MSFTEDIT_CLASS,
        (PCTSTR)NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | ES_MULTILINE | WS_TABSTOP,
        0, 0, 0, 0,
        _this->_hWndParent,
        _this->_id,
        NULL,
        NULL);
    assert(hWnd != NULL);

    _this->_hWnd = hWnd;

    return _this->_hWnd ? TRUE : FALSE;
}
