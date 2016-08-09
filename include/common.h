#ifndef _COMMON_
#define _COMMON_

#pragma once

static __int64 g_nNeedExp[] = {
	0, 5, 24, 60, 160,
		328, 542, 814, 1157, 1588,
		2250, 3086, 4135, 5444, 7068,
		9126, 11660, 14769, 18572, 23214,
		29155, 36409, 45245, 55988, 69026, 
		85569, 105656, 130009, 159494, 195150, 
		238225, 290216, 352918, 428488, 519513, 
		629149, 761081, 919784, 1110624, 1340045, 
		1615778, 1947099, 2345141, 2823265, 3397501, 
		4087087, 4915108, 5909267, 7102808, 8535623, 
		10255633, 12320243, 14798389, 17772795, 21342730, 
		25627317, 30769501, 36940820, 44347118, 53235407, 
		63902104, 76702906, 92064653, 110499551, 132622249, 
		159170373, 191028978, 229260177, 275138508, 330193415, 
		// ąŮ˛ń
		396260232,	1188853398,	1426699190,	1712116603,	2054620005, 
		2465626643 ,2958837208 ,3550692535 ,4260921625 ,5113199283 ,
		6135935388 ,7363221560 ,8835967855 ,10603266353 ,12724027540 ,
		15268944005 ,18322846853 ,21987533410 ,26385160468 ,31662316180 ,
		37994906328 ,45594017848 ,54712955065 ,65655683173 ,78786960398 ,
		94544496618 ,113453543683 ,136144403815 ,163373439683 ,196048286480 ,
};

static int g_denoHP[] = { 10, 14, 13, 13 };
static int g_denoMP[] = { 13, 10, 12, 12 };

// (struct) /////////////////////////////////////////////////////////
struct DATE_TIME
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

struct D2S_LOADPLAYER_DESC
{
	int nAID, nPID;
	WORD wStats[5];
	WORD wCurHP, wCurMP;
	__int64 n64Exp;
	WORD wPUPoint, wSUPoint, wContribute;
	int nAnger, nX, nY, nZ;
	BYTE byLevel, byClass, byJob;
	BYTE byFace, byHair;
	const char* szName;
};

//#if defined( MAINSVR) || defined( DBSVR)

struct BASEPROPERTY
{
	int prty[5];	// Str, Hth, Int, Wis, Dex
	int nHP;
	int nMP;
};

enum STAT
{
	STAT_STR,
	STAT_HTH,
	STAT_INT,
	STAT_WIS,
	STAT_AGI,
};

#define GAME_HERO 0x80

static BASEPROPERTY g_baseproperty[] = {
	18, 16, 8, 8, 10, 180, 120,		// knight
		8, 10, 18, 16, 8, 170, 140,		// mage
		14, 10, 8, 10, 18, 160, 160,	// archer
		14, 10, 8, 10, 18, 160, 160,	// thief
};
//#endif

// (define) /////////////////////////////////////////////////////////
#define COUNTRY(country) (country == g_nCountry)
#define COUNTRYMASK(mask) (mask & (1 << g_nCountry))

#define MAX_CHARACTER 5
#define MAX_PROTECT 30
#define MAX_NUM 0x7fffffff
#define INVALID_PROPERTY 0xffffffff
#define MAX_INVENTORY 60
#define MAX_INVENTORYEX 72
#define MAX_STORAGE 100
#define CLASS_NUM 3
#define BOOSTDECMP 6
#define MAX_BULLETININFO 20
#define NULL_CHECK( value) if( value == 0) return
#define MAX_BUY_ITEM_EACH	9999

// Length
#define LEN_ID				16
#define LEN_PWD				16
#define LEN_NMID			16
#define LEN_NMPWD			8
#define LEN_ACCOUNT			16
#define LEN_NAME			24
#define LEN_PLAYERNAME		20
#define LEN_GUILDNAME		16
#define LEN_NEWPLAYERNAME	14
#define LEN_NEWGUILDNAME	14
#define LEN_RANKNAME		14
#define LEN_ITEMNAME		30
#define LEN_FILENAME		20
#define LEN_PATH			128
#define LEN_CHATTING		128
#define LEN_MYTELPTNAME		20
#define LEN_GUILDNOTICE		180
#define LEN_MLMNOTICE		180
#define LEN_STALLTITLE		64

#define MAX_SHORTCUT		40
#define MAX_FRD				30

#define MAIL_MAX			100
#define MAIL_MAX_LEN		512
#define MAIL_MAX_LOAD		50
#define MAIL_COST_GENERAL	5
#define MAIL_COST_PARCEL	100

// Map
#define MAP_NONE			0x00000000
#define MAP_FIELD			0x00000001
#define MAP_DUNGEON			0x00000002

// NPC General State
#define NGS_ONMIRROR		0x00000001
#define NGS_ONMIRROREX		0x00000002
#define NGS_THRONEEFFECT1	0x00000004
#define NGS_THRONEEFFECT2	0x00000008
#define NGS_OPENDOOR		0x00000010	//˝ĂłŞ¸®żŔ2 ą® ż­¸®¸é ON
#define NGS_SIEGEGUNSET		0x00000020	//°řĽşş´±â ĽłÄˇµĘ
#define NGS_SIEGEGUNUSED	0x00000040	//°řĽşş´±â ĽłÄˇÁß


// Character General State
#define CGS_KNEE				0x00000001
#define CGS_KO					0x00000002
#define CGS_REST				0x00000004
#define CGS_ONREVIVAL			0x00000008
#define CGS_ONSTALL				0x00000010
#define CGS_FISH				0x00000020
#define CGS_COOKING				0x00000040
#define CGS_ONPVP				0x00000080
#define CGS_ONPK				0x00000100
#define CGS_ONTRANSFORM			0x00000200
#define CGS_WAR_UNFURLSTANDARD	0x00000400
#define CGS_PKSTATEOPEN			0x00000800
#define CGS_ONPORTAL			0x00001000
#define CGS_INVINCIBLE			0x00002000
#define CGS_PREASCENSION		0x00004000
#define CGS_OPENBOX				0x00008000
#define CGS_ASCENSION			0x00010000
#define CGS_LORDDECLARE			0x00020000
#define CGS_PET_FALCON 			0x00040000	// PET ¸Ĺ
#define CGS_PET_OWL 			0x00080000	// PET şÎľűŔĚ
#define CGS_PET_CROW 			0x00100000	// PET ±î¸¶±Í
#define CGS_SIEGEGUNCONTROL		0x00040000	// °řĽşş´±â°ˇ Á¶Á¤ÁßŔĎ¶§
#define CGS_SIEGEGUNDIE			0x00080000	// °řĽş ş´±â°ˇ ÇŘĂĽµÇ´Â »óĹÂ

#define CGS_DARK				0x00100000	// ľĎČćĽ®	// Á¶ÇŐ˝Ă˝şĹŰ
#define CGS_SAINT				0x00200000	// ˝ĹĽşĽ®
#define CGS_FLAME				0x00400000	// Č­ż°Ľ®
#define CGS_ICE					0x00800000	// şůż°Ľ®
#define CGS_LIGHT				0x01000000	// ł«·ÚĽ®
#define CGS_POISON				0x02000000	// µ¶żîĽ®
#define CGS_PARAL				0x04000000	// ¸¶şńĽ®
#define CGS_POWER				0x08000000	// ±âżîĽ®
#define CGS_TECH				0x10000000	// ±âĽúĽ®
#define CGS_FANTA				0x20000000	// ˝ĹşńĽ®
#define CGS_BLOOD				0x40000000	// Ç÷¸¶Ľ®
#define CGS_MIX_LEVEL2			0x80000000	// ľ÷±Ű2´Ü°č

#define CGS_MIX_HALFSETDEF_46  __int64(0x00000001) << 32	// Č­ÁÖ ÇĎÇÁĽÂĆ® 46ąćľî±¸
#define CGS_MIX_FULLSETDEF_46  __int64(0x00000002) << 32	// Č­ÁÖ ÇĂĆęĆ®
#define CGS_MIX_HALFSETDEF_50  __int64(0x00000004) << 32	// Č­ÁÖ ÇĎÇÁĽÂĆ® 50ąćľî±¸
#define CGS_MIX_FULLSETDEF_50  __int64(0x00000008) << 32	// Č­ÁÖ ÇĂĆęĆ®
#define CGS_MIX_HALFSETDEF_55  __int64(0x00000010) << 32	// Č­ÁÖ ÇĎÇÁĽÂĆ® 55ąćľî±¸
#define CGS_MIX_FULLSETDEF_55  __int64(0x00000020) << 32	// Č­ÁÖ ÇĂĆęĆ®
#define CGS_MIX_HALFSETDEF_60  __int64(0x00000040) << 32	// Č­ÁÖ ÇĎÇÁĽÂĆ® 60ąćľî±¸
#define CGS_MIX_FULLSETDEF_60  __int64(0x00000080) << 32	// Č­ÁÖ ÇĂĆęĆ®

#define CGS_EVENT_HALLOWEEN_GHOST_1		 __int64(0x00000100) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ŔŻ·É
#define CGS_EVENT_HALLOWEEN_GHOST_2		 __int64(0x00000200) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ŔŻ·É
#define CGS_EVENT_HALLOWEEN_GHOST_3		 __int64(0x00000400) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ŔŻ·É
#define CGS_EVENT_HALLOWEEN_WITCH_1		 __int64(0x00000800) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ¸¶łŕ
#define CGS_EVENT_HALLOWEEN_WITCH_2		 __int64(0x00001000) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ¸¶łŕ
#define CGS_EVENT_HALLOWEEN_WITCH_3		 __int64(0x00002000) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ¸¶łŕ
#define CGS_EVENT_HALLOWEEN_PUMPKIN_1    __int64(0x00004000) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ČŁąÚ
#define CGS_EVENT_HALLOWEEN_PUMPKIN_2    __int64(0x00008000) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ČŁąÚ
#define CGS_EVENT_HALLOWEEN_PUMPKIN_3    __int64(0x00010000) << 32	// ÇŇ·ÎŔ© ŔĚşĄĆ®. ČŁąÚ
#define CGS_EVENT_HALLOWEEN_MIX		(CGS_EVENT_HALLOWEEN_GHOST_1|CGS_EVENT_HALLOWEEN_GHOST_2|CGS_EVENT_HALLOWEEN_GHOST_3|\
									 CGS_EVENT_HALLOWEEN_WITCH_1|CGS_EVENT_HALLOWEEN_WITCH_2|CGS_EVENT_HALLOWEEN_WITCH_3|\
									 CGS_EVENT_HALLOWEEN_PUMPKIN_1|CGS_EVENT_HALLOWEEN_PUMPKIN_2|CGS_EVENT_HALLOWEEN_PUMPKIN_3)	 

#define CGS_BATTLEFIELD_RED				__int64(0x00020000) << 32	// ˝ĂłŞ¸®żŔ3 ŔüŔĺ»óĹÂ Č«ĆŔ
#define CGS_BATTLEFIELD_BLUE			__int64(0x00040000) << 32	// ˝ĂłŞ¸®żŔ3 ŔüŔĺ»óĹÂ Ă»ĆŔ
#define CGS_BATTLEFIELD					(CGS_BATTLEFIELD_RED | CGS_BATTLEFIELD_BLUE)	// ˝ĂłŞ¸®żŔ3 ŔüŔĺ»óĹÂ
#define CGS_TOWERBURNING_1				__int64(0x00080000) << 32	// ĹľŔÇ HP°ˇ ŔĎÁ¤ %ŔĚÇĎŔĎ¶§ şŇĹ¸żŔ¸§
#define CGS_TOWERBURNING_2				__int64(0x00100000) << 32	// ĹľŔÇ HP°ˇ ŔĎÁ¤ %ŔĚÇĎŔĎ¶§ şŇĹ¸żŔ¸§
#define CGS_MIX (CGS_DARK|CGS_SAINT|CGS_FLAME|CGS_ICE|CGS_LIGHT|CGS_POISON|CGS_PARAL|CGS_POWER|CGS_TECH|CGS_FANTA|CGS_BLOOD)

// CGS Ăß°ˇ˝Ă Ăß°ˇ!! ĂŁľĆş¸˝ĂżŔ~
#define CGS_PRAYCASTING					__int64(0x00200000) << 32	// ±âżř Äł˝şĆĂ Áß
#define CGS_PRAY						__int64(0x00400000) << 32	// ±âżř »óĹÂ
#define CGS_LOADPROTECTLEADER			__int64(0x00800000) << 32	// ±şÁÖ ş¸ČŁ ¸đµĺ Ľ®»óŔ» Ĺ¬¸ŻÇŇĽö ŔÖ´Â ´ë»óŔÚ¸¦ ±¸şĐÇĎ±â Ŕ§ÇŃ »óĹÂ



// Character Magic State
#define CMS_BOOST			0x00000001
#define CMS_MOVESPEED		0x00000002
#define CMS_STONE			0x00000004
#define CMS_MEDITATION		0x00000008
#define CMS_FATALCHANCE	    0x00000010
#define CMS_REVIVALSEQUELA	0x00000020
#define CMS_ATTACKUP		0x00000040
#define CMS_MAGICUP			0x00000080
#define CMS_STUN			0x00000100
#define CMS_MOVESTOP		0x00000200
#define CMS_HITUP			0x00000400
#define CMS_ATTACKMINUP		0x00000800
#define CMS_POISON			0x00001000
#define CMS_HASTE			0x00002000
#define CMS_PROTECT			0x00004000
#define CMS_PROTECTRANGE	0x00008000
#define CMS_MAGICSTOP		0x00010000
//#define CMS_CUTEXPHALF		0x00020000		// not used
//#define CMS_KILLEDNOCOUNT	0x00040000		// not used
#define CMS_HIDE         	0x00080000
#define CMS_HP              0x00100000
#define CMS_MP              0x00200000
#define CMS_ATTACKSPEED     0x00400000
#define CMS_HITUPPER        0x00800000
#define CMS_DAMAGEDEX       0x01000000
#define CMS_HITNICE         0x02000000
#define CMS_DODGEALL        0x04000000
#define CMS_FATALNICE       0x08000000
#define CMS_SLEEP           0x10000000
#define CMS_DEFENSEPER      0x20000000
#define CMS_CTDEFENSEPER    0x40000000
#define CMS_SUFFERING       0x80000000
#define CMS_INCHANTWEAPON   __int64(0x00000001) << 32
#define CMS_AURADEFENSE     __int64(0x00000002) << 32
#define CMS_CTHEALING       __int64(0x00000004) << 32
#define CMS_SPIRITDMG       __int64(0x00000008) << 32
#define CMS_FLAGMSPEED      __int64(0x00000010) << 32
#define CMS_FLAGATTACK      __int64(0x00000020) << 32
#define CMS_FLAGMAGIC       __int64(0x00000040) << 32
#define CMS_FLAGDEFENSE     __int64(0x00000080) << 32
#define CMS_FLAGRESIST      __int64(0x00000100) << 32
#define CMS_FLAGHP          __int64(0x00000200) << 32

