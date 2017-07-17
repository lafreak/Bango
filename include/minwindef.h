#ifndef _MINWINDEF_
#define _MINWINDEF_
#pragma once

//typedef unsigned long       DWORD;
typedef unsigned int 		DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef int 				SOCKET;

typedef void				*PVOID;

#define INVALID_SOCKET 		-1
#define SOCKET_ERROR		-1
#define THREAD_SUCCESS		0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#include <inttypes.h>

typedef int64_t __int64;

#include <time.h>

static DWORD GetTickCount(void) 
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

#endif
