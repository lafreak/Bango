#include "CMacroDB.h"

MacroMap CMacroDB::g_mMacro;

using namespace tinyxml2;

KeyMap CMacroDB::g_mKey = {
	// Item Class
	{"weapon", 		IC_WEAPON },
	{"defense", 	IC_DEFENSE },
	{"ornament", 	IC_ORNAMENT },
	{"general", 	IC_GENERAL },
	{"quest", 		IC_QUEST },
	{"money", 		IC_MONEY },
	{"transform", 	IC_TRANSFORM },
	{"pet", 		IC_PET },

	// Item Sub Class
	{"fish", 		ISC_FISH },
	{"sword", 		ISC_SWORD },
	{"sword2h", 	ISC_SWORD2HAND },
	{"wand", 		ISC_WAND },
	{"bow", 		ISC_BOW },
	{"shield", 		ISC_SHIELD },
	{"helmet", 		ISC_HELMET },
	{"upperarmor", 	ISC_UPPERARMOR },
	{"lowerarmor", 	ISC_LOWERARMOR },
	{"gauntlet", 	ISC_GAUNTLET },
	{"boots", 		ISC_BOOTS },
	{"ring", 		ISC_RING },
	{"trinket", 	ISC_TRINKET },
	{"refresh", 	ISC_REFRESH },
	{"charm", 		ISC_CHARM },
	{"gem", 		ISC_GEM },
	{"money", 		IC_MONEY },
	{"coin", 		ISC_COIN },
	{"repair", 		ISC_REPAIR },
	{"necklace", 	ISC_NECKLACE },
	{"cocoon", 		ISC_COCOON },	
	{"mask", 		ISC_MASK },
	{"standard", 	ISC_STANDARD },
	{"dagger",		ISC_DAGGER },

	// Player Class
	{"knight",		PC_KNIGHT },
	{"mage", 		PC_MAGE },
	{"archer", 		PC_ARCHER },
	{"thief", 		PC_THIEF },
	{"all", 		PC_ALL },
};

bool CMacroDB::Initialize()
{
	printf("Loading Items...\n");
	if (!LoadInitItem())
		return false;

	return true;
}

bool CMacroDB::LoadInitItem()
{
	XMLDocument doc;

	if (doc.LoadFile("Config/InitItem.xml") != XML_SUCCESS) {
		printf(KRED "Cannot open InitItem.xml. (%s)\n" KNRM, doc.ErrorName());
		return false;
	}

	XMLElement *pRoot = doc.RootElement();
	if (!pRoot) {
		printf("Cannot find root element inside InitItem.xml.\n");
		return false;
	}

	XMLElement *pItemInfo = pRoot->FirstChildElement("item");

	while (pItemInfo != NULL)
	{
		CItemInfo *pItem = new CItemInfo;

		pItem->m_wIndex = 		IntAttributeEx(pItemInfo, "index");
		pItem->m_byClass = 		FindKey(pItemInfo->Attribute("class"));
		pItem->m_bySubClass = 	FindKey(pItemInfo->Attribute("subclass"));
		pItem->m_byLevel = 		IntAttributeEx(pItemInfo, "level");
	 	pItem->m_bWear = 		IntAttributeEx(pItemInfo, "wear") == 1;
		pItem->m_byReqClass = 	FindKey(pItemInfo->Attribute("reqclass"));
		pItem->m_byReqLevel = 	IntAttributeEx(pItemInfo, "reqlevel");
		pItem->m_nRange = 		IntAttributeEx(pItemInfo, "range");
		pItem->m_nBuy = 		pItemInfo->IntAttribute("buy");
		pItem->m_nSell = 		pItemInfo->IntAttribute("sell");
		pItem->m_byEndurance = 	pItemInfo->IntAttribute("endurance");
		pItem->m_bPlural = 		IntAttributeEx(pItemInfo, "plural") == 1;
		pItem->m_bUse = 		IntAttributeEx(pItemInfo, "use") == 1;
		pItem->m_nCooltime = 	IntAttributeEx(pItemInfo, "cooltime");

		DWORD dwKey = (CMacro::MT_ITEM << 2) + pItem->m_wIndex;
		g_mMacro[dwKey] = pItem;

		pItemInfo = pItemInfo->NextSiblingElement("item");
	}

	return true;
}

CMacro* CMacroDB::FindMacro(WORD wKey, WORD wIndex)
{
	DWORD dwKey = (wKey << 2) + wIndex;

	MacroMap::iterator it = g_mMacro.find(dwKey);
	if (it != g_mMacro.end())
		return (*it).second;

	return NULL;
}

int CMacroDB::FindKey(const char* szKey)
{
	if (szKey == NULL)
		return -1;

	KeyMap::iterator it = g_mKey.find(std::string(szKey));
	if (it != g_mKey.end())
		return (*it).second;

	return -1;
}

int CMacroDB::IntAttributeEx(XMLElement* pEle, const char* szName)
{
	int nValue = -1;

	pEle->QueryIntAttribute(szName, &nValue);

	return nValue;
}