#define CMS_SILENCESHOT     __int64(0x00000400) << 32
#define CMS_MANABURN        __int64(0x00000800) << 32
#define CMS_POISONCLOUD     __int64(0x00001000) << 32 
#define CMS_DESTROYSIGHT    __int64(0x00002000) << 32
#define CMS_DO_UPABSORB     __int64(0x00004000) << 32
#define CMS_DO_UPRESISTALL  __int64(0x00008000) << 32
#define CMS_HIDE_CANNON		__int64(0x00010000) << 32
#define CMS_MIX_LIGHT		__int64(0x00020000) << 32
#define CMS_MIX_ICE			__int64(0x00040000) << 32




#define CMS_HALLOWEEN_ATTACKUP		__int64(0x00080000) << 32
#define CMS_HALLOWEEN_MAGICUP		__int64(0x00100000) << 32

#define CMS_ATTACK_UP			__int64(0x00200000) << 32	// Ĺ©¸®˝ş¸¶˝ş ŔĚşĄĆ® ľĆŔĚĹŰ ąöÇÁ °ř°Ý·Â ľ÷


#define CMS_CANNON_MASK		(CMS_HIDE_CANNON | CMS_HIDE)

#define CMSEX_STREN_STR			0x00000001
#define CMSEX_STREN_HTH			0x00000002
#define CMSEX_STREN_DEX			0x00000004
#define CMSEX_STREN_INT			0x00000008
#define CMSEX_STREN_FATAL		0x00000010
#define CMSEX_BERSERK			0x00000020
#define CMSEX_CTDEFLIGHTNING	0x00000040
#define CMSEX_CTDEFICE			0x00000080
#define CMSEX_CTDEFFIRE			0x00000100
#define CMSEX_CTACCURACY		0x00000200
#define CMSEX_CTBATTLE			0x00000400
#define CMSEX_SHIELDRESILIENCE	0x00000800
#define CMSEX_RESIST_LIGHTNING	0x00001000
#define CMSEX_RESIST_ICE		0x00002000
#define CMSEX_RESIST_FIRE		0x00004000
#define CMSEX_RESIST_CURSE		0x00008000
#define CMSEX_RESIST_PALSY		0x00010000
#define CMSEX_EMERGENCYESCAPE	0x00020000
#define CMSEX_CLOUDSIGHT		0x00040000
#define CMSEX_MESH_CHANCE      	0x00080000
#define CMSEX_MESH_STR         	0x00100000
#define CMSEX_MESH_HTH         	0x00200000
#define CMSEX_MESH_DEX         	0x00400000
#define CMSEX_MESH_INT         	0x00800000
#define CMSEX_MESH_WIS         	0x01000000
#define CMSEX_MESH_DEFENSE     	0x02000000
#define CMSEX_VANISHCONFI      	0x04000000
#define CMSEX_PET_HP			0x08000000
#define CMSEX_PET_MP			0x10000000
#define CMSEX_PET_ATTACK		0x20000000
#define CMSEX_PET_DEPENSE		0x40000000
#define CMSEX_HYDROCHLORICACID	0x80000000
#define CMSEX_ACCURACY_RATE		__int64(0x00000001) << 32	// Ĺ©¸®˝ş¸¶˝ş ŔĚşĄĆ® ľĆŔĚĹŰ ąöÇÁ ¸íÁß ÁˇĽö Çâ»ó
#define CMSEX_CRITICAL_HIT		__int64(0x00000002) << 32	// Ĺ©¸®˝ş¸¶˝ş ŔĚşĄĆ® ľĆŔĚĹŰ ąöÇÁ Äˇ¸íĹ¸ Č®·ü Áő°ˇ


// Character Etc. State
#define CES_TRADEASKED			0x00000001
#define CES_TRADEDISPLAY		0x00000002
#define CES_TRADEAGREED			0x00000004
#define CES_REVIVALASKED		0x00000008
#define CES_KILLEDATPVP			0x00000010
#define CES_KILLEDATONPK		0x00000020
#define CES_KILLEDATOFFPK 		0x00000040
#define CES_KILLEDATCUTEXPHALF	0x00000080
#define CES_KILLEDATCASTLEWARPK	0x00000100
#define CES_BOKJOOMUNYOPEN		0x00000200	// şąÁÖ¸Ó´Ď¸¦ ż­°í ŔÖ´Â »óĹÂ
#define CES_DANJIOPEN			0x00000400	// ±Ý,Ŕş´ÜÁö¸¦ ż­°í ŔÖ´Â »óĹÂ
#define CES_SIEGEGUNSET			0x00000800	// °řĽş ş´±â¸¦ ĽłÄˇÇĎ°í ŔÖ´Â »óĹÂ
#define CES_KILLEDATBATTLEFIELD 0x00001000

// Character Buff State
#define CBS_PCROOM          	__int64(0x00000001)
#define CBS_EXPADD130       	__int64(0x00000002)
#define CBS_MONEYADD120     	__int64(0x00000004)
#define CBS_FISHADD200      	__int64(0x00000008)
#define CBS_DROPUPCHARMARMOR	__int64(0x00000010)
#define CBS_DROPUPCHARMORNAMENT	__int64(0x00000020)
#define CBS_DROPUPCHARMWEAPON	__int64(0x00000040)
#define CBS_CUTEXPHALF			__int64(0x00000080)
#define CBS_KILLEDNOCOUNT		__int64(0x00000100)
#define CBS_PAY_UPATTACK		__int64(0x00000200)
#define CBS_PAY_CUTDAMAGE		__int64(0x00000400)
#define CBS_PAY_UPXBLOW3		__int64(0x00000800)
#define CBS_PAY_UPXBLOW5		__int64(0x00001000)
#define CBS_PAY_AUTOREFRESH		__int64(0x00002000)
#define CBS_PAY_UPHIT			__int64(0x00004000)
#define CBS_PAY_UPDODGE			__int64(0x00008000)
#define CBS_PAY_PERFECTDEF		__int64(0x00010000)
#define CBS_PAY_DRAINHP			__int64(0x00020000)
#define CBS_PAY_UPSTR			__int64(0x00040000)
#define CBS_PAY_UPHTH			__int64(0x00080000)
#define CBS_PAY_UPINT			__int64(0x00100000)
#define CBS_PAY_UPWIS			__int64(0x00200000)
#define CBS_PAY_UPDEX			__int64(0x00400000)
#define CBS_PLAYERNAMECHANGED	__int64(0x00800000)
#define CBS_GUILDNAMECHANGED	__int64(0x01000000)
#define CBS_LUCKYKEY			__int64(0x02000000)
#define CBS_LUCKYSTONE1			__int64(0x04000000)
#define CBS_LUCKYSTONE2			__int64(0x08000000)
#define CBS_CHANGEFACE			__int64(0x10000000)

#define CBS_UPHIT				__int64(0x20000000)			// ĂÖÁľ¸íÁßÁˇĽö »ó˝Â
#define CBS_UPATTACK			__int64(0x40000000)			// °ř°Ý·Â(ą°¸®/¸¶ąý) »ó˝Â
#define CBS_CUTDAMAGE			__int64(0x80000000)			// ¸đµç ĂÖÁľÇÇÇŘ °¨ĽŇ
#define CBS_UPXBLOW5			__int64(0x00000001) << 32	// Âü°Ýąßµż Č®·ü Áő°ˇ
#define CBS_UPSTR				__int64(0x00000002) << 32	// 3 Áő°ˇ	BUFF_PAY_UPSTR	60
#define CBS_UPHTH				__int64(0x00000004) << 32	// 5 Áő°ˇ	BUFF_PAY_UPHTH	61
#define CBS_UPINT				__int64(0x00000008) << 32	// 3 Áő°ˇ	BUFF_PAY_UPINT	62
#define CBS_UPWIS				__int64(0x00000010) << 32	// 5 Áő°ˇ	BUFF_PAY_UPWIS	63
#define CBS_UPDEX				__int64(0x00000020) << 32	// 3 Áő°ˇ	BUFF_PAY_UPDEX	64
#define CBS_GUNNERY				__int64(0x00000040) << 32	// Ć÷ş´ĽúŔÇ ˝Ă°ŁÁ¦ ˝Ŕµć
#define CBS_EXPADD110_1			__int64(0x00000080) << 32	// Ář´Ţ·ˇ˛É ŔĚşĄĆ® 1
#define CBS_EXPADD110_2			__int64(0x00000100) << 32	// Ář´Ţ·ˇ˛É ŔĚşĄĆ® 2
#define CBS_EXPADD110_3			__int64(0x00000200) << 32	// Ář´Ţ·ˇ˛É ŔĚşĄĆ® 3
#define CBS_RETURNCOOLTIME		__int64(0x00000400) << 32	// ±ÍČŻ ÄđĹ¸ŔÓ
#define CBS_ATK10				__int64(0x00000800) << 32	// °ř°Ý·Â 10%
#define CBS_POWER_UP			__int64(0x00001000) << 32	// °ř°Ý·Â »ó˝Â.
#define CBS_EXP_UP				__int64(0x00002000) << 32	// °ćÇčÄˇ »ó˝Â.
#define CBS_GUILD_DEF_UP		__int64(0x00004000) << 32	// ±ćµĺąöÇÁ, ąćľî·Â »ó˝Â
#define CBS_BLOW_UP				__int64(0x00008000) << 32	// Ĺ©¸®˝ş¸¶˝ş ŔĚşĄĆ® ľĆŔĚĹŰ ąöÇÁ Âü°Ý ąßµż Č®·ü
#define CBS_PKPENALTY			__int64(0x00010000) << 32	// ŔÚ°´˝Ă˝şĹŰ ĆäłÎĆĽ Ŕűżë 1´Ü°č
//(CBS_PKPENALTY1 | CBS_PKPENALTY2 | CBS_PKPENALTY3 | CBS_PKPENALTY4 | CBS_PKPENALTY5)

// Monster AI
#define AI_NONE				0x00000000
#define AI_PASSIVE			0x00000001
#define AI_AGGRESSIVE		0x00000002

// Item Info
#define ITEM_PUTON			0x00000001
#define ITEM_SETGEM			0x00000002
#define ITEM_ONTRADE		0x00000004
#define ITEM_CHEAT			0x00000008
#define ITEM_STORAGE		0x00000010
#define ITEM_TRANSFORM		0x00000020
#define ITEM_PROTECTED		0x00000040
#define ITEM_OWN			0x00000080

#define ITEM_MIX_DARK		0x00000100	// ľĎČćĽ®	// Á¶ÇŐ˝Ă˝şĹŰ
#define ITEM_MIX_SAINT		0x00000200	// ˝ĹĽşĽ®
#define ITEM_MIX_FLAME		0x00000400	// Č­ż°Ľ®
#define ITEM_MIX_ICE		0x00000800	// şůż°Ľ®
#define ITEM_MIX_LIGHT		0x00001000	// ł«·ÚĽ®
#define ITEM_MIX_POISON		0x00002000	// µ¶żîĽ®
#define ITEM_MIX_PARAL		0x00004000	// ¸¶şńĽ®
#define ITEM_MIX_POWER		0x00008000	// ±âżîĽ®
#define ITEM_MIX_TECH		0x00010000	// ±âĽúĽ®
#define ITEM_MIX_FANTA		0x00020000	// ˝ĹşńĽ®
#define ITEM_MIX_BLOOD		0x00040000	// Ç÷¸¶Ľ®
#define ITEM_MIX_LEVEL1		0x00080000	// ·ąş§1
#define ITEM_MIX_LEVEL2		0x00100000	// ·ąş§2
#define ITEM_MIX_FIREBALL	0x00200000	// Č­ÁÖ


#define ITEM_OWNMASK		( ITEM_CHEAT | ITEM_OWN)
#define ITEM_NOTMOVEMASK	( ITEM_PUTON | ITEM_OWNMASK)
#define ITEM_STORAGEMASK	( ITEM_OWNMASK | ITEM_TRANSFORM | ITEM_PROTECTED)
#define ITEM_MIX			( ITEM_MIX_DARK | ITEM_MIX_SAINT | ITEM_MIX_FLAME | ITEM_MIX_ICE | ITEM_MIX_LIGHT | ITEM_MIX_POISON | ITEM_MIX_PARAL | ITEM_MIX_POWER | ITEM_MIX_TECH | ITEM_MIX_FANTA | ITEM_MIX_BLOOD | ITEM_MIX_FIREBALL)

#define SVMAP_VERSION				1
#define SVMAP_SIZE					(SVMAP_TILE_SIZE * SVMAP_TILE_COUNT) // 8192
#define SVMAP_CELL_COUNT			(SVMAP_TILE_COUNT * SVMAP_CELL_COUNT_PER_TILE) // 1024
#define SVMAP_CELL_COUNT_PER_TILE	(SVMAP_TILE_SIZE / SVMAP_CELL_SIZE)	// 4
#define SVMAP_CELL_SIZE				8
#define SVMAP_TILE_COUNT			256
#define SVMAP_TILE_SIZE				32

#define MAX_PLAYER_SIGHT			500
#define MAX_PLAYER_STEP				128

