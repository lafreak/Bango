#ifndef _CMACRO_
#define _CMACRO_

#include <minwindef.h>
#include <common.h>

struct CMacro
{
	enum MACRO_TYPE {
		MT_NPC,
		MT_ITEM,
		MT_MONSTER,
	};
};

#endif