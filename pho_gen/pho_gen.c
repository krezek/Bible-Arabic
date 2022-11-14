#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <sqlite3.h>


#define DB_URL "..\\data\\bible.db"
#define MAX_TEXT 4098

char* g_table_name = "matthew";
int g_chapter = 1;
int g_verse_number = 1;
wchar_t g_verse_text[MAX_TEXT];

void get_verse_text();

int main(int argc, char* argv[])
{
	get_verse_text();

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
