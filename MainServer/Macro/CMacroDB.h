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
	
public:
	static bool Initialize();

	static CMacro* FindMacro(WORD wType, WORD wIndex);
	static int FindKey(const char* szKey);
	static int IntAttributeEx(tinyxml2::XMLElement* pEle, const char* szName);
};

typedef std::map<DWORD, CMacro*> MacroMap;
typedef std::map<std::string, int> KeyMap;

#endif