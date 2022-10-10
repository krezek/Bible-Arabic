#include "platform.h"

#include "main_wnd.h"
#include "resource.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("الكتاب المقدس");

WNDPROC lpTabControlWndProc;

static LRESULT HandleMessage(BaseWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT TabControlCallBckProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static int g_statusbar_height;
static const int g_margin = 5;

void OnDBClick_treeView(MainWindow* mw, WPARAM wParam, LPARAM lParam);
void OnBtnClicked_next_chapter(MainWindow* mw, WPARAM wParam, LPARAM lParam);
void OnBtnClicked_prev_chapter(MainWindow* mw, WPARAM wParam, LPARAM lParam);
void OnBtnClicked_search(MainWindow* mw, WPARAM wParam, LPARAM lParam);

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
    mw->_richEdit = RichEdit_init();
    mw->_lb_chapter = Label_init();
    mw->_lb_chapter_count1 = Label_init();
    mw->_lb_chapter_count2 = Label_init();
    mw->_tx_search = TextEdit_init();
    mw->_lv_result = ListView_init();
    mw->_bt_next_chapter = Button_init();
    mw->_bt_prev_chapter = Button_init();
    mw->_bt_search = Button_init();

    return mw;
}

void MainWindow_free(MainWindow* mw)
{
    Button_free(mw->_bt_search);
    Button_free(mw->_bt_prev_chapter);
    Button_free(mw->_bt_next_chapter);
    ListView_free(mw->_lv_result);
    TextEdit_free(mw->_tx_search);
    Label_free(mw->_lb_chapter_count2);
    Label_free(mw->_lb_chapter_count1);
    Label_free(mw->_lb_chapter);
    RichEdit_free(mw->_richEdit);
    TabControl_free(mw->_tabControl);
    TreeView_free(mw->_treeView);
    StatusBar_free(mw->_statusBar);
    free(mw);
}

static void OnCreate_TreeView(MainWindow* mw)
{
    HTREEITEM hItem;
    TVINSERTSTRUCT insertStruct = { 0 };
    TVITEM* pItem = &insertStruct.item;
    insertStruct.hParent = NULL;
    insertStruct.hInsertAfter = TVI_ROOT;

    pItem->mask = TVIF_TEXT;
    pItem->pszText = L"العهد القديم";
    hItem = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);

    if (hItem)
    {
        HTREEITEM hItem_sub;

        for (int ix = 0; ix < sizeof(OldTestament) / sizeof(OldTestament[0]); ++ix)
        {
            insertStruct.hParent = hItem;
            pItem->pszText = OldTestament[ix].table_arabic;
            hItem_sub = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
            if (hItem_sub) SendMessage(mw->_treeView->_baseWindow._hWnd, TVM_ENSUREVISIBLE, 0, (LPARAM)hItem_sub);
        }
    }

    insertStruct.hParent = NULL;

    pItem->mask = TVIF_TEXT;
    pItem->pszText = L"العهد الجديد";
    hItem = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);

    if (hItem)
    {
        HTREEITEM hItem_sub;

        for (int ix = 0; ix < sizeof(NewTestament) / sizeof(NewTestament[0]); ++ix)
        {
            insertStruct.hParent = hItem;
            pItem->pszText = NewTestament[ix].table_arabic;
            hItem_sub = (HTREEITEM)SendMessageA(mw->_treeView->_baseWindow._hWnd, TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
            if (hItem_sub) SendMessage(mw->_treeView->_baseWindow._hWnd, TVM_ENSUREVISIBLE, 0, (LPARAM)hItem_sub);
        }
    }
}