enum MOVE_ACTION_TYPE
{
	MV_AC_CREATE,
	MV_AC_DELETE,
	MV_AC_MOVE,
	MV_AC_NONE,
};

enum eSeverMapAttr
{
	SMA_NOTMOVEABLE = 0,	// ¸ř°ˇ´Â°÷
	SMA_PORTAL,				// Ć÷Ĺ»ÁöżŞ
	SMA_VILLAGE,			// ¸¶Ŕ»ĽÓĽş
	SMA_SAFETY,				// ľČŔüÁöżŞ
	SMA_ATTACK_CASTLE,		// °řĽşÁöżŞ
	SMA_DEFENCE_CASTLE,		// ĽöĽşÁöżŞ
	SMA_OBJECT				// żŔşęÁ§Ć®ÁöżŞ

	/*
	´řŔü°ú ÇĘµĺŔÇ Ľ­ąö¸Ę ŔĐ´Â ĽřĽ­°ˇ Ć˛¸®´Ů.
	´řŔüżˇĽ­´Â ±âĹ¸ ¸¶Ŕ», ľČŔü, °řĽş, ĽöĽş °ü·ĂÇŃ ĽÓĽşŔ» ľ˛Áö ľĘľĆĽ­ ±×µżľČ ą®Á¦°ˇ ľřľú´ř°Ĺ °°´Ů.
	*/
};

// Class Specialty

// (enum) /////////////////////////////////////////////////////////
enum COUNTRY_CODE
{
	N_KR,
	N_CN,
	N_EN,
};

enum MAP_STATE
{
	MS_NONE,
	MS_QUAKE1,
	MS_QUAKE2,
	MS_QUAKE3,
	MS_QUAKE4,
	MS_TB_CREATE,
};

enum MONSTER_RACE
{
	MR_MAGUNI,
	MR_NOTMAGUNI,
	MR_CASTLESTANDARD,
	MR_CASTLEGATE,
	MR_ITEM,
	MR_MAGIC,
	MR_INACTIVE,
	MR_EGG,
	MR_COCOON,
	MR_FIREFLOWER,
	MR_SIEGEGUN,
	MR_TOWER,
	MR_PRAY,
	MR_PRAYDOOR,
};

enum DROPITEMMASK
{
	G1_WEAPON = 1,
	G1_ARMOR,
	G1_ENCHANT,
	G1_GENERAL,
	G1_ORNAMENT,
	G2W_1HAND = 1,
	G2W_2HAND,
	G2A_MAIN,
	G2A_SUB,
	G2E_PREFIX,
	G2E_UPGRADE,
	G2E_ETC,
	G2G_USABLE,
	G2G_UNUSABLE,
	G2G_QUEST,
	G2G_MONEY,
	G2G_ETC,
	G2O_TRINKET,
	G2O_NECKLACE,
	G2O_RING,
	G3W_SHORT = 1,
	G3W_LONG,
	G3A_UPPER,
	G3A_HELMET,
	G3A_GAUNTLET,
	G3A_BOOTS,
	G3A_LOWER,
	G3A_SHIELD,
	G3A_MASK,
	G3A_FLAG,
	G3A_TRANSFORM,
	G3E_CHARM_WEAPON,
	G3E_CHARM_ARMOR,
	G3E_CHARM_ORNAMENT,
	G3E_CHARM_ATTACK,
	G3E_CHARM_MAGIC,
	G3E_CHARM_DEFENSE,
	G3E_CHARM_HIT,
	G3E_CHARM_DODGE,
	G3E_REPAIRKIT,
	G3E_PROTECT,
	G4A_SWORD = 1,
	G4A_BOW,
	G4A_WAND,
};

enum SKILL_ADD_VALUE
{
	SAV_DAMAGELIGHTNINGADD,
	SAV_DAMAGEWIDEICE,
	SAV_DAMAGEWIDEFIRE,
	SAV_DAMAGEPOISON,
	SAV_HEALINGPARTY,
	SAV_DAMAGESUFFERING,
	SAV_DAMAGESPIRIT,
	SAV_DAMAGEWIDECHAINLIGHTNING,
	SAV_DAMAGEWIDEICEREQUIEM,
	SAV_DAMAGEWIDEEXPLOSIVEBURST,
	SAV_HEALINGPARTYPLUS,
	SAV_HEALINGPARTYINS,
	SAV_DAMAGEPOISONCLOUD,
	SAV_DAMAGEPULLSWING,
	SAV_DAMAGEWIDEMDORAGE,
	SAV_DAMAGEWIDEMDOFURY,
	SAV_DAMAGEWIDEMDOGROUNDFEAL,
	SAV_DAMAGEWIDEMDOASCENSION1,
	SAV_DAMAGEWIDEMDOASCENSION2,
	SAV_DAMAGEWIDETHUNDERSTORM, //ąř°łĆřÇł
	SAV_DAMAGEWIDEICESTORM,     //ľóŔ˝ĆřÇł
	SAV_DAMAGEWIDEFIRERAIN,  	//Č­ż°ĆřÇł
	SAV_DAMAGEWIDEOVERRUN,		//ľî¸Ł˝ĹŔÇşĐłë
	SAV_DAMAGEWIDEMSWIING1,				//ČÖµÎ¸Ł±â1
	SAV_DAMAGEWIDEMSWIING2,				//ČÖµÎ¸Ł±â2
	SAV_DAMAGEWIDEMFURY, 
	SAV_DAMAGEWIDEFIREEXPLOSION,		//Č­ż°ĂĘ Ćřąß
	SAV_DAMAGEWIDESIEGEGUNBALL,			//°řĽşş´±â Ć÷Ĺş Ćřąß
	SAV_DAMAGEWIDEMVACCUMWAVE,			//Ář°řĆÄ
	SAV_DAMAGEWIDEFUJIEXPLOSION,		//ČÄÁö»ęĆřąß
	SAV_DAMAGEWIDEMSPRITOFGROUND,		//´ëÁöŔÇČĄ
	SAV_DAMAGEWIDEMYAMATO,				//ľß¸¶Ĺä Ćřąß
	SAV_DAMAGEWIDEMGHOST,				//±ÍČĄĽú
};

// MLM Flag
enum MLM_FLAG
{
	M_FEE = 0,	// fee
	M_GMASTER,	// great master
	M_MASTER,	// master
	M_FELLA,	// fellas
	M_PUPIL,	// pupils
	// client
	MLM_C_ASK1 = 0,
	MLM_C_INFO,
	MLM_C_ASK2,
	MLM_C_MSG,
	// authsvr
	MLM_A_SET = 0,
	MLM_A_INFO1,
	MLM_A_INFO2,
	MLM_A_RESET,
	MLM_A_SETBREAK,
	// mainsvr
	MLM_M_ASKRELATION = 0,
	MLM_M_REPLYFROMCLNT,
	MLM_M_REPLYFROMAUTH,
	MLM_M_BREAKRELATION,
	MLM_M_INFORELATION,
	MLM_M_CONFIRM,
	MLM_M_SETMSG,
	MLM_M_GETMSG,
	MLM_M_SENDMSG,
	// dbsvr
	MLM_D_INSERT = 0,
	MLM_D_BREAKONPUPIL,
	MLM_D_BREAKONMASTER,
	MLM_D_SAVEFEE,
	MLM_D_SETMSG,
	MLM_D_GETMSG,
	// mlm answer
	MLMA_SETFAIL = 0,
	MLMA_SETFIRST,
	MLMA_SETSECOND,
};

// FRD Flag
enum FRD_FLAG
{
	// msg	
	FRD_MSG_LIMITMAX = 0,   //ŔÎżřÁ¦ÇŃ
	FRD_MSG_ALREADYINSERT,  //ŔĚąĚ µî·ĎµÇľîŔÖŔ˝
	FRD_MSG_NOTEXISTPLAYER, //ľř´ÂÇĂ·ąŔĚľî
	// client
	FRD_C_INSERT = 0, //bdsb
	FRD_C_DELETE,	  //bd
	FRD_C_LIST,	      //bb
	FRD_C_REFRESH,    //bbdb
	// mainsvr
	FRD_M_INSERT = 0, //bs
	FRD_M_DELETE,     //bbd
	FRD_M_PID,
	FRD_M_LOAD,	
	FRD_M_REFRESH,    //b
	// dbsvr
	FRD_D_INSERT = 0,
	FRD_D_DELETE,
	FRD_D_PID,
	FRD_D_LOAD,
};

// MAIL Flag
enum MAIL_FLAG
{
	MAIL_SR_SUCCESS = 0,
	MAIL_SR_LIMITMAX,
	MAIL_SR_NOTEXISTPLAYER,
	MAIL_SR_NOTENOUGHMONEY,
	MAIL_SR_NOTEXISTITEM,
	MAIL_SR_NOTGETMID,
	MAIL_SR_FAILSCANPLAYER,

	MAIL_SFLAG_NONE = 0,
	MAIL_SFLAG_READ,	
	MAIL_SFLAG_SENDPROC,	
	MAIL_SFLAG_ITEMRECVPROC,

	MAIL_SF_SUCCESS = 0,
	MAIL_SF_FAIL,

	MAIL_IRF_SUCCESS = 0,
	MAIL_IRF_FAIL,

	MAIL_CR_ITEMRECVPROC = 1,
	MAIL_CR_ALREADYRETURN,

	// msg
	MAIL_MSG_NEWMAIL = 0,
	MAIL_MSG_RETURN,          //d MID
	MAIL_MSG_DELETE,          //d 
	MAIL_MSG_SENDPROC,        // 
	MAIL_MSG_ITEMRECVPROC,    //d 
	MAIL_MSG_ALREADYRETURN,   //d
	MAIL_MSG_NOTENOUGHMONEY,  //d
	MAIL_MSG_ITEMRECVSUCCESS, //d
	MAIL_MSG_ITEMRECVNOSLOT,  //d
	MAIL_MSG_ITEMATSTALL,  //d

	// Type	
	MAIL_T_GENERAL = 0,
	MAIL_T_PARCEL,
	MAIL_T_RETURN,
	MAIL_T_PAY,	
	MAIL_T_NOTICE,
	// client
	MAIL_C_SEND_RESULT = 0, //bs
	MAIL_C_LIST,            //b dbbbdsdsdddwbdd     
	MAIL_C_MSG,	            //dbdwm or dbdwmwbbdbbbbbbbbbbb
	MAIL_C_UPDATEINFO,      //dbb
	// mainsvr
	MAIL_M_SEND = 0,        //c2s bswm bswmdwbdd
	MAIL_M_SEND_RESULT,	    //d2s
	MAIL_M_REFRESH,         //c2s
	MAIL_M_LOAD,            //d2s    
	MAIL_M_RETURNPROC,      //d2s	
	MAIL_M_CHECK_RESULT,    //d2s
	MAIL_M_GETMSG,          //c2s d
	MAIL_M_SETMSG,          //d2s
	MAIL_M_RETURN,          //c2s d
	MAIL_M_DELETE,          //c2s d
	MAIL_M_ITEMRECV,        //c2s d
	MAIL_M_ITEMRECV_RESULT, //d2s
	// dbsvr
	MAIL_D_SEND = 0,
	MAIL_D_SEND_FLAG,
	MAIL_D_LOAD,
	MAIL_D_RETURNPROC,
	MAIL_D_GETMSG,
	MAIL_D_RETURN,
	MAIL_D_DELETE,
	MAIL_D_ITEMRECV,
	MAIL_D_ITEMRECV_FLAG,
};

// Event Flag
enum EVENT_FLAG
{
	EF_INVALIDCARDID,	// not used
	EF_USEDCARDID,		// not used
	EF_NOMORECHANCE,	// not used
	EF_SUCCESS_CARDEVENT,	// not used
	EF_ALREADYRECOMMAND,	// ŔĚąĚ ´Ů¸Ą °čÁ¤Ŕ» ĂßĂµÇĎĽĚ˝Ŕ´Ď´Ů.
	EF_INVALIDACCOUNT,		// ŔÔ·ÂÇŃ °čÁ¤Ŕş Á¸ŔçÇĎÁö ľĘ°ĹłŞ ŔŻČżÇĎÁö ľĘŔş °čÁ¤ŔÔ´Ď´Ů.
	EF_INVALIDPLAYER,		// ŔĚąĚ ĂßĂµ µÇľî ŔÖ˝Ŕ´Ď´Ů.		<- ŔĚąĚ ĂßĂµ µÇľî ŔÖŔ»¶§ ş¸ł» °Ú˝Ŕ´Ď´Ů.
	EF_NOTNEWACCOUNT,		// ´ç˝ĹŔş ˝Ĺ±Ô °čÁ¤ŔĚ ľĆ´Ő´Ď´Ů.
	EF_SAMEACCOUNT,			// ŔÚ±â ŔÚ˝ĹŔş ĂßĂµÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	EF_SUCCESS_SPONSOREVENT, //ÇŘ´ç °čÁ¤ŔĚ Á¤»óŔűŔ¸·Î ĂßĂµµÇľú˝Ŕ´Ď´Ů. 
	EF_OVERLEVEL10,
	EF_UNDERLEVEL16,
	EF_OVERPUPIL20,
	EF_ALREADYGOTMASTER,
	EF_REJECTEDTOBEMASTER,
	EF_PLAYERALREADYGOTMASTER,
	EF_CANTBREAKRELATION,
	EF_GOTPUPIL,
	EF_GOTMASTER,
	EF_GOT20KMONEYFOR16,
	EF_GOT20KMONEYFORPUPIL16,
	EF_BROKERELATION,
	EF_INVALIDMLMMSG,
	EF_MLMMSGUPDATED,
	EF_UNDERLEVEL10,
	EF_DEFICIENT_DICECOIN,
	EF_SUCCESS_DICEEVENT,
	EF_UNDERLEVEL20,			// ·ąş§ŔĚ 20ŔĚ»óŔĚÁö ľĘŔ»¶§. 
	EF_UNDERLEVEL30,			// ·ąş§ŔĚ 30ŔĚ»óŔĚÁö ľĘŔ»¶§.
	EF_UNDERLEVEL40,			// ĂßĂµŔÚ°ˇ ·ąş§ 40ŔĚ»óŔĚÁö ľĘŔ»‹š.
	EF_NOEVENTUSER,	// ŔĚşĄĆ® Ŕűżë ´ë»óŔĚ ľĆ´Ň¶§
	EF_ITEMRECEIVE,	// ľĆŔĚĹŰ ŔĚąĚ ąŢŔ˝
	EF_LIMITCOUNT,  // Ľ±ÂřĽř Áöł˛
	EF_NOTPLAY,		// ÇĂ·ąŔĚÁßŔĚ ľĆ´Ő´Ď´Ů.		<- Ăß°ˇ
	
