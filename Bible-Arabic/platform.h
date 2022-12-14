#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h>


#ifdef _DEBUG
#include <crtdbg.h>
#endif

#endif /* _PLATFORM_H_ */

