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
	{"LimitedPet",  IC_PET },
	{"money", 		IC_MONEY },
	{"yinyang", 	IC_YINYANG },

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
	{"coin", 		ISC_COIN },
	{"repair", 		ISC_REPAIR },
	{"necklace", 	ISC_NECKLACE },
	{"cocoon", 		ISC_COCOON },	
	{"mask", 		ISC_MASK },
	{"standard", 	ISC_STANDARD },
	{"dagger",		ISC_DAGGER },
	{"yinyangmirror", ISC_YINYANGMIRROR },
	{"taegeuk", 	ISC_TAEGEUK },
	{"trigramSlot1", ISC_TRIGRAM1 },
	{"trigramSlot2", ISC_TRIGRAM2 },
	{"trigramSlot3", ISC_TRIGRAM3 },
	{"trigramSlot4", ISC_TRIGRAM4 },
	{"trigramSlot5", ISC_TRIGRAM5 },
	{"trigramSlot6", ISC_TRIGRAM6 },
	{"trigramSlot7", ISC_TRIGRAM7 },
	{"trigramSlot8", ISC_TRIGRAM8 },
	{"egg", 		ISC_EGG },

	// Player Class
	{"knight",		PC_KNIGHT },
	{"mage", 		PC_MAGE },
	{"archer", 		PC_ARCHER },
	{"thief", 		PC_THIEF },

	// Item Specialty
	{"hp",			CItemInfo::R_HP },
	{"mp", 			CItemInfo::R_MP }
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

		pItem->m_wIndex = 		pItemInfo->IntAttribute("index");
		pItem->m_byClass = 		FindKey(pItemInfo->Attribute("class"));
		pItem->m_bySubClass = 	FindKey(pItemInfo->Attribute("subclass"));
		pItem->m_byLevel = 		pItemInfo->IntAttribute("level");
	 	pItem->m_bWear = 		pItemInfo->IntAttribute("wear") == 1;
		pItem->m_byReqClass = 	FindKey(pItemInfo->Attribute("reqclass"));
		pItem->m_byReqLevel = 	pItemInfo->IntAttribute("reqlevel");
		pItem->m_nRange = 		pItemInfo->IntAttribute("range");
		pItem->m_nBuy = 		pItemInfo->IntAttribute("buy");
		pItem->m_nSell = 		pItemInfo->IntAttribute("sell");
		pItem->m_byEndurance = 	pItemInfo->IntAttribute("endurance");
		pItem->m_bPlural = 		pItemInfo->IntAttribute("plural") == 1;
		pItem->m_bUse = 		pItemInfo->IntAttribute("use") == 1;
		pItem->m_nCooltime = 	pItemInfo->IntAttribute("cooltime");
		pItem->m_byEffect = 	pItemInfo->IntAttribute("effect");

		XMLElement *pItemSpecialtyList = pItemInfo->FirstChildElement("specialty");

		if (pItemSpecialtyList) {
			XMLNode *pSpecialty = pItemSpecialtyList->FirstChild();

			while (pSpecialty != NULL) {

				if (strcmp(pSpecialty->ToElement()->Name(), "refresh") == 0) {

					int nType = FindKey(pSpecialty->ToElement()->Attribute("property"));
					if (nType != -1)
						pItem->m_nRefresh[nType] = pSpecialty->ToElement()->IntAttribute("amount");
				}

				pSpecialty = pSpecialty->NextSibling();
			}
		}

		DWORD dwKey = (CMacro::MT_ITEM << 2) + pItem->m_wIndex;
		g_mMacro[dwKey] = pItem;

		pItemInfo = pItemInfo->NextSiblingElement("item");
	}

	return true;
}

void CMacroDB::UnloadInitItem()
{
	for (auto& a: g_mMacro)
		delete a.second;

	g_mMacro.clear();
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