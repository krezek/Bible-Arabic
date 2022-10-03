#ifndef _RICHEDIT_H_
#define _RICHEDIT_H_

#include <base_wnd.h>

typedef struct
{
	BaseWindow _baseWindow;

} RichEdit;

RichEdit* RichEdit_init();
void RichEdit_free(RichEdit* wnd);


#endif /* _RICHEDIT_H_ */