	// event bit
	EB_SPONSOR = 1,
	EB_MLM_MASTER = 2,
	EB_MLM_BROKEN = 4,
	// event answer
	EA_FROMDB = 0,
	EA_FROMAUTH,

	// event bit of 1ÁÖłâ ŔĚşĄĆ®
    EB_REST_CHANCE	= 0x00000001,	// ČŢ¸é - ±âČ¸ŔÇ µą
    EB_REST_L17	= 0x00000002,	// ČŢ¸é - LV17ą«±â
    EB_REST_L25	= 0x00000004,	// ČŢ¸é - LV25ą«±â
    EB_REST_L33	= 0x00000008,	// ČŢ¸é - LV33ą«±â
    EB_REST_L40	= 0x00000010,	// ČŢ¸é - LV40ą«±â
	EB_NEW_TELP_1	= 0x00000020,	// ˝Ĺ±Ô - ŔĚµżÁÖą®Ľ­_łŞ·çĹÍ
	EB_NEW_TELP_2	= 0x00000040,	// ˝Ĺ±Ô - ŔĚµżÁÖą®Ľ­_Á×Ľ­ÇĎÁ×Ŕĺ
	EB_NEW_LV20_1	= 0x00000080,	// ˝Ĺ±Ô - LV20´ŢĽş-ą«±â
	EB_NEW_LV20_2	= 0x00000100,	// ˝Ĺ±Ô - LV20´ŢĽş-ąćľî±¸1
	EB_NEW_LV20_3	= 0x00000200,	// ˝Ĺ±Ô - LV20´ŢĽş-ąćľî±¸2
	EB_NEW_LV20_4	= 0x00000400,	// ˝Ĺ±Ô - LV20´ŢĽş-ąćľî±¸3
	EB_NEW_LV20_5	= 0x00000800,	// ˝Ĺ±Ô - LV20´ŢĽş-ąćľî±¸4
	EB_NEW_LV20_6	= 0x00001000,	// ˝Ĺ±Ô - LV20´ŢĽş-ąćľî±¸5

	

};

// Difference Level Type
enum DIFF_LV_TYPE
{
	DLT_GRAY,
	DLT_BLUE,
	DLT_GREEN,
	DLT_YELLOW,
	DLT_ORANGE,
	DLT_RED,
	DLT_VIOLET,
};

// System Code
enum SYS_CODE
{
	SYS_PK,
	SYS_COSMO,
	SYS_BILLING,
	SYS_NMSOCKET,
	SYS_FLAG,	// not used
	SYS_ENG,	// not used
	SYS_FRD,
	SYS_NMBILLING,
	SYS_TESTSRV,
	SYS_WAR,
	SYS_MAIL,
	SYS_GAMBLE,	// µµąÚ˝Ă˝şĹŰ(±ÝŔü±łČŻ, ĹőŔü, KAL21)
	SYS_WAR2,	// Áˇ·ÉŔü 2Â÷ ľ÷µĄŔĚĆ® (°řĽşş´±â)
	SYS_HACKSHIELD,	// HackShieldÇŮ˝Çµĺ
	SYS_HACKSHIELD_PACKET,	// HackShieldÇŮ˝Çµĺ ĆĐĹ¶ ľĎČŁČ­
	SYS_SET_DEFENCE,	// ĽÂĆ® ąćľî±¸,Č­ÁÖ
	SYS_BATTLEFIELD,	// ˝ĂłŞ¸®żŔ3 ŔüąÝŔűŔÎ ˝Ă˝şĹŰ
	SYS_TOWER_CRASH,	// ˝ĂłŞ¸®żŔ3 °ĹÁˇĆÄ±«
	SYS_HONOR,
	SYS_LOAD_PROTECT,	// ˝ĂłŞ¸®żŔ3 ±şÁÖş¸ČŁ
	SYS_SHOWDOWN,		//	°áĹőŔĺ ˝Ă˝şĹŰ.

	SYS_END,
};

// Event Code
enum EVENT_CODE
{
	EVENT_DOUBLEEXP,	// 0
	EVENT_DICE,
	EVENT_MORA,
	EVENT_SPONSOR,
	EVENT_CHANGEFACE,
	EVENT_MLM,			// 5	// don't delete!!!
	EVENT_SNOW,
	EVENT_THXGIVING,
	EVENT_ANNUAL,		// »óżëČ­ 1ÁÖłâ
	EVENT_NEWSERVER,	// ˝Ĺ Ľ­ąö żŔÇÂ
	EVENT_FISHING,		// ł¬˝ĂżŐ ŔĚşĄĆ®...	ĂëĽŇµĘ. 
	EVENT_CRAFTSMAN,	// Á¦ŔŰŔÇ °íĽö ŔĚşĄĆ®
	EVENT_POWERUP,		//	°ř°Ý·Â ľ÷.
	EVENT_EXPUP,		//	°ćÇčÄˇ ľ÷.
	EVENT_NAMCHEON,		// ł˛ĂµĂË ż­¸Ĺ ŔĚşĄĆ®
	EVENT_SNOWFALL,		// ´« ł»¸®±â ŔĚşĄĆ® (ĂµÇĎĹ¸Ľł) 
	EVENT_CHRISTMAS,	// Ĺ©¸®˝ş¸¶˝ş ŔĚşĄĆ® 16 
	EVENT_NEWACCOUNT,	// ŔŻŔú ĂßĂµ ŔĚşĄĆ®		17
	EVENT_SLEEPINGACCOUNT, // ČŢ¸é °čÁ¤ şą±Í ŔĚşĄĆ®	18

	EVENT_END,
};
// Event Mora			( °ˇŔ§ąŮŔ§ş¸ ŔĚşĄĆ® Ĺ¸ŔÔ )
enum EventMora
{
	// Mora
	MORA_KAWI,			//	°ˇŔ§
	MORA_BAWI,			//	ąŮŔ§
	MORA_BO,			//	ş¸
	// C2S
	MORA_IS,			//	°ˇŔ§ąŮŔ§ş¸ °ˇ´ÉÇŃÁö.
	MORA_MORA,			//	°ˇŔ§ąŮŔ§ş¸.
	// S2C
	MORA_TIME,			//	°ˇŔ§ąŮŔ§ş¸ °ˇ´ÉÇŃ ˝Ă°Ł.
	MORA_NO_TIME,		//	°ˇŔ§ąŮŔ§ş¸ şŇ°ˇ´ÉÇŃ ˝Ă°Ł.
	MORA_SHOW,			//	°ˇşßąŮŔ§ş¸ °á°ú.
	MORA_LEVEL_LIMIT,	//	°ˇŔ§ąŮŔ§ş¸ şŇ°ˇ´ÉÇŃ ·ąş§.
};

// ł˛ĂµĂË ż­¸Ĺ ŔĚşĄĆ® 
enum EventNamCheon
{
	NAMCHEON_REFRESH,	// ¸ń·Ď °»˝Ĺ
	NAMCHEON_MOVE,		// ŔĚµż
	NAMCHEON_MOVE_END,	// ŔĚµż żĎ·á
	NAMCHEON_MOVE_FAILED, // ŔĚµż ˝ÇĆĐ
	NAMCHEON_LOGOUT,	// ÇĂ·ąŔĚľî şńÁ˘ĽÓ »óĹÂ
};

// Chatting Type
enum CHAT_TYPE
{
	CHAT_COMMON,
	CHAT_WHISPER,
	CHAT_PARTY,
	CHAT_GUILD,
};

// Base Attribute
enum ATTR
{
	ATTR_PLAYER = 1,
	ATTR_MONSTER,
	ATTR_NPC,
	ATTR_ITEM,
};

// NPC Kind
enum NPC_KIND
{
	NK_MERCHANT,
	NK_INFORMANT,
	NK_GUARD,
	NK_QUEST,
	NK_SCENARIO,
	NK_TELEPORT,
	NK_DOOR,
	NK_SIEGEGUNSTONE,
	NK_RETURNPOINT,
	NK_NEWDOOR,
	NK_BATTLEFIELD,
	NK_MERCHANT_HONOR,
	NK_BATTLEFIELD_DOOR,
};

// Effect Type
enum EFFECT_TYPE
{
	E_NONE,
	E_HP,
	E_MP,
	E_LEVELUP,
	E_CHARM_1,	 //şÎČ°ÁÖą®Ľ­
	E_CHARM_2,	 //°ř°ÝÇâ»óŔÇÁÖą®Ľ­
	E_CHARM_3,     //ÇÇÇŘ°¨ĽŇŔÇÁÖą®Ľ­
	E_CHARM_4,     //°í±ŢÂü°ÝÇâ»óŔÇÁÖą®Ľ­
	E_CHARM_5,     //¸íÁßÇâ»óŔÇÁÖą®Ľ­
	E_CHARM_6,     //Č¸ÇÇÇâ»óŔÇÁÖą®Ľ­
	E_CHARM_7,     //»ó±ŢżĎş®ÇŃąćľîŔÇÁÖą®Ľ­
	E_CHARM_8,     //»ó±ŢĂĽ·ÂČíĽöŔÇÁÖą®Ľ­
	E_POTION_1,    //ČŁ¶űŔĚąßĹéą°ľŕ
	E_POTION_2,    //°ő°ˇÁ×ŔÇą°ľŕ
	E_POTION_3,    //Çö¸íÇÔŔÇą°ľŕ
	E_POTION_4,    //żąÁöŔÇą°ľŕ
	E_POTION_5,    //µ¶Ľö¸®łŻ°łŔÇą°ľŕ
	E_FLUTE_1,	   //żµČĄŔÇ»ÔÇÇ¸®,»ÔÇÇ¸®
	E_STONE_1,     //ľîČąŔÇµą
	E_STONE_2,     //°ćÇčŔÇµą
	E_STONE_3,     //şÎŔŻŔÇµą
	E_LUCKYKEY,
	E_LUCKSTONE,
	E_DAMAGED,
	E_PET_HP,			// Ćę HPÁő°ˇ
	E_PET_MP,			// Ćę MPÁő°ˇ
	E_PET_MINMAXATTACK,	// Ćę ĂÖĽŇ °ř°Ý·ÂÁő°ˇ
	E_PET_DEFENSE,		// Ćę ąćľî·ÂÁő°ˇ
	E_MOD2NDJOB,		// ŔüÁ÷ŔÇ µą
	E_UPPER_CHANCE_STONE,	// ±âČ¸ŔÇ µą
	E_GUNNERY,
	E_MIX_FLAME,	// Č­ż°Ľ®		// Á¶ÇŐ˝Ă˝şĹŰ
	E_MIX_ICE,		// şůż°Ľ®
	E_MIX_LIGHT,	// ł«·ÚĽ®
	E_MIX_POISON,	// µ¶żîĽ®
	E_MIX_PARAL,	// ¸¶şńĽ®
	E_TOOHON,		// »ç·çÁîąĚ - ´ëÁöŔÇČĄ
};

// Wear State
enum WEAR_STATE
{
	WS_WEAPON,
	WS_SHIELD,
	WS_HELMET,
	WS_UPPERARMOR,
	WS_LOWERARMOR,
	WS_GAUNTLET,
	WS_BOOTS,
	WS_RING,
	WS_NECKLACE,
	WS_TRINKET,
	WS_TRANSFORM,
	WS_MASK,
	WS_2HANDWEAPON,
	WS_STANDARD,
};

// player Class
enum PLAYER_CLASS
{
	PC_KNIGHT,
	PC_MAGE,
	PC_ARCHER,
	PC_WARRIOR,
	PC_ASSASSIN,
	PC_TALISMAN,
	PC_SPIRITKNIGHT,
	PC_MONK,
};

// Item Class
enum ITEM_CLASS
{
	IC_WEAPON,
	IC_DEFENSE,
	IC_ORNAMENT,
	IC_GENERAL,
	IC_QUEST,
	IC_MONEY,
	IC_TRANSFORM,
};

enum ITEM_SUBCLASS
{
	ISC_SWORD,
	ISC_WAND,
	ISC_BOW,
	ISC_SHIELD,
	ISC_HELMET,
	ISC_UPPERARMOR,
	ISC_LOWERARMOR,
	ISC_GAUNTLET,
	ISC_BOOTS,
	ISC_RING,
	ISC_NECKLACE,
	ISC_TRINKET,
	ISC_REFRESH,
	ISC_CHARM,
	ISC_GEM,
	ISC_ETC,
	ISC_COIN,
	ISC_COMMON,
	ISC_REPAIR,
	ISC_COCOON,
	ISC_MASK,
	ISC_SWORD2HAND,
	ISC_STANDARD,	
};

// Resist Type
enum RESIST_TYPE
{
	RT_FIRE,
	RT_ICE,
	RT_LITNING,
	RT_CURSE,
	RT_PALSY,
};

// Action
enum ACTION_TYPE
{
	AT_COMMON,
	AT_GENERAL,
	AT_MOVE,
	AT_REST,
	AT_ATTACK,
	AT_SKILL,
	AT_DEFENSE,
	AT_DAMAGE,
	AT_KNEE,
	AT_DIE,
	AT_BEHEADED,
	AT_STALL,
	AT_PRETRANSFORM,
	AT_TRANSFORM,
	AT_REMOVE,
};

// Character Kind
enum CHAR_KIND
{
	CK_PLAYER,
	CK_MONSTER,
	CK_NPC,
	CK_HORSE,
};

