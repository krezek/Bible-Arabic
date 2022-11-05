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
	char buff[512];
	short buffer[16000];
	int i;
	FILE* output;

	rc = init_MBR(DB_MBR_URL);
	if (rc)
	{
		ShowError(L"Unable to load mbrola db file.");
		return;
	}

	reset_MBR();

	strcpy(buff, "_ 150\na 75\nb 75\na 75\nn 75\na 75\n_ 10\n");
	rc = write_MBR(buff);
	if (!rc)
	{
		ShowError(L"No enough space in the buffer");
		close_MBR();
		return;
	}

	flush_MBR();

	output = fopen("abana.ulaw", "wb");

	while ((i = readtype_MBR(buffer, 16000, LIN16)) == 16000)
		fwrite(buffer, 2, i, output);

	if (i > 0)
	{
		fwrite(buffer, 2, i, output);
	}

	fclose(output);
	close_MBR();
}
