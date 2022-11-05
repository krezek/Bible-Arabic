#include "platform.h"

#include "main_wnd.h"

#define DLL_EXPORT
typedef struct Parser Parser;
#include "Misc/incdll.h"
#include "Libonechannel/onechannel.h"

void write_header(int file_format, int audio_length, unsigned short samp_rate, FILE* output_file);

#define DB_MBR_URL "..\\mbrola_db\\ar0"
short buffer[16000];

void OnBtnClicked_read(MainWindow* mw, WPARAM wParam, LPARAM lParam)
{
	int rc = 0;
	char buff[512];
	int i;
	FILE* output;
	BOOL bRtn;
	int audio_length = 0;
	unsigned short samp_rate = 16000;

	rc = init_MBR(DB_MBR_URL);
	if (rc)
	{
		ShowError(L"Unable to load mbrola db file.");
		return;
	}

	reset_MBR();

	strcpy(buff, "_ 150\na 75\nb 75\na 75\nn 75\na 75\n_ 150\n");
	rc = write_MBR(buff);
	if (!rc)
	{
		ShowError(L"No enough space in the buffer");
		close_MBR();
		return;
	}

	flush_MBR();

	output = fopen("verse.wav", "wb");
		
	while ((i = readtype_MBR(buffer, 16000, LIN16)) == 16000)
	{
		fwrite(buffer, 2, i, output);
	}

	if (i > 0)
	{
		fwrite(buffer, 2, i, output);
	}

	audio_length = (int)(ftell(output) / 2) - 0x16;
	fseek(output, 0, SEEK_SET);
	write_header(1, audio_length, samp_rate, output);

	fclose(output);
	close_MBR();
	
	bRtn = PlaySound(L"verse.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	if (bRtn != TRUE)
	{
		ShowError(L"read wav error.");
	}
}