static void OnCreate_TabControl(MainWindow* mw)
{
    TCITEM tie;

    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = L"الانجيل";
    TabCtrl_InsertItem(mw->_tabControl->_baseWindow._hWnd, 0, &tie);
    
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = L"البحث";
    TabCtrl_InsertItem(mw->_tabControl->_baseWindow._hWnd, 1, &tie);
    
    
    mw->_richEdit->_baseWindow._SetParentFunc((BaseWindow*)mw->_richEdit, mw->_tabControl->_baseWindow._hWnd);
    mw->_richEdit->_baseWindow._SetIdFunc((BaseWindow*)mw->_richEdit, (HMENU)ID_RICHEDIT);

    if (!mw->_richEdit->_baseWindow._CreateFunc((BaseWindow*)mw->_richEdit))
    {
        ShowError(L"Unable to create rich edit!");
        return;
    }

    mw->_lb_chapter->_baseWindow._SetParentFunc((BaseWindow*)mw->_lb_chapter, mw->_tabControl->_baseWindow._hWnd);
    mw->_lb_chapter->_baseWindow._SetIdFunc((BaseWindow*)mw->_lb_chapter, (HMENU)ID_LABELCHAPTER);

    if (!mw->_lb_chapter->_baseWindow._CreateFunc((BaseWindow*)mw->_lb_chapter))
    {
        ShowError(L"Unable to create label chapter!");
        return;
    }

#ifdef _WIN64
    lpTabControlWndProc = (WNDPROC)SetWindowLongPtr(mw->_tabControl->_baseWindow._hWnd,
        GWLP_WNDPROC, (LONG_PTR)&TabControlCallBckProcedure);
    SetWindowLongPtr(mw->_tabControl->_baseWindow._hWnd,
        GWLP_USERDATA, (LONG_PTR)mw);
#else
    lpTabControlWndProc = (WNDPROC)SetWindowLongPtr(mw->_tabControl->_baseWindow._hWnd, 
        GWL_WNDPROC, (LONG_PTR)&TabControlCallBckProcedure);
    SetWindowLongPtr(mw->_tabControl->_baseWindow._hWnd,
        GWL_USERDATA, (LONG_PTR)mw);
#endif



    SetWindowText(mw->_lb_chapter->_baseWindow._hWnd, L"الاصحاح");

    mw->_lb_chapter_count1->_baseWindow._SetParentFunc((BaseWindow*)mw->_lb_chapter_count1, mw->_tabControl->_baseWindow._hWnd);
    mw->_lb_chapter_count1->_baseWindow._SetIdFunc((BaseWindow*)mw->_lb_chapter_count1, (HMENU)ID_LABELCHAPTER_COUNT2);

    if (!mw->_lb_chapter_count1->_baseWindow._CreateFunc((BaseWindow*)mw->_lb_chapter_count1))
    {
        ShowError(L"Unable to create chapter count 1!");
        return;
    }

    mw->_lb_chapter_count2->_baseWindow._SetParentFunc((BaseWindow*)mw->_lb_chapter_count2, mw->_tabControl->_baseWindow._hWnd);
    mw->_lb_chapter_count2->_baseWindow._SetIdFunc((BaseWindow*)mw->_lb_chapter_count2, (HMENU)ID_LABELCHAPTER_COUNT2);

    if (!mw->_lb_chapter_count2->_baseWindow._CreateFunc((BaseWindow*)mw->_lb_chapter_count2))
    {
        ShowError(L"Unable to create chapter count 2!");
        return;
    }

    mw->_bt_prev_chapter->_baseWindow._SetParentFunc((BaseWindow*)mw->_bt_prev_chapter, mw->_tabControl->_baseWindow._hWnd);
    mw->_bt_prev_chapter->_baseWindow._SetIdFunc((BaseWindow*)mw->_bt_prev_chapter, (HMENU)ID_BUTTON_PREV_CHAPTER);

    if (!mw->_bt_prev_chapter->_baseWindow._CreateFunc((BaseWindow*)mw->_bt_prev_chapter))
    {
        ShowError(L"Unable to create prev chapter button");
        return;
    }

    SetWindowText(mw->_bt_prev_chapter->_baseWindow._hWnd, L"السابق");

    mw->_bt_next_chapter->_baseWindow._SetParentFunc((BaseWindow*)mw->_bt_next_chapter, mw->_tabControl->_baseWindow._hWnd);
    mw->_bt_next_chapter->_baseWindow._SetIdFunc((BaseWindow*)mw->_bt_next_chapter, (HMENU)ID_BUTTON_NEXT_CHAPTER);

    if (!mw->_bt_next_chapter->_baseWindow._CreateFunc((BaseWindow*)mw->_bt_next_chapter))
    {
        ShowError(L"Unable to create next chapter button");
        return;
    }

    SetWindowText(mw->_bt_next_chapter->_baseWindow._hWnd, L"التالي");

    mw->_tx_search->_baseWindow._SetParentFunc((BaseWindow*)mw->_tx_search, mw->_tabControl->_baseWindow._hWnd);
    mw->_tx_search->_baseWindow._SetIdFunc((BaseWindow*)mw->_tx_search, (HMENU)ID_TEXTEDIT_SEARCH);

    if (!mw->_tx_search->_baseWindow._CreateFunc((BaseWindow*)mw->_tx_search))
    {
        ShowError(L"Unable to create search text edit!");
        return;
    }

    mw->_bt_search->_baseWindow._SetParentFunc((BaseWindow*)mw->_bt_search, mw->_tabControl->_baseWindow._hWnd);
    mw->_bt_search->_baseWindow._SetIdFunc((BaseWindow*)mw->_bt_search, (HMENU)ID_BUTTON_SEARCH);

    if (!mw->_bt_search->_baseWindow._CreateFunc((BaseWindow*)mw->_bt_search))
    {
        ShowError(L"Unable to create search button");
        return;
    }

    SetWindowText(mw->_bt_search->_baseWindow._hWnd, L"بحث");

    mw->_lv_result->_baseWindow._SetParentFunc((BaseWindow*)mw->_lv_result, mw->_tabControl->_baseWindow._hWnd);
    mw->_lv_result->_baseWindow._SetIdFunc((BaseWindow*)mw->_lv_result, (HMENU)ID_LISTVIW_RESULT);

    if (!mw->_lv_result->_baseWindow._CreateFunc((BaseWindow*)mw->_lv_result))
    {
        ShowError(L"Unable to create search list view!");
        return;
    }

    LV_COLUMN lvC;
    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvC.fmt = LVCFMT_LEFT;
    lvC.cx = 100;

    lvC.pszText = L"مكان";
    ListView_InsertColumn(mw->_lv_result->_baseWindow._hWnd, 0, &lvC);
    
    lvC.cx = 300; 
    lvC.pszText = L"النص";
    ListView_InsertColumn(mw->_lv_result->_baseWindow._hWnd, 1, &lvC);

    ShowWindow(mw->_tx_search->_baseWindow._hWnd, SW_HIDE);
    ShowWindow(mw->_bt_search->_baseWindow._hWnd, SW_HIDE);
    ShowWindow(mw->_lv_result->_baseWindow._hWnd, SW_HIDE);
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

    RECT sBarRc;
    GetWindowRect(mw->_statusBar->_baseWindow._hWnd, &sBarRc);
    g_statusbar_height = sBarRc.bottom - sBarRc.top;

    mw->_treeView->_baseWindow._SetParentFunc((BaseWindow*)mw->_treeView, mw->_baseWindow._hWnd);
    mw->_treeView->_baseWindow._SetIdFunc((BaseWindow*)mw->_treeView, (HMENU)ID_TREEVIEW); 
    mw->_treeView->_baseWindow._cmp._SetSizeFunc((Component*)mw->_treeView, 50, 25);
    
    if (!mw->_treeView->_baseWindow._CreateFunc((BaseWindow*)mw->_treeView))
    {
        ShowError(L"Unable to create tree view!");
        return;
    }

    mw->_tabControl->_baseWindow._SetParentFunc((BaseWindow*)mw->_tabControl, mw->_baseWindow._hWnd);
    mw->_tabControl->_baseWindow._SetIdFunc((BaseWindow*)mw->_tabControl, (HMENU)ID_TABCONTROL);

    if (!mw->_tabControl->_baseWindow._CreateFunc((BaseWindow*)mw->_tabControl))
    {
        ShowError(L"Unable to create tab control!");
        return;
    }

    OnCreate_TreeView(mw);
    OnCreate_TabControl(mw);
}

