#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define PATH "C:\\Users\\Kinaz Rezek\\Test\\ar_new\\41\\"
#define BUFF_LENGTH 1024
char buffer[BUFF_LENGTH];

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "en_US.UTF-8");

	for (int ix = 1; ix <= 16; ix++)
	{
		char source[255];
		char dist[255];
		int line = 1;
		int idx = 0;

		sprintf(source, "%s%d.htm", PATH, ix);
		sprintf(dist, "%s_%d.sql", "mark", ix);

		FILE* pSrc = fopen(source, "r");
		FILE* pDist = fopen(dist, "w");

		int c;
		while ((c = getc(pSrc)) != EOF)
		{
			if (c == L'\n' || c == L'\r')
			{
				if (c == L'\r')
					continue;

				buffer[idx] = 0;

				fprintf(pDist, "INSERT INTO mark (chapter, verse, prefix, suffix, body)\nVALUES (%d, %d, NULL, NULL, \"%s\");\n", ix, line, strchr(buffer, ';') + 1);

				++line;
				idx = 0;
			}
			else
			{
				buffer[idx++] = c;
			}
		}
	
		fclose(pDist);
		fclose(pSrc);
	}

	return 0;
}
