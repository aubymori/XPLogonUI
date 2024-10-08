#include "debug.h"

void dbgvprintf(LPCWSTR format, void *_argp)
{
	WCHAR msg[1024];
	va_list argp = (va_list)_argp;
	int cnt = wvsprintfW(msg, format, argp);

	OutputDebugStringW(msg);
}

void dbgprintf(LPCWSTR format, ...)
{
	va_list argp;
	va_start(argp, format);
	dbgvprintf(format, argp);
	va_end(argp);
}