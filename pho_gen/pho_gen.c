#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include <sqlite3.h>


#define DB_URL "..\\data\\bible.db"
#define MAX_TEXT 4098

char* g_table_name = "matthew";
int g_chapter = 1;
int g_verse_number = 1;
wchar_t g_verse_text[MAX_TEXT];

struct
{
	wchar_t _alpha;
	char _phonem;
	int _time;
} pho[] =
{
	{ L'ا', 'a', 75},
	{ L'ب', 'b', 75},
	{ L'ت', 't', 75},
	{ L'ث', '0', 75},
	{ L'ج', 'g', 75},
	{ L'ح', '1', 75},
	{ L'خ', '2', 75},
	{ L'د', 'd', 75},
	{ L'ذ', '3', 75},
	{ L'ر', 'r', 75},
	{ L'ز', 'z', 75},
	{ L'س', 's', 75},
	{ L'ش', '$', 75},
	{ L'ص', '4', 75},
	{ L'ض', '5', 75},
	{ L'ط', 'p', 75},
	{ L'ظ', 'x', 75},
	{ L'ع', '6', 75},
	{ L'غ', '7', 75},
	{ L'ف', 'f', 75},
	{ L'ق', 'q', 75},
	{ L'ك', 'k', 75},
	{ L'ل', 'l', 75},
	{ L'م', 'm', 75},
	{ L'ن', 'n', 75},
	{ L'ه', '8', 75},
	{ L'و', 'w', 75},
	{ L'ي', 'y', 75},
	{ L'َ', 'a', 40},
	{ L'ُ', 'o', 40},
	{ L'ِ', 'i', 40},
	{ L'ً', '9', 40},
	{ L'ٌ', '=', 40},
	{ L'ٍ', '?', 40},
	{ L'ء', '^', 75}
};


void get_verse_text();

int main(int argc, char* argv[])
{
	char file_name[255];

	sprintf(file_name, "%s_%d_%d.pho", g_table_name, g_chapter, g_verse_number);
	get_verse_text();
	FILE* output = fopen(file_name, "w");

	fprintf(output, "%c %d\n", '_', 150);

	size_t len = wcslen(g_verse_text);
	for (size_t ix = 0; ix < len; ++ix)
	{
		if (g_verse_text[ix] == L' ')
		{
			fprintf(output, "%c %d\n\n", '_', 10);
			fprintf(output, "%c %d\n", '_', 10);
		}
		else if (g_verse_text[ix] == L'ْ')
		{

		}
		else if (g_verse_text[ix] == L'إ')
		{
			fprintf(output, "%c %d\n", '^', 75);
		}
		else if (g_verse_text[ix] == L'أ')
		{
			fprintf(output, "%c %d\n", '^', 75);
		}
		else
		{
			char c = 0;
			int d = 0;
			for (int iy = 0; iy < sizeof(pho) / sizeof(pho[0]); ++iy)
			{
				if (pho[iy]._alpha == g_verse_text[ix])
				{
					c = pho[iy]._phonem;
					d = pho[iy]._time;
				}
			}

			if (c == 0)
			{
				fprintf(stderr, "%x\n", (int)g_verse_text[ix]);
			}

			fprintf(output, "%c %d\n", c, d);
		}
		
	}

	fprintf(output, "%c %d\n", '_', 150);

	fclose(output);
	return 0;
}

void get_verse_text()
{
	sqlite3* bible_db;
	char* err_msg = 0;
	sqlite3_stmt* res;
	int rc;
	char sql[255];

	rc = sqlite3_open_v2(DB_URL, &bible_db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK) {
		printf("Can't open database file!");
		sqlite3_close(bible_db);
		return;
	}

	sprintf(sql, "SELECT body FROM %s WHERE chapter=%d AND verse=%d", g_table_name, g_chapter, g_verse_number);

	rc = sqlite3_prepare_v2(bible_db, sql, -1, &res, 0);

	if (rc != SQLITE_OK)
	{
		printf("Unable to select verse!");
		sqlite3_finalize(res);
		sqlite3_close(bible_db);
		return;
	}

	if (sqlite3_step(res) == SQLITE_ROW)
	{
		wcscpy(g_verse_text, sqlite3_column_text16(res, 0));
	}

	sqlite3_finalize(res);
	sqlite3_close(bible_db);
}
