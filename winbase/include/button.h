#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <base_wnd.h>

typedef struct
{
	BaseWindow _baseWindow;

} Button;

Button* Button_init();
void Button_free(Button* wnd);


#endif /* _BUTTON_H_ */
