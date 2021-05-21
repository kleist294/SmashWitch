#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_


#include <windows.h>
#include <stdio.h>


inline void DebugPrintf(const char* pformat, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pformat);
	vsprintf_s(buf, 256, pformat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif // _DEBUG || DEBUG
}


#endif // _DEBUG_PRINTF_H_