// Character Admin Level
enum AdminType
{
	A_USER,
	A_BLOCKED,
	A_RESERVED1,
	A_ADMIN,	// Ĺ×˝şĆ®żë
	A_GM,	// Game Master	
	A_SUPERADMIN,	// °łąßŔÚ
	A_GM2,			// żîżµŔÚ 2
	A_SUPERADMIN2,	// °łąßŔÚ 2
};

enum ANSWER
{
	ANS_ERROR,
	ANS_OK,
	ANS_MLMOK,
	ANS_ERROR_DISSOLUTION,
};

enum LOGIN_ANS
{
	LA_ERROR,
	LA_OK,
	LA_WRONGID,
	LA_WRONGPWD,
	LA_SAMEUSER,
	LA_BLOCKED,
	LA_EXPIRED,
	LA_AGELIMITED,
	LA_NOTPERMITTED,
	LA_LOGINLATER,

	LA_CREATE_SECONDARY=12,
};

enum NEWPLAYER_ANS
{
	NA_ERROR,
	NA_OK,
	NA_WRONGCLASS,
	NA_OVERPLAYERNUM,
	NA_OCCUPIEDID,
	NA_WRONGPROPERTY,
	NA_NOTAVAILABLE,
};

enum COPYPLAYER_ANS
{
	CP_ERROR,
	CP_OK,
	CP_VALIDNAME,
	CP_OVERPLAYERNUM,
	CP_OCCUPIEDNAME,
	CP_INVALIDSERVER,
	CP_INVALIDPLAYER,
	CP_BLOCKEDPLAYER,
};

enum CLOSE_CONNECT
{
	CC_NORMAL,
	CC_KICK,
	CC_SAMEPLAYER,
	CC_SAMEUSER,
	CC_HACK,
	CC_EXPIRED,
	CC_OVERPOPULATION,
	CC_ERROR,
	CC_RELOGINFORCOPYPLAYER,
	CC_RESTOREPLAYER,	// Äł¸Ż şą±¸ ČÄ ¸®Á¶ŔÎÇĎ±âŔ§ÇŘ ż¬°áÇŘÁ¦
	CC_WRONG_PROTOCOL_VERSION,
	CC_DETECTED_HACK,
	CC_CHECKING,
};

enum LOGIN_TYPE
{
	LT_DELETED = 1,
	LT_BLOCKED = 2,
	//	LT_NOTPERMITTED = 4,
	LT_FREE = 8,
	LT_FLATRATE = 16,
	LT_PRORATE = 32,
	//	LT_PFIXCOST = 64,
	//	LT_PFIXAMOUNT = 128,
	LT_HOST = 256,
	LT_PCBANG = 512,
	LT_BILLINGMASK = (LT_PRORATE | LT_FLATRATE),
	LT_AUTHMASK = (LT_FREE | LT_BILLINGMASK),
};

enum TYPE_MAINLOG
{
	TML_PLAYER,	// 0
	TML_DELETEITEM,
	TML_INSERTITEM,
	TML_UPDATEITEMPID,
	TML_UPDATEITEMNUM,
	TML_PUTINSTORAGE,
	TML_PUTOUTSTORAGE,
	TML_QUEST,
	TML_ACCOUNT,
	TML_ENCHANTITEM,
	TML_UPDATETRANSFORM,	// 10
	TML_ALLIANCE,
	TML_CASTLEWAR,
	TML_UPGRADEITEM,
	TML_MAIL,
	TML_STOREDPROC,	// ŔúŔĺÇÁ·Î˝ĂÁ®°ü·Ă
	TML_COPYPLAYER,	// Ĺ×Ľ· ÇĂ·ąŔĚľî şą»ç
};

enum TYTE_LOG					// A : Auth   D : DB
{
	TL_LOGIN,			// 0	// A
	TL_LOGOUT,					// A
	TL_CREATE,					// D ľĆŔĚĹŰ Á¤»ó »ýĽş
	TL_CREATE_CHEAT,			// D ľĆŔĚĹŰ şńÁ¤»ó »ýĽş
	TL_DELETE,					// D ľĆŔĚĹŰ ĆÄ±«
	TL_UPDATEPID,				// D ľĆŔĚĹŰ ĽŇŔŻŔÚ şŻČ­
	TL_UPDATENUM,				// D ľĆŔĚĹŰ °ąĽö şŻČ­
	TL_BUY,						// D ľĆŔĚĹŰ »ç±â
	TL_SELL,					// D ľĆŔĚĹŰ ĆČ±â
	TL_USE,						// D ľĆŔĚĹŰ »çżë
	TL_TRADE,			// 10	// D ľĆŔĚĹŰ °Ĺ·ˇ
	TL_DROP,					// D ľĆŔĚĹŰ ¶ł±¸±â
	TL_PICKUP,					// D ľĆŔĚĹŰ ÁÝ±â
	TL_PERMIT,					// A 
	TL_SKILLUP,					// D ˝şĹł·ąş§ ľ÷
	TL_STORAGE,					// D Ă˘°í
	TL_QUEST,					// D Äů˝şĆ®
	TL_SAVE_SP,					// D ˝şĹł Ć÷ŔÎĆ®
	TL_UPDATE_PRTY,				// D ˝şĹČ ľ÷µĄŔĚĆ® °ü·Ă
	TL_BLOCK,					// A °čÁ¤ şí·°
	TL_FREE,			// 20	// A °čÁ¤ şí·° ÇŘÁ¦
	TL_CHARMING,				// D şÎŔű °˘ŔÎ
	TL_SETGEM,					// D ĽÓĽşŔÇ µą °˘ŔÎ
	TL_UPDATEEND,				// D ł»±¸µµ
	TL_EVENT,					// D ŔĚşĄĆ® °ü·Ă
	TL_PARTYPICKUP,				// D ĆÄĆĽČÄ ľĆŔĚĹŰ ŔçşĐąč
	TL_TRADEBYSTALL,			// D ÁÂĆÇ
	TL_CHANGEPREFIX,			// D Á˘µÎ»ç şÎŔű°˘ŔÎ
	TL_UPDATE_CHEAT,
	TL_EXPLEVEL,				// D 
	TL_SKILLREDISTRIBUTE,// 30	// D 
	TL_GUILD,					// D ±ćµĺ°ü·Ă şńżë
	TL_GUILD_EXP,				// D 
	TL_ALLIANCE_CREATE,			// D 
	TL_ALLIANCE_JOIN,			// D 
	TL_ALLIANCE_DELETE,			// D 
	TL_ALLIANCE_POSTPONE,		// D 
	TL_CASTLEWAR_ADD,			// D 
	TL_CASTLEWAR_END,			// D 
	TL_BLESS,					// D 
	TL_FORCEDIN,		// 40	// D »çÁ¦·Î ľňŔş ŔÚ¸đŔü
	TL_MLM,						// D 
	TL_BUYFORCEDIN,				// D ľĆŔĚĹŰ ŔĺĹÍŔĚżë
	TL_USEPAYITEM,				// D ŔŻ·áľĆŔĚĹŰ »çżë
	TL_UPDATEITEMINFO,			// D ż¬¸¶Á¦ »çżë
	TL_UPGRADE_DESTROY,			// D ş¸Á¤Ľ® ĂßĂâ
	TL_UPGRADE_RATE,			// D 
	TL_UPGRADE_LEVEL,			// D Âü°Ý
	TL_MAIL_SEND,				// D ÂĘÁö ş¸łż
	TL_MAIL_POSTAGEL,			// D ĽŇĆ÷ş¸łľ ¶§ żä±ÝąŢ´Â °Í
	TL_MAIL_ITEMSEND,	// 50	// D ĽŇĆ÷(ľĆŔĚĹŰ µżşŔ)
	TL_MAIL_ITEMRECV,			// D ĽŇĆ÷(ľĆŔĚĹŰ ąŢ±â)
	TL_CHANGEFACE,				// D 
	TL_MOVEITEM,				// SQL ŔúŔĺÇÁ·Î˝ĂÁ® (EXEC MoveItem PID, IID)
								// GETDATE(), nMainType=15, nType=53, nID1=PID, nID2=0, nIID= IID, nVal1=0, nVal2=0, nVal3=0, nVal4=0
	TL_HACKING,
	TL_BATTLEFIELD,				// ŔüŔĺ°ü·Ă
	TL_COPYPLAYER,				// Ĺ×Ľ· ÇĂ·ąŔĚľî şą»ç 
	TL_COPYPLAYERITEM,				// Ĺ×Ľ· ÇĂ·ąŔĚľî şą»ç·Î ľĆŔĚĹŰ »ýĽş 
	TL_CHANGEUSER,				// SQL ŔúŔĺÇÁ·Î˝ĂÁ® (EXEC MoveItem PID, IID)
	TL_CHANGESERVER,				// SQL ŔúŔĺÇÁ·Î˝ĂÁ® (EXEC MoveItem PID, IID)

};

enum PROPERTY_TYPE
{
	P_STR,	// 0
	P_HTH,
	P_INT,
	P_WIS,
	P_DEX,
	P_HP,
	P_MP,
	P_CURHP,
	P_CURMP,
	P_HIT,
	P_DODGE,	// 10
	P_MINATTACK,
	P_MAXATTACK,
	P_MINMAGIC,
	P_MAXMAGIC,
	P_DEFENSE,
	P_ABSORB,
	P_ASPEED,
	P_RESFIRE,
	P_RESICE,
	P_RESLITNING,	// 20
	P_RESCURSE,
	P_RESPALSY,
	P_PUPOINT,		// property upgrade point
	P_SUPOINT,	// skill upgrade point
	P_EXP,
	P_LEVEL,
	P_MINMAXATTACK,
	P_MINMAXMAGIC,
	P_RESISTALL,
	P_CONTRIBUTE,	// 30
	P_FATAL,
	P_MSPEED,
	P_BLOCK,
	P_HASTE,
	P_RAGE,
	P_MORTAL,
	P_HOST,	
	P_RANGE,
	P_MIX,
	P_CURHPR,		// 40
	P_CURMPR,


	P_PREFIX = 0xff,	// maximum
};