static void OnSize(MainWindow* mw, int width, int height)
{
    mw->_client_width = width;
    mw->_client_height = height;

    MoveWindow(mw->_statusBar->_baseWindow._hWnd, 0, height - g_statusbar_height, width, g_statusbar_height, TRUE);

    mw->_treeView->_baseWindow._MoveWindowFunc((BaseWindow*)mw->_treeView, g_margin, g_margin,
        200 - 2 * g_margin, height - 2 * g_margin - g_statusbar_height, TRUE);

    mw->_tabControl->_baseWindow._MoveWindowFunc((BaseWindow*)mw->_tabControl, 200 + g_margin, g_margin,
        width - 200 - 2 * g_margin, height - 2 * g_margin - g_statusbar_height, TRUE);

    RECT rc;
    TabCtrl_GetItemRect(mw->_tabControl->_baseWindow._hWnd, 0, &rc);

    int iHeight = rc.bottom - rc.top;
    GetClientRect(mw->_tabControl->_baseWindow._hWnd, &rc);

    // TAB 1
    MoveWindow(mw->_richEdit->_baseWindow._hWnd, rc.left + g_margin, rc.top + iHeight + g_margin, 
        rc.right - rc.left - 2 * g_margin, rc.bottom - rc.top - iHeight * 4 - 2 * g_margin, TRUE);

    int x0 = rc.left + 2 * g_margin;
    int y0 = rc.bottom - rc.top - iHeight * 2 - 2 * g_margin;
    
    MoveWindow(mw->_lb_chapter->_baseWindow._hWnd, x0, y0,
        75, iHeight, TRUE);

    x0 += 75 + g_margin;

    MoveWindow(mw->_lb_chapter_count1->_baseWindow._hWnd, x0, y0,
        50, iHeight, TRUE);

    x0 += 50 + g_margin;

    MoveWindow(mw->_lb_chapter_count2->_baseWindow._hWnd, x0, y0,
        50, iHeight, TRUE);

    x0 += 50 + g_margin;

    MoveWindow(mw->_bt_prev_chapter->_baseWindow._hWnd, x0, y0,
        50, iHeight, TRUE);

    x0 += 50 + g_margin;
    
    MoveWindow(mw->_bt_next_chapter->_baseWindow._hWnd, x0, y0,
        50, iHeight, TRUE);
    
    // TAB 2

    x0 = rc.left + g_margin;
    y0 = rc.top + iHeight + g_margin;

    MoveWindow(mw->_tx_search->_baseWindow._hWnd, x0, y0,
        rc.right - rc.left - 2 * g_margin, rc.top + iHeight + g_margin, TRUE);

    y0 += iHeight + 3 * g_margin;
    
    MoveWindow(mw->_bt_search->_baseWindow._hWnd, x0, y0,
        75, iHeight, TRUE);

    y0 += iHeight + 2 * g_margin;

    MoveWindow(mw->_lv_result->_baseWindow._hWnd, x0, y0,
        rc.right - rc.left - 2 * g_margin, rc.bottom - rc.top - iHeight * 4 - 2 * g_margin, TRUE);
}

