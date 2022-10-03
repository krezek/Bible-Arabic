#include "platform.h"

#include "main_wnd.h"
#include "resource.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("الكتاب المقدس");

static LRESULT HandleMessage(BaseWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam);

ATOM MainWindow_RegisterClass()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_DBLCLKS;
    wcex.lpfnWndProc = BaseWindow_Proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; // MAKEINTRESOURCE(IDR_POPUPMENU);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDC_MYICON));

    return RegisterClassEx(&wcex);
}

BOOL Create(BaseWindow* _this)
{
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        _this
    );

    _this->_hWnd = hWnd;

    return _this->_hWnd ? TRUE : FALSE;
}

MainWindow* MainWindow_init()
{
    MainWindow* mw = (MainWindow*)malloc(sizeof(MainWindow));
    assert(mw != NULL);

    BaseWindow_default((BaseWindow*)mw);

    mw->_client_width = mw->_client_height = 0;

    mw->_baseWindow._HandleMessageFunc = HandleMessage;
    mw->_baseWindow._CreateFunc = Create;

    mw->_statusBar = StatusBar_init();
    mw->_treeView = TreeView_init();
    mw->_tabControl = TabControl_init();

    return mw;
}

void MainWindow_free(MainWindow* mw)
{
    TabControl_free(mw->_tabControl);
    TreeView_free(mw->_treeView);
    StatusBar_free(mw->_statusBar);
    free(mw);
}

static void OnCreate(MainWindow* mw)
{
    RECT rc;
    GetClientRect(mw->_baseWindow._hWnd, &rc);

    mw->_client_width = rc.right - rc.left;
    mw->_client_height = rc.bottom - rc.top;

    mw->_statusBar->_baseWindow._SetParentFunc((BaseWindow*)mw->_statusBar, mw->_baseWindow._hWnd);
    mw->_statusBar->_baseWindow._SetIdFunc((BaseWindow*)mw->_statusBar, (HMENU)ID_STATUSBAR);

    if (!mw->_statusBar->_baseWindow._CreateFunc((BaseWindow*)mw->_statusBar))
    {
        ShowError(L"Unable to create status bar!");
        return;
    }

    mw->_statusBar->_baseWindow._MoveWindowFunc((BaseWindow*)mw->_statusBar, 0, mw->_client_height - 25, mw->_client_width, 25, TRUE);
    
    mw->_treeView->_baseWindow._SetParentFunc((BaseWindow*)mw->_treeView, mw->_baseWindow._hWnd);
    mw->_treeView->_baseWindow._SetIdFunc((BaseWindow*)mw->_treeView, (HMENU)ID_TREEVIEW); 
    
    if (!mw->_treeView->_baseWindow._CreateFunc((BaseWindow*)mw->_treeView))
    {
        ShowError(L"Unable to create tree view!");
        return;
    }

    mw->_treeView->_baseWindow._MoveWindowFunc((BaseWindow*)mw->_treeView, 0, 0, mw->_client_width / 2, mw->_client_height - 25, TRUE);

    mw->_tabControl->_baseWindow._SetParentFunc((BaseWindow*)mw->_tabControl, mw->_baseWindow._hWnd);
    mw->_tabControl->_baseWindow._SetIdFunc((BaseWindow*)mw->_tabControl, (HMENU)ID_TABCONTROL);

    if (!mw->_tabControl->_baseWindow._CreateFunc((BaseWindow*)mw->_tabControl))
    {
        ShowError(L"Unable to create tab control!");
        return;
    }

    mw->_tabControl->_baseWindow._MoveWindowFunc((BaseWindow*)mw->_tabControl, mw->_client_width / 2, 0, mw->_client_width / 2, mw->_client_height - 25, TRUE);

    HTREEITEM hItem;
    TVINSERTSTRUCT insertStruct = { 0 };
    TVITEM* pItem = &insertStruct.item;
    insertStruct.hParent = NULL;
    insertStruct.hInsertAfter = TVI_ROOT;

    pItem->mask = TVIF_TEXT;
    pItem->pszText = L"العهد الجديد";
    hItem = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);

    if (hItem)
    {
        insertStruct.hParent = hItem;
        pItem->pszText = L"متى";
        hItem = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
        if (hItem) SendMessage(mw->_treeView->_baseWindow._hWnd, TVM_ENSUREVISIBLE, 0, (LPARAM)hItem);
    }
    
    TCITEM tie;
    
    tie.mask = TCIF_TEXT | TCIF_IMAGE;
    tie.iImage = -1;
    tie.pszText = L"متى";
    TabCtrl_InsertItem(mw->_tabControl->_baseWindow._hWnd, 0, &tie);
    TabCtrl_InsertItem(mw->_tabControl->_baseWindow._hWnd, 1, &tie);
}

static void OnSize(MainWindow* mw, int width, int height)
{
    if (!IsWindowVisible(mw->_baseWindow._hWnd))
        return;
}

static void OnPaint(MainWindow* mw)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(mw->_baseWindow._hWnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWFRAME));

    EndPaint(mw->_baseWindow._hWnd, &ps);
}

static void OnDestroy(MainWindow* mw)
{
    PostQuitMessage(0);
}

static LRESULT HandleMessage(BaseWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MainWindow* mw = (MainWindow*)_this;

    switch (uMsg)
    {
    case WM_CREATE:
        OnCreate(mw);
        return 0;

    case WM_PAINT:
        OnPaint(mw);
        return 0;

    case WM_SIZING:
        return mw->_baseWindow._OnSizingFunc(&mw->_baseWindow, (RECT*)lParam);

    case WM_SIZE:
        OnSize(mw, LOWORD(lParam), HIWORD(lParam));
        return 0;

    case WM_DESTROY:
        OnDestroy(mw);
        return 0;

    default:
        return DefWindowProc(_this->_hWnd, uMsg, wParam, lParam);
    }
}
