#ifndef _MINWINDEF_
#define _MINWINDEF_
#pragma once

typedef unsigned long       DWORD;
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

#include <inttypes.h>

typedef int64_t __int64;

#endif