static void OnNotify_tabControl(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
    switch (((LPNMHDR)lParam)->code)
    {
    case TCN_SELCHANGE:
    {
        int iPage = TabCtrl_GetCurSel(mw->_tabControl->_baseWindow._hWnd);
        if (iPage == 0)
        {

            ShowWindow(mw->_richEdit->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_lb_chapter->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_lb_chapter_count1->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_lb_chapter_count2->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_bt_next_chapter->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_bt_prev_chapter->_baseWindow._hWnd, SW_SHOW);

            ShowWindow(mw->_tx_search->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_bt_search->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_lv_result->_baseWindow._hWnd, SW_HIDE);
        }
        else if (iPage == 1)
        {
            ShowWindow(mw->_richEdit->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_lb_chapter->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_lb_chapter_count1->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_lb_chapter_count2->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_bt_next_chapter->_baseWindow._hWnd, SW_HIDE);
            ShowWindow(mw->_bt_prev_chapter->_baseWindow._hWnd, SW_HIDE);

            ShowWindow(mw->_tx_search->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_bt_search->_baseWindow._hWnd, SW_SHOW);
            ShowWindow(mw->_lv_result->_baseWindow._hWnd, SW_SHOW);
        }
        break;
    }
    }
}

static void OnNotify_treeView(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
    switch (((LPNMHDR)lParam)->code)
    {
    case NM_DBLCLK:
        OnDBClick_treeView(mw, wParam, lParam);
        break;
    }
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

    case WM_NOTIFY:
        if (((LPNMHDR)lParam)->hwndFrom == mw->_treeView->_baseWindow._hWnd)
            OnNotify_treeView(mw, wParam, lParam);
        else if (((LPNMHDR)lParam)->hwndFrom == mw->_tabControl->_baseWindow._hWnd)
            OnNotify_tabControl(mw, wParam, lParam);
        return 0;

    case WM_DESTROY:
        OnDestroy(mw);
        return 0;

    default:
        return DefWindowProc(_this->_hWnd, uMsg, wParam, lParam);
    }
}

LRESULT TabControlCallBckProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN64
    MainWindow* mw = (MainWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
    MainWindow* mw = (MainWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);
#endif

    switch (uMsg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_NEXT_CHAPTER:
            OnBtnClicked_next_chapter(mw, wParam, lParam);
            break;

        case ID_BUTTON_PREV_CHAPTER:
            OnBtnClicked_prev_chapter(mw, wParam, lParam);
            break;
        
        case ID_BUTTON_SEARCH:
            OnBtnClicked_search(mw, wParam, lParam);
            break;
        
        default:
            break;
        }
        break;
    default:
        break;
    }
    return CallWindowProc(lpTabControlWndProc, hWnd, uMsg, wParam, lParam);
}