enum MESSAGE_TYPE
{
	MSG_SHUTDOWN_MIN,	// 0
	MSG_SHUTDOWN_SEC,
	MSG_SHUTDOWN_NOW,
	MSG_SHUTDOWN_CANCEL,
	MSG_INVALID_NAME,
	MSG_SAMEPLAYERONGAME,
	MSG_BLOCKEDPLAYER,
	MSG_FAILLOADPLAYER,
	MSG_NOTEXISTPLAYER,
	MSG_MOVEHACK,
	MSG_ALREADYPUTON,	// 10
	MSG_CANTDELPUTONITEM,
	MSG_CLASSLIMIT,
	MSG_CANTDROPPUTONITEM,
	MSG_DODGED,	// not use
	MSG_USERCOUNT,
	MSG_USERALLCOUNT,
	MSG_INVENISFULL,	// not use
	MSG_CURRENCY,
	MSG_DESTPLAYERONTRADE,
	MSG_NOTENOUGHPEERINVENSLOT,	// 20
	MSG_INVALID_ITEMLIST,
	MSG_TRADEAGREED,
	MSG_PRIORITYOFITEM,
	MSG_TOOFARFROMME,
	MSG_THEREISNOPLAYER,
	MSG_NEEDPUPOINT,
	MSG_NORIGHTOFPARTYHEAD,
	MSG_ASKJOINPARTY,
	MSG_JOINEDINPARTY,
	MSG_PARTYISFULL,	// 30
	MSG_JOINEDINOTHERPARTY,
	MSG_LEFTPARTY,
	MSG_EXILEDFROMPARTY,
	MSG_REJECTJOINPARTY,
	MSG_BECOMEPARTYHEAD,
	MSG_ENDPARTY,
	MSG_OFFLINE_OUTOFRANGE,
	MSG_SPECIALTYUP,
	MSG_NOTENOUGHSTORSLOT,
	MSG_NOTENOUGHINVENSLOT,	// 40
	MSG_SAVEDREVIVALPT,
	MSG_PARTYMEMGETITEM,
	MSG_EVENTRESULT,
	MSG_FISH_PROGRESS,					//	ł¬˝ĂÁřÇŕąŮ ˝ĂŔŰ¸ŢĽĽÁö.
	MSG_SOLDOUT_SITEM,
	MSG_NOTENOUGH_SITEM,
	MSG_CANTBUY_SITEM,
	MSG_CHANGEDSTALLINFO,
	MSG_COOKING_PROGRESS,				//	żä¸®ÁřÇŕąŮ ˝ĂŔŰ¸ŢĽĽÁö.
	MSG_ALREADYENDEDSTALL,				//	50
	MSG_COOKING_SCARCE_MATERIALS,		//	żä¸®˝Ă Á¶°ÇŔĚ Ľş¸łÇĎÁö ľĘ˝Ŕ´Ď´Ů.
	MSG_CANTPUTONSTALLITEM,
	MSG_ASKREVIVAL,
	MSG_ENCHANTFAILED,
	MSG_GIG_FAIL,						//	ŔŰ»ě ł¬˝Ăżˇ ˝ÇĆĐÇß˝Ŕ´Ď´Ů.
	MSG_REALTIMEEVENT,					//	˝Ç˝Ă°ŁŔĚşĄĆ® ÄˇĆ® ŔŔ´ä.
	MSG_REALTIMEEVENT_START,			//	˝Ç˝Ă°ŁŔĚşĄĆ® ˝ĂŔŰ¸ŢĽĽÁö
	MSG_REALTIMEEVENT_END,				//	˝Ç˝Ă°ŁŔĚşĄĆ® Áľ·á¸ŢĽĽÁö
	MSG_DONEINITSTAT,
	MSG_NOTREADYTOTRADE,	// 60
	MSG_NOTREADYTOPARTY,
	MSG_NOTREADYTOPVP,
	MSG_OFFLINE_OUTOFPVPRANGE,
	MSG_REJECTPVP,
	MSG_ONPVP,
	MSG_NOTENOUGHRAGE,
	MSG_NOTTRANSFORMAREA,
	MSG_INVALIDTILE,
	MSG_TAXRATE,
	MSG_INFOSYS,            // 70
	MSG_REVIVAL_FAIL,
	MSG_CHANT_ALREADYUSE,
	MSG_MLMLOGIN,
	MSG_ADDBSTATE,
	MSG_SUBBSTATE,
	MSG_CANTSAVEREVIVALPT,
	MSG_NOTTRANSFORMBYFLAG,	// ±ęąßÂřżëÁß µĐ°©şŇ°ˇ
	MSG_CANTDROPFLAG,	// ±ęąß Drop şŇ°ˇ
	MSG_PUTOFFAFTER10SEC,	// ±ęąßÂřżëČÄ 10ĂĘ°Ł ąţ±âşŇ°ˇ
	MSG_MYTELEPORTERROR,	// 80
	MSG_UPGRADELEVELSUBMONEY, //ą«±âľ÷±×·ąŔĚµĺ µ·łŞ°¨
	MSG_UPGRADELEVELDESTORY,  //ą«±âľ÷±×·ąŔĚµĺ Äˇ¸íŔű˝ÇĆĐ·Î ĆÄ±«
	MSG_FRD,  //ÄŁ±¸
	MSG_NOTSTALLATCASTLE,
	MSG_MAIL,
	MSG_ITEMMONSTERUSED,		// ş¸ą°»óŔÚ : ´Ů¸Ą »ç¶÷ŔĚ »çżëÁßŔÔ´Ď´Ů
	MSG_ITEMMONSTEROPEN,		// ş¸ą°»óŔÚ : ş¸ą°»óŔÚ¸¦ ż­°í ŔÖ˝Ŕ´Ď´Ů
	MSG_ITEMMONSTEROPENED,		// ş¸ą°»óŔÚ : ş¸ą°»óŔÚ°ˇ ż­·Č˝Ŕ´Ď´Ů
	MSG_ITEMMONSTERCANCELED,	// ş¸ą°»óŔÚ : ş¸ą°»óŔÚ ż­±â°ˇ ĂëĽŇµÇľú˝Ŕ´Ď´Ů
	MSG_LUCKYBLOW,				// ÇŕżîŔÇ ŔĎ°Ý + "b", nLBLevel	// 90
	MSG_ALREADYMIRRORSET,
	MSG_NOMIRROR,
	MSG_MIRRORSET,
	MSG_MIRRORBROKEN,
	MSG_TB_CREATE0,
	MSG_TB_CREATE1,
	MSG_TB_CREATE2,
	MSG_TB_CREATE3,
	MSG_TB_CREATE4,
	MSG_CHANGENAME,	// 100
	MSG_SKILLBUFFALREADYUSE,
	MSG_ALREADYCHANGEDFACE,
	MSG_FAIL_DELETEGUILDMASTER,
	MSG_INSUFFICIENTITEM,
	MSG_REMAINTIME,
	MSG_INIT_2ND_JOB,			// ŔüÁ÷ŔÇ µą, "bb" 0 : żĎ·á,  1 : ˝ÇĆĐ
	MSG_BILLINGEXTENDED,
	MSG_BILLINGTYPECHANGED,
	MSG_NOMOREPUTON,
	MSG_UPPER_CHANCE_STONE,	// 110	// »ó±Ţ±âČ¸ŔÇ µą, "bb" 0 : żĎ·á,  1 : ˝ÇĆĐ
	MSG_EX_GEUMJUN_JAMOJUN,		// "bb"	0:·ąş§Á¦ÇŃ, 1:ŔÚ¸đŔüşÎÁ·, 2:±ÝŔüşÎÁ·, 3:±łČŻĽş¸ł
	MSG_EVENT_LIMIT,	// ŔĚşĄĆ® ´ë»óŔĚ ľĆ´Ô
	MSG_ITEMDROP,		// "bbw"	b:µĺ¶řÇŃ ÁÖĂĽ 0->ľî¸Ł˝Ĺ , w:ItemIndex
	MSG_EXISTPARTYONPK,		// ĆÄĆĽżˇ ŔÚ°´ŔĚ ŔÖľî ŔĚµżşŇ°ˇ
	MSG_NODOORKEY,	//ż­Ľč°ˇ ľř˝Ŕ´Ď´Ů	//"w" ż­Ľčindex
	MGS_DOOROPEN,	//***(ą®ŔĚ¸§)°ˇ ż­¸ł´Ď´Ů.	//"w" NPC ID
	MGS_DOORCLOSE,	//***(ą®ŔĚ¸§)°ˇ ´ÝČü´Ď´Ů.	//"w" NPC ID
	//MSG_SIEGEGUN					//°řĽş ş´±â °ü·Ă ¸ŢĽĽÁö
	MSG_SIEGEGUNSETCANCEL,			//ĽłÄˇ°ˇ ĂëĽŇ µÇľú˝Ŕ´Ď´Ů. 
	MSG_SIEGEGUNIMPOSSIBLE,			//Áö±Ý ĽłÄˇ°ˇ şŇ°ˇ´É ÇŐ´Ď´Ů. 
	MSG_SIEGEGUNUSED,		// 120	//ŔĚąĚ ´Ů¸Ą »ç¶÷ŔĚ ĽłÄˇ ÁßŔÔ´Ď´Ů. 
	MSG_SIEGEGUNUNSETUSED,			//ŔĚąĚ ´Ů¸Ą »ç¶÷ŔĚ ÇŘĂĽ ÁßŔÔ´Ď´Ů.
	MSG_SIEGEGUNSETCLASS,			//şÎŔÇ 1µî±Ţ¸¸ ĽłÄˇ°ˇ °ˇ´ÉÇŐ´Ď´Ů. 
	MSG_SIEGEGUNCONDITION,			//Ŕç·á°ˇ şÎÁ·ÇŐ´Ď´Ů. 

	MSG_SIEGEGUNDIFFERNT,			//´Ů¸Ą şÎŔÇ °řĽş ş´±âŔÔ´Ď´Ů. 
	MSG_SIEGEGUNHANDLING,			//ŔĚąĚ ´Ů¸Ą »ç¶÷ŔĚ Á¶Áľ ÁßŔÔ´Ď´Ů. 
	
	MSG_SIEGEGUNREMOVECLASS,		//şÎŔÇ 1µî±Ţ ¸¸ ÇŘĂĽ ÇŇĽö ŔÖ˝Ŕ´Ď´Ů. 
	MSG_SIEGEGUNREMOVEHANDLING,		//´Ů¸Ą »ç¶÷ŔĚ Á¶Áľ ÁßŔĚ¶óĽ­ ÇŘĂĽ ÇŇĽö ľř˝Ŕ´Ď´Ů. 
	MSG_SIEGEGUNREMOVECANCEL,		//ÇŘĂĽ°ˇ ĂëĽŇ µÇľú˝Ŕ´Ď´Ů. 

	MSG_SIEGEGUNSET,				//ŔĚąĚ °řĽş ş´±â°ˇ ĽłÄˇµÇľî ŔÖ˝Ŕ´Ď´Ů
	MSG_SIEGEGUNNOSKILL,			//°řĽş ş´±â Á¶Áľ ˝şĹłŔĚ ÇĘżäÇŐ´Ď´Ů.
	//130
	MSG_SIEGEGUNGUILD,				//´Ů¸Ą °÷żˇ ŔĚąĚ "%s"şÎŔÇ °řĽş ş´±â°ˇ Á¸ŔçÇŐ´Ď´Ů.   "s", szGuildName	//130
	MSG_SIEGEGUNUNSETIMPOSSIBLE,	//Áö±Ý ÇŘĂĽ°ˇ şŇ°ˇ´É ÇŐ´Ď´Ů. 
	MSG_SIEGEGUNNOTGUILD,			//´Ů¸ĄşÎŔÇ ş´±â´Â ÇŘĂĽÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	MSG_SIEGEGUNNORELATION,			//°řĽşżˇ Âüż©ÇĎ´Â şÎżÍ ±× µż¸ÍşÎ¸¸ ĽłÄˇ°ˇ °ˇ´ÉÇŐ´Ď´Ů.
	MSG_CANTSIEGEITEMUSE,			// "%s"ľĆŔĚĹŰŔş Áˇ·ÉŔüŔĚ ˝ĂŔŰµÇľîľß »çżëŔĚ °ˇ´ÉÇŐ´Ď´Ů.
	MSG_LONGRESTUSER,				// ČŢ¸éŔŻŔú
	MSG_RETURNCOOLTIME,				// °ĹÁˇŔĚµżŔÇ Ŕç»çżë °ˇ´É ˝Ă°ŁŔĚ "%d"şĐ ł˛ľŇ˝Ŕ´Ď´Ů. w:ł˛Ŕş ˝Ă°Ł(şĐ´ÜŔ§)
	MSG_MIXING,						// "b"	0:ľĆŔĚĹŰşÎÁ·/1:Á¶ÇŐ˝ÇĆĐ
	MSG_TOOHONBOSSPOP,				// ĹőČĄŔĚşĄĆ® »ç·çÁîąĚ(ş¸˝ş) ĆË
	//140
	MSG_FIREBALL,					// "b" 0:ŔĺÂřĽş°ř, 1 ŔĺÂř ˝ÇĆĐ, 2 ŔĺÂř´ë»óľĆ´Ô HWC
	MSG_PLAYTIMEWARNING,			// ÇĂ·ąŔĚ˝Ă°Ł 1˝Ă°Ł °ć°ú˝Ă °ć°í
	MGS_NEWDOOROPEN,	//***(ą®ŔĚ¸§)°ˇ ż­¸ł´Ď´Ů.	//"w" NPC ID
	MGS_NEWDOORCLOSE,	//***(ą®ŔĚ¸§)°ˇ ´ÝČü´Ď´Ů.	//"w" NPC ID
	MSG_EVENT_NOTLEVEL,	// ·ąş§ ąĚ´Ţ
	MSG_EVENT_FULL,		// Ľ±ÂřĽř Áöł˛
	MSG_EVENT_RECEIVE,	// ŔĚąĚ ąŢŔ˝
	MSG_LIMIT_BATTLEFIELD,			// ŔüŔĺ ÁřÇŕÁßŔĎ¶§żˇ´Â şŇ°ˇ´ÉÇŐ´Ď´Ů.
	MSG_BATTLEINPARTY,		// ĆÄĆĽżˇ ŔüŔĺÂüż© ŔÎżřŔĚ ŔÖľî ŔĚµżşŇ°ˇ
	MSG_NOPARTYWITHENEMY,			// ŔüŔĺ Âüż©ÁßŔĎ¶§żˇ´Â »ó´ëĆí°ú ĆÄĆĽ°ˇ şŇ°ˇ´É ÇŐ´Ď´Ů.
	//150
	MSG_EVENT_SNOWFALL, // ĂµÇĎĹ¸Ľł ŔĚşĄĆ® ĽöÁ¤ŔĚ 1000°ł ¸đľĆÁ® ´«ŔĚł»¸±¶§
	MSG_ADDBSTATEX,					// 
	MSG_HONORPOINT,			//"ds" ÁˇĽö, Äł¸ŻŔĚ¸§
	MSG_BEFOREWARREMAINSEC,			// "bd"	b:ŔüŔĺÁľ·ů (1:°ĹÁˇĆÄ±« 2:±şÁÖş¸ČŁ..) d:ł˛Ŕş ĂĘ

	MSG_PRAYUSED,		// ±âżřŔÇ»ó : ´Ů¸Ą ÇĂ·ąŔĚľî°ˇ ŔĚąĚ Äł˝şĆĂ Áß.
	MSG_PRAYOPEN,		// ±âżřŔÇ»ó : Äł˝şĆĂ Áß.
	MSG_PRAYOPENED,		// ±âżřŔÇ»ó : Äł˝şĆĂ żĎ·á.
	MSG_PRAYCANCELED,	// ±âżřŔÇ»ó : Äł˝şĆĂ ĂëĽŇ 
	MSG_PRAYALREADY,    // ±âżřŔÇ»ó : »ó´ëĆŔŔĚ ŔĚąĚ ±âżř »óĹÂ.
	MSG_PRAYSTATENOTUSE, // ±âżř»óĹÂ ľĆŔĚĹŰ »çżë X
	MSG_REVIVALITEMNOTUSE, // ±şÁÖ°ˇ şÎČ° ľĆŔĚĹŰŔ» »çżëÇĎ·Á ÇŇ¶§. 
	MSG_REVIVALSKILLNOTUSE,	// şÎČ° ˝şĹł »çżë˝Ă ´ë»óŔĚ ±şÁÖş¸ČŁżˇ Âüż©ÁßŔÎ ±şÁÖ ŔĎ¶§.
};

// ±ćµĺżř µî±Ţ.
enum GUILD_MEMBER_CLASS { 
	GUILD_LEADER = 1, 
	GUILD_SUBLEADER,
	GUILD_CENTURION,
	GUILD_TEN,
	GUILD_REGULAR,
	GUILD_TEMP,
	GUILD_CONSENT,
	GUILD_CONSENT_WAIT,
};

// ±ćµĺżř˝şĹł.
enum GUILD_SKILL {
	GUILD_CONFLUX,			// ÇŐ·ů.
	GUILD_BANISH,			// Ăßąć.
	GUILD_NOTICE,			// °řÁö.
	GUILD_APPOINTMENT,		// ŔÓ¸í.
	GUILD_TITLE,			// Á÷Ŕ§¸í.
};

#define GUILD_SUBLEADER_DEFAULT_SKILL	(1<<GUILD_CONFLUX) + (1<<GUILD_BANISH)
#define GUILD_CENTURION_DEFAULT_SKILL	(1<<GUILD_CONFLUX)
#define GUILD_TEN_DEFAULT_SKILL			(1<<GUILD_CONFLUX)
#define GUILD_REGULAR_DEFAULT_SKILL		0
#define GUILD_TEMP_DEFAULT_SKILL		0


