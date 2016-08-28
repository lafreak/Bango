#ifndef _CMACRODB_
#define _CMACRODB_

#include <map>

#include <TinyXML2/tinyxml2.h>

#include "CItemInfo.h"

class CMacroDB
{

	static std::map<DWORD, CMacro*> g_mMacro;
	static std::map<std::string, int> g_mKey;

	static bool LoadInitItem();

	// Use only on MainServer close.
	
	
public:
	static bool Initialize();

	static void UnloadInitItem();

	static CMacro* FindMacro(WORD wType, WORD wIndex);
	static int FindKey(const char* szKey);
};

typedef std::map<DWORD, CMacro*> MacroMap;
typedef std::map<std::string, int> KeyMap;

#endif