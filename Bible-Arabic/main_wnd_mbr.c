#include "platform.h"

#include "main_wnd.h"

#define DLL_EXPORT
typedef struct Parser Parser;
#include "Misc/incdll.h"
#include "Libonechannel/onechannel.h"

#define DB_MBR_URL "..\\mbrola_db\\ar0"

void OnBtnClicked_read(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	int rc = 0;

	rc = init_MBR(DB_MBR_URL);
	if (rc)
	{
		ShowError(L"Unable to load mbrola db file.");
		return;
	}

	close_MBR();
}