enum GUILD_TYPE
{
	G_MSG,								// ¸ŢĽĽÁö.(żˇ·Ż°°Ŕş...)
	G_CREATE_TRIAL,						// ±ćµĺ»ýĽş ˝ĂŔŰ.
	G_CREATE_CONSENT,					// ±ćµĺ µżŔÇĂ˘.
	G_CREATE_CONSENT_ANSWER,			// ±ćµĺ »ýĽş µżŔÇ ŔŔ´ä.
	G_CREATE_CONSENT_COMPLET,			// ±ćµĺ»ýĽş µżŔÇĽ­ żĎ·á.
	G_CREATE_GUILDNAME,					// ±ćµĺ»ýĽş ŔĚ¸§ĽłÁ¤.
	G_MEMBERINFO,						// ±ćµĺżř Á¤ş¸.
	G_ADMININFO,						// ±ćµĺ°ü¸®Ă˘.
	G_BASICINFO,						// ±ćµĺ±âş»Ă˘.
	G_VIEW,								// ±ćµĺ ŔĚ¸§°ú ą®ŔĺŔ» ş¸ŔĚ´Ů/ľČş¸ŔĚ´Ů
	G_SECESSION,						// ±ćµĺĹ»Ĺđ.
	G_TODAYMESSAGE,						// ±ćµĺ°řÁö
	G_EXPADD,							// ±ćµĺ°ćÇčÄˇĂß°ˇ
	G_SETSKILLABLE,						// ±ćµĺµî±Ţş° ˝şĹł ĽÂ.
	G_CONFLUX,							// ±ćµĺÇŐ·ůĂ˘
	G_CONFLUX_ANSWER,					// ±ćµĺÇŐ·ů ŔŔ´ä.
	G_DISSOLUTION,						// ±ćµĺ ÇŘĂĽ.
	G_ALLIANCEINFO,						// µż¸Í Á¤ş¸.
	G_ALLIANCEANSWER,					// µż¸Í ˝ĹĂ» ŔŔ´ä.
	G_WAR_DECLARE,						// °řĽş Ľ±Ć÷.
	G_WAR_DECLARE_LIST,					// °řĽş ĽöĽş&°řĽş ±ćµĺ ¸®˝şĆ®.
	G_WAR_UNFURL,						// Áˇ·ÉŔü ±ęąß ĽĽżě±â.
	G_WAR_UNFURL_CANCEL,				// Áˇ·ÉŔü ±ęąß ĽĽżě±â ĂëĽŇ.
	G_CASTLEINFO,						// Ľş Á¤ş¸ ş¸±â.
	G_TAX_RATE_CONTROL,					// Ľş ĽĽŔ˛ Á¶Á¤.
	G_CASTLEGATENPC,					// Ľş NPC portal
	G_CASTLEGATE_SETLIMIT,				// Ľşą® NPC »çżëÁ¦ÇŃ ĽÂ.
	G_TAX_LEVY,							// ĽĽ±Ý ÂˇĽö.
	G_CHECK_STANDARD,				// »ýĽş°ˇ´É ±ćµĺ±ęąß Č®ŔÎ
	G_SET_STANDARD,			// ±ćµĺ±ęąß »ýĽş
};

enum GUILD_MSG
{
	GMSG_CONTINUE,
	GMSG_ERROR,
	GMSG_CONNECT,						// ąąąą´ÔŔĚ Á˘ĽÓÇĎż´˝Ŕ´Ď´Ů.
	GMSG_DISCONNECT,					// ąąąą´ÔŔĚ Á˘ĽÓŔ» ˛÷ľú˝Ŕ´Ď´Ů.
	GMSG_NOMEMBER,						// ±ćµĺżřŔĚ ľĆ´Ő´Ď´Ů.
	GMSG_TODAYMESSAGE,					// ±ćµĺ¸ŢĽĽÁö¸¦ ş¸ł˝´Ů.(żŔ´ĂŔÇ ±ćµĺ°řÁö:ąąąąąąąą~~~)
	GMSG_DATE_LIMIT,					// ąąąą´ÔŔş **/**/** **:** ŔĚ ÁöłŞľß ±ćµĺÇŐ·ůłŞ ±ćµĺ»ýĽşŔĚ °ˇ´ÉÇŐ´Ď´Ů.
	GMSG_CREATE_LEVEL_LIMIT,			// ±ćµĺ»ýĽş ·ąş§ŔĚ şÎÁ·ÇŐ´Ď´Ů.
	GMSG_CREATE_MONEY_LIMIT,			// ±ćµĺ»ýĽş şńżëŔĚ şÎÁ·ÇŐ´Ď´Ů.
	GMSG_CREATE_POINT_LIMIT,			// ±ćµĺ»ýĽş °řÇĺµµ°ˇ şÎÁ·ÇŐ´Ď´Ů.
	GMSG_CREATE_NOPARTY,				// ±ćµĺ»ýĽş˝Ă´Â ĆÄĆĽ°ˇ ±¸ĽşµÇľß ÇŐ´Ď´Ů.
	GMSG_CREATE_NOHEAD,					// şÎ´Â żŔÁ÷ ŔĎÇŕŔÇ Ŕĺ¸¸ŔĚ Ľ±Ć÷ÇŇ Ľö ŔÖ˝Ŕ´Ď´Ů. ÇöŔç ´ç˝ĹŔş ŔĎÇŕŔÇ ŔĺŔĚ ľĆ´Ő´Ď´Ů.
	GMSG_CREATE_NOFULLPARTY,			// ĂÖĽŇ 6ŔÎŔÇ ŔĎÇŕŔĚ ĂŁľĆżÍľß şÎŔÇ Ľ±Ć÷°ˇ °ˇ´ÉÇŐ´Ď´Ů.
	GMSG_CREATE_ALREADYMEMBER,			// ŔĎÇŕ ±¸Ľşżř Áß ´©±ş°ˇ°ˇ ŔĚąĚ ´Ů¸Ą şÎżˇ ĽŇĽÓµÇ°ĹłŞ ±ćµĺ»ýĽşÁßŔĚ±â ¶§ą®żˇ şÎŔÇ Ľ±Ć÷°ˇ şŇ°ˇ´ÉÇŐ´Ď´Ů
	GMSG_CREATE_CONSENTWAIT,			// (ŔÓ˝Ă±ćµĺżřµéŔÇ µżŔÇ¸¦ ±â´Ů¸°´Ů.)
	GMSG_CREATE_ALREADYCANCEL,			// ŔĚąĚ ±ćµĺ»ýĽşŔĚ ĂëĽŇ‰ç˝Ŕ´Ď´Ů.
	GMSG_CREATE_ALREADYCONSENT,			// ŔĚąĚ ±ćµĺµżŔÇ¸¦ Çß˝Ŕ´Ď´Ů.
	GMSG_CREATE_CONSENT,				// ±ćµĺ»ýĽş µżŔÇÇŐ´Ď´Ů/µżŔÇÇĎÁö ľĘ˝Ŕ´Ď´Ů.
	GMSG_CREATE_INVALID_NAME,			// »çżëÇŇ Ľöľř´Â ±ćµĺŔĚ¸§ŔÔ´Ď´Ů.
	GMSG_CREATE_SAMENAME,				// ŔĚąĚ »çżëÇĎ°í ŔÖ´Â şÎŔÇ ŔĚ¸§ŔÔ´Ď´Ů. ´Ů˝Ă °áÁ¤ÇŘÁÖĽĽżä.
	GMSG_CREATE_NOT_ALLCONSENT,			// ±ćµĺ µżŔÇĽ­°ˇ żĎ·áµÇÁö ľĘľŇ˝Ŕ´Ď´Ů.
	GMSG_CREATE_COMPLET,				// ąąąą±ćµĺ°ˇ °áĽşµÇľú˝Ŕ´Ď´Ů.
	GMSG_LACK_SKILL,					// ±ÇÇŃŔĚ ľř˝Ŕ´Ď´Ů.
	GMSG_CONFLUX_TEMPMEMBERFULL,		// ŔÓ˝Ă±ćµĺżřĽöŔ» ŔĚ ŔĚ»ó »ĚŔ» Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_CONFLUX_DISCONNECT,			// Á˘ĽÓÇĎÁö ľĘ°ĹłŞ ľř´Â ÇĂ·ąŔĚľîŔÔ´Ď´Ů.
	GMSG_CONFLUX_ALREADYMEMBER,			// ´ë»ó ÇĂ·ąŔĚľî´Â ŔĚąĚ ´Ů¸Ą şÎżˇ ĽŇĽÓµÇ°ĹłŞ ±ćµĺ»ýĽş µżŔÇÁßŔÔ´Ď´Ů.
	GMSG_CONFLUX_OFFER_DISCONNECT,		// °ˇŔÔ˝ĹĂ»ÇŃ ÇĂ·ąŔĚľî°ˇ şńÁ˘ĽÓ»óĹÂŔÔ´Ď´Ů.
	GMSG_CONFLUX_SENDOK,				// ąąąą´Ôżˇ°Ô şÎ °ˇŔÔŔ» ±ÇŔŻÇĎż´˝Ŕ´Ď´Ů.
	GMSG_CONFLUX_CANCEL,				// ąąąą´Ô˛˛Ľ­ ´ç˝ĹŔÇ şÎ °ˇŔÔ ±ÇŔŻ¸¦ °ĹŔýÇĎĽĚ˝Ŕ´Ď´Ů.
	GMSG_CONFLUX_U_ALREADYMEMBER,		// ´ç˝ĹŔş ŔĚąĚ ´Ů¸Ą şÎżˇ ĽŇĽÓµÇ°ĹłŞ ±ćµĺ»ýĽş µżŔÇÁßŔÔ´Ď´Ů.
	GMSG_CONFLUX_COMPLET,				// ±ćµĺżˇ ÇŐ·ůµÇľú˝Ŕ´Ď´Ů.
	GMSG_SECESSION_LEADER,				// ±ć¸¶´Â Ĺ»ĹđÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_SECESSION,						// ąąąą´ÔŔĚ ±ćµĺżˇĽ­ Ĺ»ĹđÇĎż´˝Ŕ´Ď´Ů.
	GMSG_SECESSION_COMPLET,				// ±ćµĺ Ĺ»Ĺđ°ˇ µÇľú˝Ŕ´Ď´Ů.
	GMSG_BANISH_LEADER,					// ±ć¸¶´Â ĂßąćÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_BANISH,						// ąąąą´ÔŔş ±ćµĺżˇĽ­ Ăßąć´çÇß˝Ŕ´Ď´Ů.
	GMSG_BANISH_COMPLET,				// ĂßąćŔĚ µÇľú˝Ŕ´Ď´Ů.
	GMSG_APPOINTMENT_LEADER,			// ±ć¸¶´Â Á÷Ŕ§¸¦ ąŮ˛ÜĽöµµ ŔÓ¸íÇŇĽöµµ ľř˝Ŕ´Ď´Ů.
	GMSG_APPOINTMENT_FULL,				// ´ő ŔĚ»ó ŔÓ¸íÇŇ Ľö ľř´Â Á÷Ŕ§ŔÔ´Ď´Ů.
	GMSG_SUBLEADER_DATE_LIMIT,			// şÎ±ć¸¶´Â ??/??/?? ??:?? ŔĚČÄżˇ ŔÓ¸íŔĚ °ˇ´ÉÇŐ´Ď´Ů.
	GMSG_APPOINTMENT_MEMBERFULL,		// ±ćµĺŔÎżřŔĚ °ˇµćĂŁ˝Ŕ´Ď´Ů.
	GMSG_APPOINTMENT_SAMECLASS,			// ŔÓ¸íÇŇ·Á´Â Á÷±Ţ°ú ÇöŔçŔÇ Á÷±ŢŔĚ °°˝Ŕ´Ď´Ů.
	GMSG_APPOINTMENT_COMPLET,			// ŔÓ¸íŔĚ µÇľú˝Ŕ´Ď´Ů.
	GMSG_DISSOLUTION,					// ±ćµĺ°ˇ ÇŘĂĽµÇľú˝Ŕ´Ď´Ů.
	GMSG_DISSOLUTION_COMPLET,			// ±ćµĺ°ˇ ÇŘĂĽ żĎ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_TITLE_INVALID,					// »çżëÇŇ Ľö ľř´Â ¸íÄŞŔÔ´Ď´Ů.
	GMSG_TITLE_COMPLET,					// ¸íÄŞ şŻ°ćŔĚ żĎ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_SETSKILL_COMPLET,				// ±ćµĺ Á÷Ŕ§±â´É ĽłÁ¤ŔĚ żĎ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_SETSTANDARD_COMPLET,			// ±ćµĺ ą®Ŕĺ ĽłÁ¤ŔĚ żĎ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_SETCONNECTTELL_SAME,			// Á˘ĽÓż©şÎ ĽłÁ¤°ŞŔĚ ÇöŔçżÍ °°˝Ŕ´Ď´Ů.
	GMSG_SETCONNECTTELL_COMPLET,		// Á˘ĽÓż©şÎ ĽłÁ¤ şŻ°ćŔĚ żĎ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_HAVE_NO_EXP,					// ł˛Ŕş °ćÇčÄˇ°ˇ ľř˝Ŕ´Ď´Ů.
	GMSG_EXPADD,						// ąąąą °ćÇčÄˇ¸¦ ĹőŔÚÇß˝Ŕ´Ď´Ů.
	GMSG_EXPFULL,						// şÎ°ćÇčÄˇ¸¦ ´őŔĚ»ó ĹőŔÚ ÇŇ Ľö ľř˝Ŕ´Ď´Ů
	GMSG_MEMBERLEVELUP,					// ¸âąö ·ąş§ľ÷˝Ă ±ćµĺżřµéżˇ°Ô ľË¸°´Ů.
	GMSG_UNKNOWN_CLASS,					// ľË Ľö ľř´Â Á÷±Ţ¸íŔÔ´Ď´Ů.
	GMSG_GUILDNOTICE_INVALID,			// ±ćµĺ°řÁöżˇ´Â ĆŻĽöą®ŔÚ¸¦ »çżëÇŇ Ľö ľř˝Ŕ´Ď´Ů.

