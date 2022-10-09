#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

const char* source = "C:\\Users\\Kinaz Rezek\\Test\\ar_new\\04\\1.htm";
const char* dist = "generated.sql";

#define chapter 1

#define BUFF_LENGTH 1024
char buffer[BUFF_LENGTH];

int line = 1;
int idx = 0;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "en_US.UTF-8");

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

			fprintf(pDist, "INSERT INTO leviticus (chapter, verse, prefix, suffix, body)\nVALUES (%d, %d, NULL, NULL, \"%s\");\n", chapter, line, strchr(buffer, ';') + 1);
			
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

	return 0;
}
