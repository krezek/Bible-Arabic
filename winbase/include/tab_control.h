#ifndef _TAB_CONTROL_H_
#define _TAB_CONTROL_H_

#include <base_wnd.h>

typedef struct
{
	BaseWindow _baseWindow;
} TabControl;

TabControl* TabControl_init();
void TabControl_free(TabControl* wnd);

#endif /* _TAB_CONTROL_H_ */
