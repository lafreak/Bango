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
	{"ride", 		IC_RIDE },

	// Item Sub Class
	{"etc", 	    ISC_ETC },
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
	{"resistnecklace2", ISC_RESISTNECKLACE2 },
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
	{"enchantnecklace", ISC_ENCHANTNECKLAKE },
	{"cost",		ISC_COSTUME },

	// Player Class
	{"knight",		PC_KNIGHT },
	{"mage", 		PC_MAGE },
	{"archer", 		PC_ARCHER },
	{"thief", 		PC_THIEF },
	{"shaman",		PC_SHAMAN },

	// Item Specialty
	{"hp",			CItemInfo::R_HP },
	{"mp", 			CItemInfo::R_MP }
};

bool CMacroDB::Initialize()
{
	printf("Loading Items...\n");
	if (!LoadInitItem())
		return false;

	printf("Loading Monsters...\n");
	if (!LoadInitMonster())
		return false;

	return true;
}

bool CMacroDB::LoadInitItem()
{
	XMLDocument doc;

	if (doc.LoadFile("Config/InitItem.xml") != XML_SUCCESS) {
		std::ofstream error1("InitItemError.txt");
		error1 << std::string(doc.GetErrorStr1());
		error1.close();

		printf(KRED "Cannot open InitItem.xml. (%s)\nMore information in generated InitItemError.txt file." KNRM, doc.ErrorName());

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
		pItem->m_wRange =		pItemInfo->IntAttribute("range");

		XMLElement *pItemSpecialtyList = pItemInfo->FirstChildElement("specialty");

		if (pItemSpecialtyList) {
			pItem->m_wDefense = pItemSpecialtyList->IntAttribute("defense");
			pItem->m_wHit =		pItemSpecialtyList->IntAttribute("hit");
			pItem->m_wDodge =	pItemSpecialtyList->IntAttribute("dodge");
			pItem->m_wAbsorb =	pItemSpecialtyList->IntAttribute("absorb");
			pItem->m_wResistFire =		pItemSpecialtyList->IntAttribute("resistfire");
			pItem->m_wResistIce =		pItemSpecialtyList->IntAttribute("resistice");
			pItem->m_wResistLitning =	pItemSpecialtyList->IntAttribute("resistlitning");
			pItem->m_wResistCurse =		pItemSpecialtyList->IntAttribute("resistcurse");
			pItem->m_wResistPalsy =		pItemSpecialtyList->IntAttribute("resistpalsy");
			pItem->m_dwHP = pItemSpecialtyList->IntAttribute("hp");
			pItem->m_dwMP = pItemSpecialtyList->IntAttribute("mp");
			pItem->m_wMinAttack = pItemSpecialtyList->IntAttribute("minattack");
			pItem->m_wMaxAttack = pItemSpecialtyList->IntAttribute("maxattack");
			pItem->m_wMinMagic =  pItemSpecialtyList->IntAttribute("minmagic");
			pItem->m_wMaxMagic =  pItemSpecialtyList->IntAttribute("maxmagic");
			pItem->m_wStr =		pItemSpecialtyList->IntAttribute("str");
			pItem->m_wHth =		pItemSpecialtyList->IntAttribute("hth");
			pItem->m_wInt =		pItemSpecialtyList->IntAttribute("int");
			pItem->m_wWis =		pItemSpecialtyList->IntAttribute("wis");
			pItem->m_wDex =		pItemSpecialtyList->IntAttribute("dex");
			pItem->m_wAttackSpeed = pItemSpecialtyList->IntAttribute("attackspeed");

			XMLNode *pSpecialty = pItemSpecialtyList->FirstChild();

			while (pSpecialty != NULL) {

				if (strcmp(pSpecialty->ToElement()->Name(), "refresh") == 0) {

					int nType = FindKey(pSpecialty->ToElement()->Attribute("property"));
					if (nType != -1)
						pItem->m_nRefresh[nType] = pSpecialty->ToElement()->IntAttribute("amount");
				}

				else if (strcmp(pSpecialty->ToElement()->Name(), "buff") == 0) {
					XMLElement *pElement = pSpecialty->ToElement();

					pItem->m_nBuffId = pElement->IntAttribute("id");
					pItem->m_nBuffTime = pElement->IntAttribute("time");
					pItem->m_nBuffValue = pElement->IntAttribute("value");
				}

				else if (strcmp(pSpecialty->ToElement()->Name(), "teleport") == 0) {
					XMLElement *pElement = pSpecialty->ToElement();

					pItem->m_nTeleport[0] = pElement->IntAttribute("v1");
					pItem->m_nTeleport[1] = pElement->IntAttribute("v2");
					pItem->m_nTeleport[2] = pElement->IntAttribute("v3");
					/*
					if (pItem->m_byReqLevel > 0)
					{
						pItem->m_nX = pElement->IntAttribute("val");
						pItem->m_nTeleportKind = pElement->IntAttribute("val2");
						pItem->m_nY = pElement->IntAttribute("val3");
					}
					else
					{
						pItem->m_nTeleportKind = pElement->IntAttribute("val");
						pItem->m_bTeleportType = pElement->IntAttribute("val2");
						pItem->m_wTeleportID = pElement->IntAttribute("val3");
					}
					*/
				}

				pSpecialty = pSpecialty->NextSibling();
			}
		}

		DWORD dwKey = (CMacro::MT_ITEM << 16) + pItem->m_wIndex;
		g_mMacro[dwKey] = pItem;

		pItemInfo = pItemInfo->NextSiblingElement("item");
	}

	return true;
}

