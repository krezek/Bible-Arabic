#include "sqlite3.h"

#include <wchar.h>

void remove_marks(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    if (argc == 1) {
        const wchar_t* text = sqlite3_value_text16(argv[0]);
        if (text) {
            int length = (int)wcslen(text);
            wchar_t* result = (wchar_t*)sqlite3_malloc((length + 1)* sizeof(wchar_t));
            
            int iy = 0;

            for (int ix = 0; ix < length; ++ix)
            {
                wchar_t c = text[ix];
                if (c >= 0x064B && c <= 0x065F)
                {

                }
                else if (c == 0x0622 || c == 0x0623 || c == 0x0625)
                {
                    result[iy++] = 0x0627;
                }
                else
                {
                    result[iy++] = text[ix];
                }
            }

            result[iy++] = 0;
            
            sqlite3_result_text16(context, result, -1, SQLITE_TRANSIENT);
            sqlite3_free(result);
            return;
        }
    }

    sqlite3_result_null(context);
}