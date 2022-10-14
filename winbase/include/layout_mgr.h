#ifndef _LAYOUT_MGR_H_
#define _LAYOUT_MGR_H_

#include <cmp.h>

typedef struct _LayoutManager LayoutManager;
typedef struct _Margin Margin;

typedef enum {LM_H_LEFT = 1, LM_H_CENTER = 2, LM_H_RIGHT = 4, LM_H_EXPAND = 8,
				LM_V_TOP = 16, LM_V_CENTER = 32, LM_V_BOTOM = 64, LM_V_EXPAND = 128} STYLE;

typedef void (*LayoutManagerInitFunc) (LayoutManager* _this, int rows, int columns);
typedef void (*LayoutManagerSetRowsHeightFunc)(LayoutManager* _this, ...);
typedef void (*LayoutManagerSetColumnsWidthFunc)(LayoutManager* _this, ...);
typedef void (*LayoutManagerSetCmpFunc)(LayoutManager* _this, int i, int j, Component* cmp, STYLE style, Margin margin);
typedef int (*LayoutManagerGetMinWidthFunc)(LayoutManager* _this);
typedef int (*LayoutManagerGetMinHeightFunc)(LayoutManager* _this);
typedef void (*LayoutManagerDoLayoutFunc)(LayoutManager* _this, int x0, int y0, int width, int height, BOOL repiant, HDC hdc);

typedef struct _Margin
{
	int _left, _top;
	int _right, _buttom;
} Margin;

typedef struct _LayoutManager
{
	Component _cmp;

	int _rows, _columns;

	double* _rowsHeight;
	double* _columnsWidth;

	Component** _components;
	STYLE* _style;
	Margin* _margin;

	int _x, _y, _width, _height;

	LayoutManagerInitFunc _InitFunc;
	LayoutManagerSetRowsHeightFunc _SetRowsHeightFunc;
	LayoutManagerSetColumnsWidthFunc _SetColumnWidthFunc;
	LayoutManagerSetCmpFunc _SetCmpFunc;
	LayoutManagerGetMinWidthFunc _GetMinWidthFunc;
	LayoutManagerGetMinHeightFunc _GetMinHeightFunc;
	LayoutManagerDoLayoutFunc _DoLayoutFunc;
} LayoutManager;

LayoutManager* LayoutManager_init();
void LayoutManager_free(LayoutManager* lm);

#endif /* _LAYOUT_MGR_H_ */