bool CMacroDB::LoadInitMonster()
{
	XMLDocument doc;

	if (doc.LoadFile("Config/InitMonster.xml") != XML_SUCCESS) {
		printf(KRED "Cannot open InitMonster.xml. (%s)\n" KNRM, doc.ErrorName());
		return false;
	}

	XMLElement *pRoot = doc.RootElement();
	if (!pRoot) {
		printf("Cannot find root element inside InitMonster.xml.\n");
		return false;
	}

	XMLElement *pMonsterInfo = pRoot->FirstChildElement("monster");

	while (pMonsterInfo != NULL)
	{
		CMonsterInfo *pMonster = new CMonsterInfo;

/*

		m_byRace(0),
		m_byLevel(0),
		m_byAI(0),
		m_wRange(0),
		m_wCloseSight(0),
		m_wFarSight(0),
		m_n64Exp(0),
		m_wWalkSpeed(0),
		m_wRunSpeed(0),
		m_wAttackSpeed(0),
		*/
		pMonster->m_wIndex = 		pMonsterInfo->IntAttribute("index");
		pMonster->m_byRace = 		pMonsterInfo->IntAttribute("race");
		pMonster->m_byLevel =		pMonsterInfo->IntAttribute("level");
		pMonster->m_byAI =			pMonsterInfo->IntAttribute("ai");
		pMonster->m_wRange =		pMonsterInfo->IntAttribute("range");
		pMonster->m_wCloseSight =	pMonsterInfo->IntAttribute("closesight");
		pMonster->m_wFarSight =		pMonsterInfo->IntAttribute("farsight");
		pMonster->m_wWalkSpeed =	pMonsterInfo->IntAttribute("walkspeed");
		pMonster->m_wRunSpeed =		pMonsterInfo->IntAttribute("runspeed");
		pMonster->m_wAttackSpeed =  pMonsterInfo->IntAttribute("attackspeed");

		pMonster->m_wDefense[DT_CLOSE] =pMonsterInfo->IntAttribute("closedefense");
		pMonster->m_wDefense[DT_FAR] =  pMonsterInfo->IntAttribute("fardefense");
		pMonster->m_wHit =			pMonsterInfo->IntAttribute("hit");
		pMonster->m_wDodge =		pMonsterInfo->IntAttribute("dodge");
		pMonster->m_wAbsorb =		pMonsterInfo->IntAttribute("absorb");
		pMonster->m_wResistFire =	pMonsterInfo->IntAttribute("resistfire");
		pMonster->m_wResistIce =	pMonsterInfo->IntAttribute("resistice");
		pMonster->m_wResistLitning =pMonsterInfo->IntAttribute("resistlitning");
		pMonster->m_wResistCurse =	pMonsterInfo->IntAttribute("resistcurse");
		pMonster->m_wResistPalsy =	pMonsterInfo->IntAttribute("resistpalsy");
		pMonster->m_dwHP =			pMonsterInfo->IntAttribute("hp");
		pMonster->m_dwMP =			pMonsterInfo->IntAttribute("mp");
		pMonster->m_wMinAttack =	pMonsterInfo->IntAttribute("minattack");
		pMonster->m_wMaxAttack =	pMonsterInfo->IntAttribute("maxattack");
		pMonster->m_wMinMagic =		pMonsterInfo->IntAttribute("minmagic");
		pMonster->m_wMaxMagic =		pMonsterInfo->IntAttribute("maxmagic");
		pMonster->m_wStr =			pMonsterInfo->IntAttribute("str");
		pMonster->m_wHth =			pMonsterInfo->IntAttribute("hth");
		pMonster->m_wInt =			pMonsterInfo->IntAttribute("int");
		pMonster->m_wWis =			pMonsterInfo->IntAttribute("wis");
		pMonster->m_wDex =			pMonsterInfo->IntAttribute("dex");
		pMonster->m_wSize =			pMonsterInfo->IntAttribute("size");

		std::stringstream conv;
		const char* exp = pMonsterInfo->Attribute("exp");
		conv << exp;
		conv >> pMonster->m_n64Exp;

		DWORD dwKey = (CMacro::MT_MONSTER << 16) + pMonster->m_wIndex;
		g_mMacro[dwKey] = pMonster;

		pMonsterInfo = pMonsterInfo->NextSiblingElement("monster");
	}

	return true;
}

void CMacroDB::Destroy()
{
	for (auto& a: g_mMacro)
		delete a.second;

	g_mMacro.clear();
}

CMacro* CMacroDB::FindMacro(WORD wKey, WORD wIndex)
{
	DWORD dwKey = (wKey << 16) + wIndex;

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
