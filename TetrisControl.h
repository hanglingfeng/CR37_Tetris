#pragma once
//#undef UNICODE
#ifdef UNICODE
#define TCHAR wchar_t
#define _T(X) L##X
#define _tprintf wprintf
#define _tsystem _wsystem

#else
#define TCHAR char
#define _T(X) X
#define _tprintf printf
#define _tsystem system
#endif // Unicode


int StartGame();