	GMSG_SKILL_LEVEL_LIMIT,				// ±ćµĺ·ąş§ŔĚ şÎÁ·ÇŐ´Ď´Ů.
	GMSG_ALLIANCE_U_ALREADY,			// µż¸Í˝ĹĂ»Ŕş şńµż¸ÍÁßŔĚ°ĹłŞ µż¸ÍŔÇ¸ÍÁÖż©ľß ÇŐ´Ď´Ů.
	GMSG_ALLIANCE_INVALID_DATE,			// µż¸Í˝ĹĂ»Ŕş 1ŔĎ°ú 15ŔĎ»çŔĚż©ľß ÇŐ´Ď´Ů.
	GMSG_ALLIANCE_DISCONNECT,			// Á¸ŔçÇĎÁö ľĘ´Â şÎ°ĹłŞ ±şÁÖ°ˇ Á˘ĽÓÇŘŔÖÁö ľĘ˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_ALREADY,				// ŔĚąĚ µż¸ÍÁßŔÔ´Ď´Ů.
	GMSG_ALLIANCE_OFFER,				// ąąąąşÎ°ˇ ąąąą/ąąąą/ąąąą ąąąą:ąąąą ±îÁö µż¸ÍŔ» ˝ĹĂ»Çß˝Ŕ´Ď´Ů. Ľö¶ôÇŇ·ˇ?
	GMSG_ALLIANCE_OFFER_SEND,			// ąąąąşÎżˇ°Ô µż¸ÍŔ» ˝ĹĂ»Çß˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_FULL,					// ´ő ŔĚ»ó µż¸ÍŔ» ÇŇ Ľö°ˇ ľř˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_COMPLET,				// ąąąąşÎ´Â ąąąąşÎŔÇ µż¸Íżˇ ąąąą/ąąąą/ąąąą ąąąą:ąąąą ±îÁöŔÇ µż¸Íżˇ Âüż©Çß˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_CANCEL,				// ąąąąşÎ´Â µż¸ÍŔ» °ĹŔýÇß˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_EXPIRE,				// µż¸Í ±â°ŁŔĚ Áľ·áµÇľú˝Ŕ´Ď´Ů.
	GMSG_ALLIANCE_NO_PERIOD,			// µż¸Í˝ĹĂ»Ŕ» ÇŇ Ľö ľř´Â ±â°ŁŔÔ´Ď´Ů.
	GMSG_ALLIANCE_POSTPONE,				// Áˇ·ÉŔüŔ» Ľ±Ć÷˝Ă µż¸Í±â°ŁŔĚ Áˇ·ÉŔüÁßŔĚąÇ·Î ąąąą/ąąąą/ąąąą ąąąą:ąąąą ±îÁö ż¬ŔĺµË´Ď´Ů.

	GMSG_WARDECLARE_NO_PERIOD,			// Áˇ·ÉŔü ˝ĹĂ»±â°ŁŔĚ ľĆ´Ő´Ď´Ů.
	GMSG_WARDECLARE_NO_LEADER,			// µż¸Í˝Ă´Â ¸ÍÁÖ¸¸ŔĚ Áˇ·ÉŔüŔ» ˝ĹĂ»ÇŇ Ľö ŔÖ˝Ŕ´Ď´Ů.
	GMSG_WARDECLARE_LORD,				// ´ç˝ĹŔÇ ĽşŔÔ´Ď´Ů.
	GMSG_WARDECLARE_ALLIANCE,			// ĽşÁÖżÍ µż¸Í°ü°čŔÔ´Ď´Ů.
	GMSG_WARDECLARE_MONEY_LIMIT,		// Áˇ·ÉŔü şńżëŔĚ şÎÁ·ÇŐ´Ď´Ů.
	GMSG_WARDECLARE_ALREADYDECLARE,		// ŔĚąĚ Áˇ·ÉŔüŔ» Ľ±Ć÷ÇĎż´˝Ŕ´Ď´Ů.
	GMSG_WARDECLARE,					// ąąąąşÎ°ˇ ąąąąĽşżˇ Áˇ·ÉŔüŔ» Ľ±Ć÷Çß˝Ŕ´Ď´Ů.
	GMSG_WARDECLARE_COUNT_OVER,			// ´ő ŔĚ»ó Áˇ·ÉŔü ˝ĹĂ»Ŕ» ąŢŔ» Ľö ľř˝Ŕ´Ď´Ů.

	GMSG_WARBEGIN,						// ąąąąĽşŔÇ Áˇ·ÉŔüŔĚ ˝ĂŔŰ‰ç˝Ŕ´Ď´Ů.
	GMSG_WAREND_WIN,					// ąąąąĽşŔÇ Áˇ·ÉŔüżˇ ˝Â¸®ÇĎż´˝Ŕ´Ď´Ů.
	GMSG_WAREND_LOSE,					// ąąąąĽşŔÇ Áˇ·ÉŔüżˇ ĆĐÇĎż´˝Ŕ´Ď´Ů.
	GMSG_WARUNFURL_NO_DECLARE,			// Áˇ·ÉŔüŔ» Ľ±Ć÷ÇŃ °÷ŔĚ ľĆ´Ő´Ď´Ů.
	GMSG_WARUNFURL_ALREADY,				// ŔĚąĚ ±â¸¦ ĽĽżě´Â ÁßŔÔ´Ď´Ů.
	GMSG_WARUNFURL_STANDARDLIVE,		// ±ęąßŔĚ ĆÄ±«µÇ±â Ŕüżˇ´Â ĽłÄˇÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_WAR_UNFURLSTANDARD_BEGIN,		// ±â¸¦ »őżě±â ˝ĂŔŰ.
	GMSG_WAR_UNFUELCOMPLET,				// XXX şÎ°ˇ XXX Ľşżˇ ±ęąßŔ» ĽłÄˇÇĎż´˝Ŕ´Ď´Ů.

	GMSG_TAX_NO_LORD,					// ĽşÁÖ°ˇ ľĆ´Ő´Ď´Ů.
	GMSG_TAX_DEVIATE,					// ĽĽŔ˛Á¶Á¤ ąüŔ§¸¦ ąţľîłµ˝Ŕ´Ď´Ů.
	GMSG_TAX_SET_RATE_COMPLET,			// ĽĽŔ˛Á¶Á¤ŔĚ żĎ·á‰ç˝Ŕ´Ď´Ů.

	GMSG_GATE_LIMIT,					// ŔĚµżÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_SET_GATELIMIT_COMPLET,			// Ľşą® Á¦ÇŃ ĽłÁ¤ŔĚ żĎ·áµÇľú˝Ŕ´Ď´Ů.

	GMSG_WAR_NOPERIOD,					// Áˇ·ÉŔüÁßŔĚ ľĆ´Ő´Ď´Ů.
	GMSG_WAR_NO_LEADER,					// µż¸ÍŔÇ ¸ÍÁÖ°ˇ ľĆ´Ő´Ď´Ů.
	GMSG_WAR_NO_RELATION,				// Áˇ·ÉŔü°ú °ü·ĂŔĚ ľř´Â °ü°čŔÔ´Ď´Ů.
	GMSG_CONFLUX_NOPERIOD,				// şÎ °ˇŔÔ ±ÇŔŻ´Â Áˇ·ÉŔüżˇ °řĽş Č¤Ŕş ĽöĽşĂřŔ¸·Î Âüż© ÁßŔÎ şÎ´Â Áˇ·ÉŔü±â°Ł, Áˇ·ÉŔü ÁŘşń±â°Łżˇ´Â ÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_WARUNFURL_U_ALREADY,			// ´Ů¸Ą şÎ°ˇ ¸ŐŔú ±ęąßŔ» ĽłÄˇÇĎ´Â ÁßŔÔ´Ď´Ů. Áö±ÝŔş ĽłÄˇÇŇ Ľö ľř˝Ŕ´Ď´Ů.

	GMSG_GATE_LIMIT_GUILD,				// ĽşŔ» Áˇ·ÉÇŃ şÎŔÇ ±¸Ľşżř¸¸ »çżëÇŇ Ľö ŔÖ˝Ŕ´Ď´Ů.
	GMSG_GATE_LIMIT_ALLIANCE,			// ĽşŔ» Áˇ·ÉÇŃ şÎŔÇ ±¸Ľşżř°ú µż¸Í şÎŔÇ ±¸Ľşżř¸¸ »çżëÇŇ Ľö ŔÖ˝Ŕ´Ď´Ů

	GMSG_WAR_BROKEN_STANDARD,			// XXXĽşŔÇ XXX şÎŔÇ ±ęąßŔĚ ĆÄ±« µÇľú˝Ŕ´Ď´Ů bbdsb
	GMSG_WAR_BROKEN_GATE,				// XXXĽşŔÇ ąąąą Ľşą®ŔĚ ĆÄ±« µÇľú˝Ŕ´Ď´Ů
	GMSG_WAR_TIME,						// Áˇ·ÉŔü Áľ·á˝Ă°ŁŔĚ ąąąą(şĐ/ĂĘ) ł˛ľŇ˝Ŕ´Ď´Ů.
	GMSG_TAX_LEVY,						// ĽĽ±ÝŔĚ ??Ŕü ÂˇĽöµÇľú˝Ŕ´Ď´Ů.
	GMSG_SETSTANDARD_FAILED,		// şÎ ą®Ŕĺ Áßşą (ą®Ŕĺ ĽłÁ¤ ˝ÇĆĐ)
	GMSG_SETSTANDARD_FAILEDBYLEVEL,		// ĽłÁ¤ ±ćµĺ·ąş§ Á¦ÇŃ
	GMSG_WAR_LORDDECLARE_TIME,			// ±şÁÖĽ±ľđł˛Ŕş ˝Ă°Ł	bbbb
	GMSG_WAR_EXTENDED_TIME,				// °řĽşŔü ż¬Ŕĺ			bb
	GMSG_WAR_CHANGELORD,				// ĽşÁÖ°ˇ ąŮ˛îľú˝Ŕ´Ď´Ů. bbds
	GMSG_DISSOLUTION_FAIL,			// ĽşŔ» Áˇ·ÉÇŃ şÎłŞ °řĽşŔüŔ» ˝ĹĂ»ÇŃ şÎ´Â ÇŘĂĽ¸¦ ÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_DISSOLUTION_FAIL_BATTLE,			// ŔüŔĺÂüż©¸¦ ˝ĹĂ»ÇŃ şÎ´Â ÇŘĂĽ¸¦ ÇŇ Ľö ľř˝Ŕ´Ď´Ů.
	GMSG_SECESSION_FAIL_BATTLE,			// ŔüŔĺÂüż©¸®˝şĆ®żˇ µî·ĎµČ ±ćµĺżřŔş Ĺ»Ĺđ°ˇ şŇ°ˇ´ÉÇŐ´Ď´Ů.
};

enum PK_MSG
{
	PKMSG_ONPK,                         //b  1´ç˝ĹŔş ŔÚ°´ »óĹÂ°ˇ µÇľú˝Ŕ´Ď´Ů.
	PKMSG_ONPKAROUND,                   //b  1±ŮĂłżˇ ´©±ş°ˇ°ˇ Ĺ»Ŕ» »çżëÇĎ°í ŔÖ˝Ŕ´Ď´Ů.
	PKMSG_ONPKDIE,                      //b  1´ç˝ĹŔş ŔÚ°´ »óĹÂżˇĽ­ Á×ŔÓŔ» ´çÇĎż´˝Ŕ´Ď´Ů.
	PKMSG_PKDIE,                        //bd 1´ç˝ĹŔş ŔÚ°´ XXXżˇ°Ô Á×ŔÓŔ» ´çÇĎż´˝Ŕ´Ď´Ů.
	PKMSG_OFFPK,                        //b  1´ç˝ĹŔş ŔÚ°´ »óĹÂ¸¦ ÇŘÁ¦ÇĎż´˝Ŕ´Ď´Ů.
	PKMSG_ONPKKILL,                     //bd 1´ç˝ĹŔş ŔÚ°´ XXX ¸¦ Ă´»ěÇĎż© ±×¸íĽşŔ» ł˛°ĺ˝Ŕ´Ď´Ů. ´ç˝ĹŔÇ °řÇĺŔş ąćżˇ °ř°í µË´Ď´Ů.
	PKMSG_LIMIT_OFFPKTICK,              //b  1ŔÚ°´ »óĹÂ´Â Ľ±ľđ ČÄ 1˝Ă°Ł, Č¤Ŕş ¸¶Á÷¸· °ř°Ý ČÄ 180ĂĘ µżľČ »óĹÂşŻ°ćŔ» ÇŇĽö ľř˝Ŕ´Ď´Ů.	
	PKMSG_LIMIT_TRADESELF,              //b  1ŔÚ°´ »óĹÂżˇĽ­´Â ´Ů¸Ą »ç¶÷żˇ°Ô °Ĺ·ˇ¸¦ ˝ĹĂ»ÇŇ Ľö ľř˝Ŕ´Ď´Ů. ¸ŐŔú ŔÚ°´ »óĹÂ¸¦ ÇŘÁ¦ÇŘľß ÇŐ´Ď´Ů. 
	PKMSG_LIMIT_TRADEOTHER,             //b  1ŔÚ°´ »óĹÂŔÇ ´ë»óżˇ°Ô´Â °Ĺ·ˇ°ˇ şŇ°ˇ´ÉÇŐ´Ď´Ů.
};

enum SL_SECONDARY_LOGIN
{
	SL_CREATE_PASSWORD=1,
	SL_LOGIN=0,
	SL_CHANGE_PASSWORD=2,
	SL_RESULT_MSG=3,
};

enum MSL_SECONDARY_MSG
{
	MSL_NONE,
	MSL_WRONG_PWD,
	MSL_PWD_8_DIGIT_NUMBER=3,
	MSL_BLOCK,
	MSL_ALREADY_PWD,
	MSL_CREATE_PWD,
	MSL_SUCCESS,
};

enum MOVE_TYPE
{
	MOVE_ON,
	MOVE_STOP,
};
#endif