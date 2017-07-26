# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`MONSTER_WALK_FREQUENCY`](#CMonster_8h_1a5b7eae3edb8b301b111c691bc53249f9)            | 
`define `[`MONSTER_WALK_TIME`](#CMonster_8h_1a689452730e78553fb130430444bfc605)            | 
`define `[`GEAR_NUM`](#CPlayer_8h_1ac2937dbb016e4437d5968d8d0aa230ad)            | 
`define `[`GEAR_VISIBLE_NUM`](#CPlayer_8h_1afe2cd4d1aad191fa9c2f5f1ae8b49a43)            | 
`define `[`ITEMTELEPORT_SPREAD`](#CItemTeleport_8cpp_1a6dc574b58efc9343be55a5512c3709bc)            | 
`define `[`TILE_LEN`](#CMap_8h_1abcef8203a5d63d217f2eee1303fb4b16)            | 
`define `[`ZONE_LEN`](#CMap_8h_1ae22f41e367b754418baa5a4a3f264ca9)            | 
`define `[`KSM_WIDTH`](#CZone_8h_1aec138258fe2f35694f1e8543253b5a56)            | 
`define `[`KSM_CELL_SIZE`](#CZone_8h_1a4030a22cb3af9e4fcd9b5d0b799c34dc)            | 
`define `[`KSM_HEADER_SIZE`](#CZone_8h_1aefad18939d0adc4bc626995c09f7f222)            | 
`define `[`KSM_TOTAL_CELLS_SIZE`](#CZone_8h_1ab25e6d52b9d4b44ab7645f384013894a)            | 
`define `[`KSM_TOTAL_SIZE`](#CZone_8h_1aac04854d5b8f1507064f1c85b9c37df0)            | 
`enum `[`TELEPORT`](#CItemTeleport_8h_1a041cbfc9d31c82a29012d10a8ebf3259)            | 
`public int `[`main`](#DBServer_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | 
`public int `[`main`](#MainServer_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | 
`class `[`CAccount`](#classCAccount) | 
`class `[`CCharacter`](#classCCharacter) | 
`class `[`CClient`](#classCClient) | 
`class `[`CClientSocket`](#classCClientSocket) | 
`class `[`CDatabase`](#classCDatabase) | 
`class `[`CDBSocket`](#classCDBSocket) | 
`class `[`CItem`](#classCItem) | 
`class `[`CItemDefense`](#classCItemDefense) | 
`class `[`CItemDrop`](#classCItemDrop) | 
`class `[`CItemGeneral`](#classCItemGeneral) | 
`class `[`CItemOrnament`](#classCItemOrnament) | 
`class `[`CItemPet`](#classCItemPet) | 
`class `[`CItemRefresh`](#classCItemRefresh) | 
`class `[`CItemRide`](#classCItemRide) | 
`class `[`CItemTeleport`](#classCItemTeleport) | 
`class `[`CItemTransform`](#classCItemTransform) | 
`class `[`CItemWeapon`](#classCItemWeapon) | 
`class `[`CItemYinyang`](#classCItemYinyang) | 
`class `[`CMacroDB`](#classCMacroDB) | 
`class `[`CMainSocket`](#classCMainSocket) | 
`class `[`CMap`](#classCMap) | 
`class `[`CMonster`](#classCMonster) | 
`class `[`CMonsterMaguni`](#classCMonsterMaguni) | 
`class `[`CMonsterReal`](#classCMonsterReal) | 
`class `[`CNPC`](#classCNPC) | Class representation of NPC such as merchants and more.
`class `[`CParty`](#classCParty) | Class representation of ingame Party. Group of Players playing together.
`class `[`CPlayer`](#classCPlayer) | 
`class `[`CServer`](#classCServer) | 
`class `[`CTile`](#classCTile) | Represents square tile of 1024x1024 cells. Keeps track of all dynamic objects on that area.
`class `[`CZone`](#classCZone) | Represents square zone of 8192x8192 cells. Encapsulates one .KSM (Kal Server Map) file per instance.
`struct `[`CItemInfo`](#structCItemInfo) | 
`struct `[`CMacro`](#structCMacro) | 
`struct `[`CMonsterInfo`](#structCMonsterInfo) | 
`struct `[`MapInfo`](#structMapInfo) | 

## Members

#### `define `[`MONSTER_WALK_FREQUENCY`](#CMonster_8h_1a5b7eae3edb8b301b111c691bc53249f9) 

#### `define `[`MONSTER_WALK_TIME`](#CMonster_8h_1a689452730e78553fb130430444bfc605) 

#### `define `[`GEAR_NUM`](#CPlayer_8h_1ac2937dbb016e4437d5968d8d0aa230ad) 

#### `define `[`GEAR_VISIBLE_NUM`](#CPlayer_8h_1afe2cd4d1aad191fa9c2f5f1ae8b49a43) 

#### `define `[`ITEMTELEPORT_SPREAD`](#CItemTeleport_8cpp_1a6dc574b58efc9343be55a5512c3709bc) 

#### `define `[`TILE_LEN`](#CMap_8h_1abcef8203a5d63d217f2eee1303fb4b16) 

#### `define `[`ZONE_LEN`](#CMap_8h_1ae22f41e367b754418baa5a4a3f264ca9) 

#### `define `[`KSM_WIDTH`](#CZone_8h_1aec138258fe2f35694f1e8543253b5a56) 

#### `define `[`KSM_CELL_SIZE`](#CZone_8h_1a4030a22cb3af9e4fcd9b5d0b799c34dc) 

#### `define `[`KSM_HEADER_SIZE`](#CZone_8h_1aefad18939d0adc4bc626995c09f7f222) 

#### `define `[`KSM_TOTAL_CELLS_SIZE`](#CZone_8h_1ab25e6d52b9d4b44ab7645f384013894a) 

#### `define `[`KSM_TOTAL_SIZE`](#CZone_8h_1aac04854d5b8f1507064f1c85b9c37df0) 

#### `enum `[`TELEPORT`](#CItemTeleport_8h_1a041cbfc9d31c82a29012d10a8ebf3259) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NARO            | 
CARGO            | 
GEUM            | 
PUB            | 
TEMP            | 
PRIEST            | 
CHEONJI            | 
HONDEL            | 

#### `public int `[`main`](#DBServer_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

#### `public int `[`main`](#MainServer_2main_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

# class `CAccount` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Access `[`m_Access`](#classCAccount_1aeadec51d154df15e0527a084cc7552d8) | 
`public inline  `[`CAccount`](#classCAccount_1a71fcf22852f152f88fc3eec7d3b1dece)`(int nClientID,int nAccountID,std::string szLogin,std::string szPassword,std::string szSecondary)` | 
`public  `[`~CAccount`](#classCAccount_1aea90b7725a7f2dca17b24e8010735b11)`()` | 
`public inline void `[`Lock`](#classCAccount_1a5d01c40991060a6d15a3da34ce5a2efd)`()` | 
`public inline void `[`Unlock`](#classCAccount_1a0585bc1edbc5a884da2107ab02d0325d)`()` | 
`public inline int `[`GetAID`](#classCAccount_1a9a5e97de4d010c2d6ec3438e13f25340)`() const` | 
`public inline int `[`GetCID`](#classCAccount_1a08bd903c24ad2231c7368aa0ac9f1e7e)`() const` | 
`public inline std::string `[`GetLogin`](#classCAccount_1ab9909b5e60335e30fc8f50084865b521)`() const` | 
`public inline std::string `[`GetPassword`](#classCAccount_1a34c3797b77cf1f80e6d8d0db8d3e366b)`() const` | 
`public inline std::string `[`GetSecondary`](#classCAccount_1a5bee37079ee7d004de3afdaaed9ab46d)`() const` | 
`public inline void `[`SetSecondary`](#classCAccount_1a3224a50f3a821e05526cd0ddcd6d0d87)`(std::string szSecondary)` | 
`public void `[`SendPlayerInfo`](#classCAccount_1a5082d85afb038c010d4a4cda8eddcb4e)`(Connection_T con)` | 

## Members

#### `public Access `[`m_Access`](#classCAccount_1aeadec51d154df15e0527a084cc7552d8) 

#### `public inline  `[`CAccount`](#classCAccount_1a71fcf22852f152f88fc3eec7d3b1dece)`(int nClientID,int nAccountID,std::string szLogin,std::string szPassword,std::string szSecondary)` 

#### `public  `[`~CAccount`](#classCAccount_1aea90b7725a7f2dca17b24e8010735b11)`()` 

#### `public inline void `[`Lock`](#classCAccount_1a5d01c40991060a6d15a3da34ce5a2efd)`()` 

#### `public inline void `[`Unlock`](#classCAccount_1a0585bc1edbc5a884da2107ab02d0325d)`()` 

#### `public inline int `[`GetAID`](#classCAccount_1a9a5e97de4d010c2d6ec3438e13f25340)`() const` 

#### `public inline int `[`GetCID`](#classCAccount_1a08bd903c24ad2231c7368aa0ac9f1e7e)`() const` 

#### `public inline std::string `[`GetLogin`](#classCAccount_1ab9909b5e60335e30fc8f50084865b521)`() const` 

#### `public inline std::string `[`GetPassword`](#classCAccount_1a34c3797b77cf1f80e6d8d0db8d3e366b)`() const` 

#### `public inline std::string `[`GetSecondary`](#classCAccount_1a5bee37079ee7d004de3afdaaed9ab46d)`() const` 

#### `public inline void `[`SetSecondary`](#classCAccount_1a3224a50f3a821e05526cd0ddcd6d0d87)`(std::string szSecondary)` 

#### `public void `[`SendPlayerInfo`](#classCAccount_1a5082d85afb038c010d4a4cda8eddcb4e)`(Connection_T con)` 

# class `CCharacter` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Access `[`m_Access`](#classCCharacter_1a7c09b343980598688a971ce13995b884) | 
`public  `[`CCharacter`](#classCCharacter_1a94574d74f605d70d70acb96e01233adf)`()` | 
`public inline void `[`Lock`](#classCCharacter_1a1c3cf4b18b5fc184d62770f10fa81851)`()` | 
`public inline void `[`Unlock`](#classCCharacter_1a75454c5b85705b5f118bfb775085ae76)`()` | 
`public inline int `[`GetID`](#classCCharacter_1ad7f5f1742dc177fd2209648690b30190)`() const` | 
`public inline BYTE `[`GetKind`](#classCCharacter_1af268189e36a1bea406a5bbaa6670302d)`() const` | 
`public inline BYTE `[`GetClass`](#classCCharacter_1ad23b140d84b130c0424bfa334972fb0e)`() const` | 
`public inline virtual WORD `[`GetStr`](#classCCharacter_1a58744cb98cc68993d943e0ec2647306a)`() const` | 
`public inline virtual WORD `[`GetHth`](#classCCharacter_1a5240b51c5308228a33ba02e9f1dd2279)`() const` | 
`public inline virtual WORD `[`GetInt`](#classCCharacter_1aa6d3cd9981516a834e16bf7b1158c224)`() const` | 
`public inline virtual WORD `[`GetWis`](#classCCharacter_1ab5a1b339e78d7581131aaf19fc398b06)`() const` | 
`public inline virtual WORD `[`GetAgi`](#classCCharacter_1a60ed981680f1ae170d8f94f44accf080)`() const` | 
`public inline DWORD `[`GetCurHP`](#classCCharacter_1a15ad355680c7702eb4b1e86e5df5d118)`() const` | 
`public inline WORD `[`GetCurMP`](#classCCharacter_1a8eeda86886aa7c0a652109823190fe89)`() const` | 
`public inline virtual DWORD `[`GetMaxHP`](#classCCharacter_1a2c280eb02bd39dd245b48370db35ee2b)`() const` | 
`public inline virtual WORD `[`GetMaxMP`](#classCCharacter_1a210fba6eac3e87aae59c681195c48369)`() const` | 
`public inline int `[`GetX`](#classCCharacter_1ab43af4e964cc23dde5b75840a77acd5e)`() const` | 
`public inline int `[`GetY`](#classCCharacter_1a849ceb26d2c01ec720f2fbd8ab1619d4)`() const` | 
`public inline int `[`GetZ`](#classCCharacter_1a74b10ffeef48e680bca8c761d84aca29)`() const` | 
`public inline WORD `[`GetDir`](#classCCharacter_1ac8b2b38e896c0b82210a7c2d6b2c67d4)`() const` | 
`public inline virtual BYTE `[`GetLevel`](#classCCharacter_1a377cc0f6a658e0416c742ccdcad4372f)`() const` | 
`public inline virtual WORD `[`GetHit`](#classCCharacter_1a56435a6058690cffe37840e76eeeca87)`() const` | 
`public inline virtual WORD `[`GetDodge`](#classCCharacter_1afff27b3e1caa3764f7a23f0d927e5af7)`() const` | 
`public inline virtual WORD `[`GetDefense`](#classCCharacter_1a9ec02921a5e7286d0a09ca33cbff156b)`(BYTE byType) const` | 
`public inline virtual BYTE `[`GetAbsorb`](#classCCharacter_1a7e86accfee142376c3799f59aaaa0b7e)`() const` | 
`public inline virtual WORD `[`GetMinAttack`](#classCCharacter_1a7e9ccca9b9c5515fb358829cd1ca3db6)`() const` | 
`public inline virtual WORD `[`GetMaxAttack`](#classCCharacter_1a72aca8cd8b2f435ea57c842fa6c06991)`() const` | 
`public inline virtual WORD `[`GetMinMagic`](#classCCharacter_1ae5f14202b5ee6c43930462b7c9632d30)`() const` | 
`public inline virtual WORD `[`GetMaxMagic`](#classCCharacter_1a1fc2bd31eea1bc2907077a5dd8e9fdf8)`() const` | 
`public inline virtual WORD `[`GetResist`](#classCCharacter_1ad1b2b1bc32824f8b446e04e59079caab)`(BYTE byResist) const` | 
`public inline virtual WORD `[`GetSize`](#classCCharacter_1a109680868eaafda26341c7b07f4abf23)`() const` | 
`public WORD `[`GetAttack`](#classCCharacter_1a013683c064c423fd17bb13e5b5ba7e1a)`() const` | 
`public WORD `[`GetMagic`](#classCCharacter_1a9445d97edb6bf4787086ba0a6ebcdb8a)`() const` | 
`public virtual bool `[`CanAttack`](#classCCharacter_1aa1c9b59cfacc095884265e95eee69194)`(CCharacter * pTarget) const` | 
`public virtual bool `[`CheckHit`](#classCCharacter_1aaf781230de62a807fcdcb79022777006)`(CCharacter * pTarget,int nAdd) const` | 
`public inline virtual bool `[`CheckBlock`](#classCCharacter_1a398efeea83df4f2349a38737c11f8158)`(CCharacter * pAttacker) const` | 
`public DWORD `[`GetFinalDamage`](#classCCharacter_1a957de429305b2f9de1e524491c729e54)`(CCharacter * pAttacker,DWORD dwDamage,BYTE byType)` | 
`public DWORD `[`GetFatalDamage`](#classCCharacter_1ae9c0dcc3311ba9e68217404cfb0f85b1)`(DWORD dwFinalDamage,BYTE & byType)` | 
`public inline __int64 `[`GetGState`](#classCCharacter_1abb9fb45114752bd3e127c79e32d3b5f4)`() const` | 
`public inline __int64 `[`GetMState`](#classCCharacter_1aa0a340e1becaead14f794ff013f39cae)`() const` | 
`public inline __int64 `[`GetGStateEx`](#classCCharacter_1aa8f2c178d15eda870a7ac001069cfd03)`() const` | 
`public inline __int64 `[`GetMStateEx`](#classCCharacter_1a325a9a67f4565ea58e5d5ef3d2960a64)`() const` | 
`public void `[`AddGState`](#classCCharacter_1af38c38bdb5d7c371e786e2c933a9466a)`(__int64 n64GState)` | 
`public void `[`AddMState`](#classCCharacter_1aefea6662e4aef15ae8c734697eaaac25)`(__int64 n64MState)` | 
`public void `[`AddGStateEx`](#classCCharacter_1a45e2cc520af9e829b399f1ba0e7dd82e)`(__int64 n64GStateEx)` | 
`public void `[`AddMStateEx`](#classCCharacter_1a86c04d0aacd6c83484c7bd4a69c0f2e4)`(__int64 n64MStateEx)` | 
`public void `[`SubGState`](#classCCharacter_1ac55904391a0295a865e8d7593f5f61b8)`(__int64 n64GState)` | 
`public void `[`SubMState`](#classCCharacter_1a73a3e166928352776f2be316767730a6)`(__int64 n64MState)` | 
`public void `[`SubGStateEx`](#classCCharacter_1ae80b266496b646cadbe3fc5a4b1eff24)`(__int64 n64GStateEx)` | 
`public void `[`SubMStateEx`](#classCCharacter_1a29926f9323d2091c8d824ff3325024b5)`(__int64 n64MStateEx)` | 
`public bool `[`IsGState`](#classCCharacter_1a854edafae6cdccd8250aab74e6991486)`(__int64 n64GState)` | 
`public bool `[`IsMState`](#classCCharacter_1a8d6040120fa1c55e7469d7d2cbdfb171)`(__int64 n64MState)` | 
`public bool `[`IsGStateEx`](#classCCharacter_1acbef8d19711780d3042290df28df8e97)`(__int64 n64GStateEx)` | 
`public bool `[`IsMStateEx`](#classCCharacter_1a3998f7bb41290e11bce58171152c0895)`(__int64 n64MStateEx)` | 
`public virtual Packet `[`GenerateCreatePacket`](#classCCharacter_1a96f8788d5511e2dc05b300518b73ebdb)`(bool bHero)` | 
`public virtual Packet `[`GeneratePetPacket`](#classCCharacter_1a4f0669edcafe73a3eea7f153614f545d)`()` | 
`public virtual Packet `[`GenerateDeletePacket`](#classCCharacter_1ab3debdc7f346843d009acb7c2a42e5ba)`()` | 
`public virtual Packet `[`GenerateMovePacket`](#classCCharacter_1a408dc692b77e60db7a6871332ada6d84)`(BYTE byType,char byX,char byY,char byZ)` | 
`public inline virtual void `[`SendPacket`](#classCCharacter_1ad3570e1c2917721b4d6bdc132402bfc1)`(Packet & packet)` | 
`public inline virtual void `[`Tick`](#classCCharacter_1aaa3ad354eeb4fa16acf29211b89641ac)`()` | 
`public bool `[`WriteInSight`](#classCCharacter_1a6c2c1dbb58c8341270104f745c0cde66)`(BYTE byType,...)` | 
`public void `[`SendPacketInSight`](#classCCharacter_1a9f56b301fe16b09c71c27d5cd0f569cc)`(Packet & packet)` | 
`public void `[`SetDirection`](#classCCharacter_1aae7b164533ebd3eb340a73e8bd52a482)`(int nX,int nY)` | 
`public inline void `[`SetDirection`](#classCCharacter_1ad10316950dde5427e21eeed010f8922c)`(CCharacter * pCharacter)` | 
`public inline bool `[`IsNormal`](#classCCharacter_1afcb034bf778707a7eff06c464277039f)`() const` | 
`public inline virtual void `[`Damage`](#classCCharacter_1ac83eb913462cc822b7a8603a1e78fd97)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` | 
`public inline virtual void `[`Die`](#classCCharacter_1af5ed7b39fc9af23953936bbf7d4190b4)`()` | 
`public BYTE `[`GetMoveAction`](#classCCharacter_1a60939bf801ffa3abc0799338445b953e)`(CCharacter * pCharacter,char byX,char byY)` | 
`public int `[`GetDistance`](#classCCharacter_1a05f71e08c02d84c7358fe927ca56f49d)`(CCharacter * pCharacter) const` | 
`protected int `[`m_nID`](#classCCharacter_1a5100b377fbde4fe13ee4bed308139519) | 
`protected WORD `[`m_wStrAdd`](#classCCharacter_1a1bb083b5de32db494e01c80e20e682d1) | 
`protected WORD `[`m_wHthAdd`](#classCCharacter_1a6dfef75d0df714aac08bd03625228ab7) | 
`protected WORD `[`m_wIntAdd`](#classCCharacter_1ad0a9a9780e0b9b2c75f1784c9af75da3) | 
`protected WORD `[`m_wWisAdd`](#classCCharacter_1a12152eb9465ec3d5e3d30d9de65ac77d) | 
`protected WORD `[`m_wDexAdd`](#classCCharacter_1a146be16d3e5e67df90bb49591d5cac5b) | 
`protected DWORD `[`m_nCurHP`](#classCCharacter_1a233168733923400c942e8db32153fd93) | 
`protected WORD `[`m_wCurMP`](#classCCharacter_1a7c2e8eaef126696d9b2c8d1598c8f218) | 
`protected int `[`m_nX`](#classCCharacter_1a575aaf88f15cbcf470d24c9daf108031) | 
`protected int `[`m_nY`](#classCCharacter_1abfcc5499774eaa139a48d05bb5ddb89d) | 
`protected int `[`m_nZ`](#classCCharacter_1afa7d5ce0dc10dc4e14e7b1a0d4c73256) | 
`protected BYTE `[`m_byClass`](#classCCharacter_1a3fa27ddd90e660b4611b2e02c2128313) | 
`protected WORD `[`m_wHitAdd`](#classCCharacter_1af77f7347c4a427d76bcfc417f346d336) | 
`protected WORD `[`m_wDodgeAdd`](#classCCharacter_1a6bee344fec334262c3f9037379953a7f) | 
`protected DWORD `[`m_dwMaxHPAdd`](#classCCharacter_1ac970b808f13dcb0871540d81b61a0494) | 
`protected WORD `[`m_wMaxMPAdd`](#classCCharacter_1aa6e8742b8d3c7998496095899d6c2dd2) | 
`protected WORD `[`m_wMinAttackAdd`](#classCCharacter_1aae5f38b035432bb180ae18ef1260cbb1) | 
`protected WORD `[`m_wMaxAttackAdd`](#classCCharacter_1a56e544a4b59c4b23ebcbada5db7c20be) | 
`protected WORD `[`m_wMinMagicAdd`](#classCCharacter_1a691b8d50ec927a5663455515e1b8c9c6) | 
`protected WORD `[`m_wMaxMagicAdd`](#classCCharacter_1acab6d919bb5e7cb1df0054450920b1fc) | 
`protected WORD `[`m_wResistFireAdd`](#classCCharacter_1a0382beebaccc6b3581526aaa6a64f45f) | 
`protected WORD `[`m_wResistIceAdd`](#classCCharacter_1ac4863e7c549efbf181891340d84d96d2) | 
`protected WORD `[`m_wResistLitningAdd`](#classCCharacter_1a8613bea5d897b0afead970258c3c6473) | 
`protected WORD `[`m_wResistCurseAdd`](#classCCharacter_1adf134d13bd080a71f0ee77e832bd606f) | 
`protected WORD `[`m_wResistPalsyAdd`](#classCCharacter_1a3029ff4022f676a8465f51cc738764ca) | 
`protected WORD `[`m_wDir`](#classCCharacter_1ada406988f032855f9aed19145db3076e) | 
`protected __int64 `[`m_n64GState`](#classCCharacter_1a3ee4eea5b273de4f9d60a0d3e993b9dd) | 
`protected __int64 `[`m_n64MState`](#classCCharacter_1a0ffb595a7f713235f2e4db171c6df5d0) | 
`protected __int64 `[`m_n64GStateEx`](#classCCharacter_1a57a0d5731bda059fe301957c115cc909) | 
`protected __int64 `[`m_n64MStateEx`](#classCCharacter_1a394aca418b2a9fdb79b5de2aa0b8456c) | 
`protected BYTE `[`m_byKind`](#classCCharacter_1a6d5bea65ba62c3392077f4a851f7d770) | 

## Members

#### `public Access `[`m_Access`](#classCCharacter_1a7c09b343980598688a971ce13995b884) 

#### `public  `[`CCharacter`](#classCCharacter_1a94574d74f605d70d70acb96e01233adf)`()` 

#### `public inline void `[`Lock`](#classCCharacter_1a1c3cf4b18b5fc184d62770f10fa81851)`()` 

#### `public inline void `[`Unlock`](#classCCharacter_1a75454c5b85705b5f118bfb775085ae76)`()` 

#### `public inline int `[`GetID`](#classCCharacter_1ad7f5f1742dc177fd2209648690b30190)`() const` 

#### `public inline BYTE `[`GetKind`](#classCCharacter_1af268189e36a1bea406a5bbaa6670302d)`() const` 

#### `public inline BYTE `[`GetClass`](#classCCharacter_1ad23b140d84b130c0424bfa334972fb0e)`() const` 

#### `public inline virtual WORD `[`GetStr`](#classCCharacter_1a58744cb98cc68993d943e0ec2647306a)`() const` 

#### `public inline virtual WORD `[`GetHth`](#classCCharacter_1a5240b51c5308228a33ba02e9f1dd2279)`() const` 

#### `public inline virtual WORD `[`GetInt`](#classCCharacter_1aa6d3cd9981516a834e16bf7b1158c224)`() const` 

#### `public inline virtual WORD `[`GetWis`](#classCCharacter_1ab5a1b339e78d7581131aaf19fc398b06)`() const` 

#### `public inline virtual WORD `[`GetAgi`](#classCCharacter_1a60ed981680f1ae170d8f94f44accf080)`() const` 

#### `public inline DWORD `[`GetCurHP`](#classCCharacter_1a15ad355680c7702eb4b1e86e5df5d118)`() const` 

#### `public inline WORD `[`GetCurMP`](#classCCharacter_1a8eeda86886aa7c0a652109823190fe89)`() const` 

#### `public inline virtual DWORD `[`GetMaxHP`](#classCCharacter_1a2c280eb02bd39dd245b48370db35ee2b)`() const` 

#### `public inline virtual WORD `[`GetMaxMP`](#classCCharacter_1a210fba6eac3e87aae59c681195c48369)`() const` 

#### `public inline int `[`GetX`](#classCCharacter_1ab43af4e964cc23dde5b75840a77acd5e)`() const` 

#### `public inline int `[`GetY`](#classCCharacter_1a849ceb26d2c01ec720f2fbd8ab1619d4)`() const` 

#### `public inline int `[`GetZ`](#classCCharacter_1a74b10ffeef48e680bca8c761d84aca29)`() const` 

#### `public inline WORD `[`GetDir`](#classCCharacter_1ac8b2b38e896c0b82210a7c2d6b2c67d4)`() const` 

#### `public inline virtual BYTE `[`GetLevel`](#classCCharacter_1a377cc0f6a658e0416c742ccdcad4372f)`() const` 

#### `public inline virtual WORD `[`GetHit`](#classCCharacter_1a56435a6058690cffe37840e76eeeca87)`() const` 

#### `public inline virtual WORD `[`GetDodge`](#classCCharacter_1afff27b3e1caa3764f7a23f0d927e5af7)`() const` 

#### `public inline virtual WORD `[`GetDefense`](#classCCharacter_1a9ec02921a5e7286d0a09ca33cbff156b)`(BYTE byType) const` 

#### `public inline virtual BYTE `[`GetAbsorb`](#classCCharacter_1a7e86accfee142376c3799f59aaaa0b7e)`() const` 

#### `public inline virtual WORD `[`GetMinAttack`](#classCCharacter_1a7e9ccca9b9c5515fb358829cd1ca3db6)`() const` 

#### `public inline virtual WORD `[`GetMaxAttack`](#classCCharacter_1a72aca8cd8b2f435ea57c842fa6c06991)`() const` 

#### `public inline virtual WORD `[`GetMinMagic`](#classCCharacter_1ae5f14202b5ee6c43930462b7c9632d30)`() const` 

#### `public inline virtual WORD `[`GetMaxMagic`](#classCCharacter_1a1fc2bd31eea1bc2907077a5dd8e9fdf8)`() const` 

#### `public inline virtual WORD `[`GetResist`](#classCCharacter_1ad1b2b1bc32824f8b446e04e59079caab)`(BYTE byResist) const` 

#### `public inline virtual WORD `[`GetSize`](#classCCharacter_1a109680868eaafda26341c7b07f4abf23)`() const` 

#### `public WORD `[`GetAttack`](#classCCharacter_1a013683c064c423fd17bb13e5b5ba7e1a)`() const` 

#### `public WORD `[`GetMagic`](#classCCharacter_1a9445d97edb6bf4787086ba0a6ebcdb8a)`() const` 

#### `public virtual bool `[`CanAttack`](#classCCharacter_1aa1c9b59cfacc095884265e95eee69194)`(CCharacter * pTarget) const` 

#### `public virtual bool `[`CheckHit`](#classCCharacter_1aaf781230de62a807fcdcb79022777006)`(CCharacter * pTarget,int nAdd) const` 

#### `public inline virtual bool `[`CheckBlock`](#classCCharacter_1a398efeea83df4f2349a38737c11f8158)`(CCharacter * pAttacker) const` 

#### `public DWORD `[`GetFinalDamage`](#classCCharacter_1a957de429305b2f9de1e524491c729e54)`(CCharacter * pAttacker,DWORD dwDamage,BYTE byType)` 

#### `public DWORD `[`GetFatalDamage`](#classCCharacter_1ae9c0dcc3311ba9e68217404cfb0f85b1)`(DWORD dwFinalDamage,BYTE & byType)` 

#### `public inline __int64 `[`GetGState`](#classCCharacter_1abb9fb45114752bd3e127c79e32d3b5f4)`() const` 

#### `public inline __int64 `[`GetMState`](#classCCharacter_1aa0a340e1becaead14f794ff013f39cae)`() const` 

#### `public inline __int64 `[`GetGStateEx`](#classCCharacter_1aa8f2c178d15eda870a7ac001069cfd03)`() const` 

#### `public inline __int64 `[`GetMStateEx`](#classCCharacter_1a325a9a67f4565ea58e5d5ef3d2960a64)`() const` 

#### `public void `[`AddGState`](#classCCharacter_1af38c38bdb5d7c371e786e2c933a9466a)`(__int64 n64GState)` 

#### `public void `[`AddMState`](#classCCharacter_1aefea6662e4aef15ae8c734697eaaac25)`(__int64 n64MState)` 

#### `public void `[`AddGStateEx`](#classCCharacter_1a45e2cc520af9e829b399f1ba0e7dd82e)`(__int64 n64GStateEx)` 

#### `public void `[`AddMStateEx`](#classCCharacter_1a86c04d0aacd6c83484c7bd4a69c0f2e4)`(__int64 n64MStateEx)` 

#### `public void `[`SubGState`](#classCCharacter_1ac55904391a0295a865e8d7593f5f61b8)`(__int64 n64GState)` 

#### `public void `[`SubMState`](#classCCharacter_1a73a3e166928352776f2be316767730a6)`(__int64 n64MState)` 

#### `public void `[`SubGStateEx`](#classCCharacter_1ae80b266496b646cadbe3fc5a4b1eff24)`(__int64 n64GStateEx)` 

#### `public void `[`SubMStateEx`](#classCCharacter_1a29926f9323d2091c8d824ff3325024b5)`(__int64 n64MStateEx)` 

#### `public bool `[`IsGState`](#classCCharacter_1a854edafae6cdccd8250aab74e6991486)`(__int64 n64GState)` 

#### `public bool `[`IsMState`](#classCCharacter_1a8d6040120fa1c55e7469d7d2cbdfb171)`(__int64 n64MState)` 

#### `public bool `[`IsGStateEx`](#classCCharacter_1acbef8d19711780d3042290df28df8e97)`(__int64 n64GStateEx)` 

#### `public bool `[`IsMStateEx`](#classCCharacter_1a3998f7bb41290e11bce58171152c0895)`(__int64 n64MStateEx)` 

#### `public virtual Packet `[`GenerateCreatePacket`](#classCCharacter_1a96f8788d5511e2dc05b300518b73ebdb)`(bool bHero)` 

#### `public virtual Packet `[`GeneratePetPacket`](#classCCharacter_1a4f0669edcafe73a3eea7f153614f545d)`()` 

#### `public virtual Packet `[`GenerateDeletePacket`](#classCCharacter_1ab3debdc7f346843d009acb7c2a42e5ba)`()` 

#### `public virtual Packet `[`GenerateMovePacket`](#classCCharacter_1a408dc692b77e60db7a6871332ada6d84)`(BYTE byType,char byX,char byY,char byZ)` 

#### `public inline virtual void `[`SendPacket`](#classCCharacter_1ad3570e1c2917721b4d6bdc132402bfc1)`(Packet & packet)` 

#### `public inline virtual void `[`Tick`](#classCCharacter_1aaa3ad354eeb4fa16acf29211b89641ac)`()` 

#### `public bool `[`WriteInSight`](#classCCharacter_1a6c2c1dbb58c8341270104f745c0cde66)`(BYTE byType,...)` 

#### `public void `[`SendPacketInSight`](#classCCharacter_1a9f56b301fe16b09c71c27d5cd0f569cc)`(Packet & packet)` 

#### `public void `[`SetDirection`](#classCCharacter_1aae7b164533ebd3eb340a73e8bd52a482)`(int nX,int nY)` 

#### `public inline void `[`SetDirection`](#classCCharacter_1ad10316950dde5427e21eeed010f8922c)`(CCharacter * pCharacter)` 

#### `public inline bool `[`IsNormal`](#classCCharacter_1afcb034bf778707a7eff06c464277039f)`() const` 

#### `public inline virtual void `[`Damage`](#classCCharacter_1ac83eb913462cc822b7a8603a1e78fd97)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` 

#### `public inline virtual void `[`Die`](#classCCharacter_1af5ed7b39fc9af23953936bbf7d4190b4)`()` 

#### `public BYTE `[`GetMoveAction`](#classCCharacter_1a60939bf801ffa3abc0799338445b953e)`(CCharacter * pCharacter,char byX,char byY)` 

#### `public int `[`GetDistance`](#classCCharacter_1a05f71e08c02d84c7358fe927ca56f49d)`(CCharacter * pCharacter) const` 

#### `protected int `[`m_nID`](#classCCharacter_1a5100b377fbde4fe13ee4bed308139519) 

#### `protected WORD `[`m_wStrAdd`](#classCCharacter_1a1bb083b5de32db494e01c80e20e682d1) 

#### `protected WORD `[`m_wHthAdd`](#classCCharacter_1a6dfef75d0df714aac08bd03625228ab7) 

#### `protected WORD `[`m_wIntAdd`](#classCCharacter_1ad0a9a9780e0b9b2c75f1784c9af75da3) 

#### `protected WORD `[`m_wWisAdd`](#classCCharacter_1a12152eb9465ec3d5e3d30d9de65ac77d) 

#### `protected WORD `[`m_wDexAdd`](#classCCharacter_1a146be16d3e5e67df90bb49591d5cac5b) 

#### `protected DWORD `[`m_nCurHP`](#classCCharacter_1a233168733923400c942e8db32153fd93) 

#### `protected WORD `[`m_wCurMP`](#classCCharacter_1a7c2e8eaef126696d9b2c8d1598c8f218) 

#### `protected int `[`m_nX`](#classCCharacter_1a575aaf88f15cbcf470d24c9daf108031) 

#### `protected int `[`m_nY`](#classCCharacter_1abfcc5499774eaa139a48d05bb5ddb89d) 

#### `protected int `[`m_nZ`](#classCCharacter_1afa7d5ce0dc10dc4e14e7b1a0d4c73256) 

#### `protected BYTE `[`m_byClass`](#classCCharacter_1a3fa27ddd90e660b4611b2e02c2128313) 

#### `protected WORD `[`m_wHitAdd`](#classCCharacter_1af77f7347c4a427d76bcfc417f346d336) 

#### `protected WORD `[`m_wDodgeAdd`](#classCCharacter_1a6bee344fec334262c3f9037379953a7f) 

#### `protected DWORD `[`m_dwMaxHPAdd`](#classCCharacter_1ac970b808f13dcb0871540d81b61a0494) 

#### `protected WORD `[`m_wMaxMPAdd`](#classCCharacter_1aa6e8742b8d3c7998496095899d6c2dd2) 

#### `protected WORD `[`m_wMinAttackAdd`](#classCCharacter_1aae5f38b035432bb180ae18ef1260cbb1) 

#### `protected WORD `[`m_wMaxAttackAdd`](#classCCharacter_1a56e544a4b59c4b23ebcbada5db7c20be) 

#### `protected WORD `[`m_wMinMagicAdd`](#classCCharacter_1a691b8d50ec927a5663455515e1b8c9c6) 

#### `protected WORD `[`m_wMaxMagicAdd`](#classCCharacter_1acab6d919bb5e7cb1df0054450920b1fc) 

#### `protected WORD `[`m_wResistFireAdd`](#classCCharacter_1a0382beebaccc6b3581526aaa6a64f45f) 

#### `protected WORD `[`m_wResistIceAdd`](#classCCharacter_1ac4863e7c549efbf181891340d84d96d2) 

#### `protected WORD `[`m_wResistLitningAdd`](#classCCharacter_1a8613bea5d897b0afead970258c3c6473) 

#### `protected WORD `[`m_wResistCurseAdd`](#classCCharacter_1adf134d13bd080a71f0ee77e832bd606f) 

#### `protected WORD `[`m_wResistPalsyAdd`](#classCCharacter_1a3029ff4022f676a8465f51cc738764ca) 

#### `protected WORD `[`m_wDir`](#classCCharacter_1ada406988f032855f9aed19145db3076e) 

#### `protected __int64 `[`m_n64GState`](#classCCharacter_1a3ee4eea5b273de4f9d60a0d3e993b9dd) 

#### `protected __int64 `[`m_n64MState`](#classCCharacter_1a0ffb595a7f713235f2e4db171c6df5d0) 

#### `protected __int64 `[`m_n64GStateEx`](#classCCharacter_1a57a0d5731bda059fe301957c115cc909) 

#### `protected __int64 `[`m_n64MStateEx`](#classCCharacter_1a394aca418b2a9fdb79b5de2aa0b8456c) 

#### `protected BYTE `[`m_byKind`](#classCCharacter_1a6d5bea65ba62c3392077f4a851f7d770) 

# class `CClient` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Access `[`m_Access`](#classCClient_1adb2dbfc0aca4e475b41d9f65b1b2f15e) | 
`public inline  `[`CClient`](#classCClient_1a4092fee044e82df0fb5164b36a56d401)`(int nCID)` | 
`public  `[`~CClient`](#classCClient_1adfec5dfb8d13c1245020e52aac0812b1)`()` | 
`public bool `[`Write`](#classCClient_1acaf14202e441a6f768baba78ae8657ba)`(BYTE byType,...)` | 
`public void `[`Process`](#classCClient_1a1362876b107a0215647c59cd5a5451c9)`(Packet packet)` | 
`public inline void `[`Lock`](#classCClient_1af920a05bd08aae9358b2b3cf44700f71)`()` | 
`public inline void `[`Unlock`](#classCClient_1a86533589cea9105bc648dd6fb04435f5)`()` | 
`public inline void `[`SetMAC`](#classCClient_1a25f5afad884d5189e5c5323caadbd515)`(std::string szMac)` | 
`public inline std::string `[`GetMAC`](#classCClient_1af64bc448af86fd34517f03d580900529)`() const` | 
`public inline void `[`SetLogin`](#classCClient_1a4fe2ece49363de49add4013531a29a6d)`(std::string szLogin)` | 
`public inline std::string `[`GetLogin`](#classCClient_1a27459bf9bebd7cfa95d274b513079950)`() const` | 
`public inline void `[`SetPassword`](#classCClient_1a89236ebf751c30c1f4c21a60c5777c07)`(std::string szPassword)` | 
`public inline std::string `[`GetPassword`](#classCClient_1a70271a57361ec5cfa25a4ddefa2c3728)`() const` | 
`public inline int `[`GetCID`](#classCClient_1a81eaf7cd6de91784fdbf2e0410f3b593)`() const` | 
`public inline CPlayer * `[`GetPlayer`](#classCClient_1a5b1516cd6b0c6908160c03fddc35c095)`() const` | 
`public inline void `[`RemovePlayer`](#classCClient_1a3b4ab8844e7415c3b0c58c5db123a739)`()` | 
`public void `[`OnLogin`](#classCClient_1af86a2bd31a3928d8ce1da75d55cae277)`(char * p)` | 
`public char * `[`OnLoadPlayer`](#classCClient_1a40593b06716a5f2ab93a283035416632)`(char * p)` | 
`public void `[`OnLoadItems`](#classCClient_1ae388aca737d8706c0d78d851b993fd81)`(char * p)` | 

## Members

#### `public Access `[`m_Access`](#classCClient_1adb2dbfc0aca4e475b41d9f65b1b2f15e) 

#### `public inline  `[`CClient`](#classCClient_1a4092fee044e82df0fb5164b36a56d401)`(int nCID)` 

#### `public  `[`~CClient`](#classCClient_1adfec5dfb8d13c1245020e52aac0812b1)`()` 

#### `public bool `[`Write`](#classCClient_1acaf14202e441a6f768baba78ae8657ba)`(BYTE byType,...)` 

#### `public void `[`Process`](#classCClient_1a1362876b107a0215647c59cd5a5451c9)`(Packet packet)` 

#### `public inline void `[`Lock`](#classCClient_1af920a05bd08aae9358b2b3cf44700f71)`()` 

#### `public inline void `[`Unlock`](#classCClient_1a86533589cea9105bc648dd6fb04435f5)`()` 

#### `public inline void `[`SetMAC`](#classCClient_1a25f5afad884d5189e5c5323caadbd515)`(std::string szMac)` 

#### `public inline std::string `[`GetMAC`](#classCClient_1af64bc448af86fd34517f03d580900529)`() const` 

#### `public inline void `[`SetLogin`](#classCClient_1a4fe2ece49363de49add4013531a29a6d)`(std::string szLogin)` 

#### `public inline std::string `[`GetLogin`](#classCClient_1a27459bf9bebd7cfa95d274b513079950)`() const` 

#### `public inline void `[`SetPassword`](#classCClient_1a89236ebf751c30c1f4c21a60c5777c07)`(std::string szPassword)` 

#### `public inline std::string `[`GetPassword`](#classCClient_1a70271a57361ec5cfa25a4ddefa2c3728)`() const` 

#### `public inline int `[`GetCID`](#classCClient_1a81eaf7cd6de91784fdbf2e0410f3b593)`() const` 

#### `public inline CPlayer * `[`GetPlayer`](#classCClient_1a5b1516cd6b0c6908160c03fddc35c095)`() const` 

#### `public inline void `[`RemovePlayer`](#classCClient_1a3b4ab8844e7415c3b0c58c5db123a739)`()` 

#### `public void `[`OnLogin`](#classCClient_1af86a2bd31a3928d8ce1da75d55cae277)`(char * p)` 

#### `public char * `[`OnLoadPlayer`](#classCClient_1a40593b06716a5f2ab93a283035416632)`(char * p)` 

#### `public void `[`OnLoadItems`](#classCClient_1ae388aca737d8706c0d78d851b993fd81)`(char * p)` 

# class `CClientSocket` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CDatabase` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CDBSocket` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CItem` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Access `[`m_Access`](#classCItem_1a0b2e1cfa343aa2de2fe16c427677ed2c) | 
`public  `[`CItem`](#classCItem_1a3b0faf4a5b905b09697a002910cc22d7)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public  `[`~CItem`](#classCItem_1a2487c6e822ed0e850544f1745b43f584)`()` | 
`public inline int `[`GetIID`](#classCItem_1a6397b70896999b6e281a68da540ae8e3)`() const` | 
`public inline int `[`GetInfo`](#classCItem_1a65c14c3be072bbd1f10cb597a3afb524)`() const` | 
`public inline int `[`GetNum`](#classCItem_1ae7e44327c71d7b0a73c522be9be49fc2)`() const` | 
`public inline void `[`SetNum`](#classCItem_1ae3d488c1f9fe85b86ed70ed0045d1c42)`(int nNum)` | 
`public inline WORD `[`GetIndex`](#classCItem_1a429b6bbc45c497966208f4787614b848)`() const` | 
`public inline BYTE `[`GetLevel`](#classCItem_1ac3c97b8250fb9ed4e05643d8cf8be1d1)`() const` | 
`public inline BYTE `[`GetClass`](#classCItem_1a0d1dd3dcf572d3b926db29c79ae3c957)`() const` | 
`public inline BYTE `[`GetSubClass`](#classCItem_1ac7821b2e12b09c89b503bc7edb1cc5a9)`() const` | 
`public inline BYTE `[`GetWearType`](#classCItem_1a21b7f4f0fe897093d3cc483064b6a834)`() const` | 
`public inline CItemInfo * `[`GetMacro`](#classCItem_1a8b8ac7b6818894f971187a6573a7051a)`() const` | 
`public inline bool `[`IsState`](#classCItem_1abd9c949506f4ee46222311a07a63aadc)`(int nState)` | 
`public inline void `[`AddState`](#classCItem_1af52c7b0acb76aeef010a6b6932676d69)`(int nState)` | 
`public inline void `[`SubState`](#classCItem_1abbe08f4912ce874800cff8205aa2f6eb)`(int nState)` | 
`public inline void `[`Lock`](#classCItem_1a131ecdd784e0b986befce1f577f0e2fc)`()` | 
`public inline void `[`Unlock`](#classCItem_1a6cc30317104d1e0350e03628ec13b27f)`()` | 
`public inline virtual bool `[`Use`](#classCItem_1ad68ff7df8ad358daab91dd61cc50ac4f)`(CPlayer * pPlayer)` | 
`public inline virtual void `[`PutOn`](#classCItem_1a55d0c2c1090517a608bb26fff1ec5fe9)`(CPlayer * pPlayer)` | 
`public inline virtual void `[`PutOff`](#classCItem_1a0f704fc3afb7ecb419296f0b0b56af71)`(CPlayer * pPlayer)` | 
`public bool `[`CanUse`](#classCItem_1af029cc1aad0740d70a68286b391c7b55)`(CPlayer * pPlayer)` | 
`public bool `[`CanTrash`](#classCItem_1a137daf554896f4f6052ac506bc6c19fe)`(CPlayer * pPlayer)` | 
`protected ITEMINFO_DESC `[`m_desc`](#classCItem_1a4e324af341937bffad0493254ce40265) | 
`protected CItemInfo * `[`m_pMacro`](#classCItem_1acb6d6f0949cc68721d2b4f536b32bf16) | 
`protected BYTE `[`m_byWearType`](#classCItem_1a8861ef25a1545a969a4893640f66e0f1) | 
`protected std::mutex `[`m_mxThis`](#classCItem_1a1be269ae356f44e14ec53ce783198923) | 

## Members

#### `public Access `[`m_Access`](#classCItem_1a0b2e1cfa343aa2de2fe16c427677ed2c) 

#### `public  `[`CItem`](#classCItem_1a3b0faf4a5b905b09697a002910cc22d7)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public  `[`~CItem`](#classCItem_1a2487c6e822ed0e850544f1745b43f584)`()` 

#### `public inline int `[`GetIID`](#classCItem_1a6397b70896999b6e281a68da540ae8e3)`() const` 

#### `public inline int `[`GetInfo`](#classCItem_1a65c14c3be072bbd1f10cb597a3afb524)`() const` 

#### `public inline int `[`GetNum`](#classCItem_1ae7e44327c71d7b0a73c522be9be49fc2)`() const` 

#### `public inline void `[`SetNum`](#classCItem_1ae3d488c1f9fe85b86ed70ed0045d1c42)`(int nNum)` 

#### `public inline WORD `[`GetIndex`](#classCItem_1a429b6bbc45c497966208f4787614b848)`() const` 

#### `public inline BYTE `[`GetLevel`](#classCItem_1ac3c97b8250fb9ed4e05643d8cf8be1d1)`() const` 

#### `public inline BYTE `[`GetClass`](#classCItem_1a0d1dd3dcf572d3b926db29c79ae3c957)`() const` 

#### `public inline BYTE `[`GetSubClass`](#classCItem_1ac7821b2e12b09c89b503bc7edb1cc5a9)`() const` 

#### `public inline BYTE `[`GetWearType`](#classCItem_1a21b7f4f0fe897093d3cc483064b6a834)`() const` 

#### `public inline CItemInfo * `[`GetMacro`](#classCItem_1a8b8ac7b6818894f971187a6573a7051a)`() const` 

#### `public inline bool `[`IsState`](#classCItem_1abd9c949506f4ee46222311a07a63aadc)`(int nState)` 

#### `public inline void `[`AddState`](#classCItem_1af52c7b0acb76aeef010a6b6932676d69)`(int nState)` 

#### `public inline void `[`SubState`](#classCItem_1abbe08f4912ce874800cff8205aa2f6eb)`(int nState)` 

#### `public inline void `[`Lock`](#classCItem_1a131ecdd784e0b986befce1f577f0e2fc)`()` 

#### `public inline void `[`Unlock`](#classCItem_1a6cc30317104d1e0350e03628ec13b27f)`()` 

#### `public inline virtual bool `[`Use`](#classCItem_1ad68ff7df8ad358daab91dd61cc50ac4f)`(CPlayer * pPlayer)` 

#### `public inline virtual void `[`PutOn`](#classCItem_1a55d0c2c1090517a608bb26fff1ec5fe9)`(CPlayer * pPlayer)` 

#### `public inline virtual void `[`PutOff`](#classCItem_1a0f704fc3afb7ecb419296f0b0b56af71)`(CPlayer * pPlayer)` 

#### `public bool `[`CanUse`](#classCItem_1af029cc1aad0740d70a68286b391c7b55)`(CPlayer * pPlayer)` 

#### `public bool `[`CanTrash`](#classCItem_1a137daf554896f4f6052ac506bc6c19fe)`(CPlayer * pPlayer)` 

#### `protected ITEMINFO_DESC `[`m_desc`](#classCItem_1a4e324af341937bffad0493254ce40265) 

#### `protected CItemInfo * `[`m_pMacro`](#classCItem_1acb6d6f0949cc68721d2b4f536b32bf16) 

#### `protected BYTE `[`m_byWearType`](#classCItem_1a8861ef25a1545a969a4893640f66e0f1) 

#### `protected std::mutex `[`m_mxThis`](#classCItem_1a1be269ae356f44e14ec53ce783198923) 

# class `CItemDefense` 

```
class CItemDefense
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemDefense`](#classCItemDefense_1ada1904fbee80348cf03325419e106832)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public void `[`PutOn`](#classCItemDefense_1a0efa605ca2e725a2081cb8670e568b80)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemDefense_1a6e2d4a0d5f9161d97170f80ad692255f)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemDefense`](#classCItemDefense_1ada1904fbee80348cf03325419e106832)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public void `[`PutOn`](#classCItemDefense_1a0efa605ca2e725a2081cb8670e568b80)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemDefense_1a6e2d4a0d5f9161d97170f80ad692255f)`(CPlayer * pPlayer)` 

# class `CItemDrop` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CItemGeneral` 

```
class CItemGeneral
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CItemGeneral`](#classCItemGeneral_1aca253e109d4a77cc669174ca78cc90fa)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public bool `[`Use`](#classCItemGeneral_1a41ac30786b18006a1c143b30c0bb8eb4)`(CPlayer * pPlayer)` | 

## Members

#### `public inline  `[`CItemGeneral`](#classCItemGeneral_1aca253e109d4a77cc669174ca78cc90fa)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public bool `[`Use`](#classCItemGeneral_1a41ac30786b18006a1c143b30c0bb8eb4)`(CPlayer * pPlayer)` 

# class `CItemOrnament` 

```
class CItemOrnament
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemOrnament`](#classCItemOrnament_1abf03d27f6fc74849a8a2fe9931f6e6a6)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public void `[`PutOn`](#classCItemOrnament_1a2ec0f313e1a5f5749542cfa915eacfb0)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemOrnament_1a4e8cda616f2ca290b7caacabe36ada4f)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemOrnament`](#classCItemOrnament_1abf03d27f6fc74849a8a2fe9931f6e6a6)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public void `[`PutOn`](#classCItemOrnament_1a2ec0f313e1a5f5749542cfa915eacfb0)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemOrnament_1a4e8cda616f2ca290b7caacabe36ada4f)`(CPlayer * pPlayer)` 

# class `CItemPet` 

```
class CItemPet
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemPet`](#classCItemPet_1aaff2dc5ef2a45bcde79ecb942860db51)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public inline BYTE `[`GetPetType`](#classCItemPet_1a54d6d4d63c11d114373edf758bd5e23b)`()` | 
`public void `[`PutOn`](#classCItemPet_1aab0406ba21d9f116085077ac74aef62f)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemPet_1a8d029571677633f9bc5f241211604cc2)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemPet`](#classCItemPet_1aaff2dc5ef2a45bcde79ecb942860db51)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public inline BYTE `[`GetPetType`](#classCItemPet_1a54d6d4d63c11d114373edf758bd5e23b)`()` 

#### `public void `[`PutOn`](#classCItemPet_1aab0406ba21d9f116085077ac74aef62f)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemPet_1a8d029571677633f9bc5f241211604cc2)`(CPlayer * pPlayer)` 

# class `CItemRefresh` 

```
class CItemRefresh
  : public CItemGeneral
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CItemRefresh`](#classCItemRefresh_1aface0d243a742c48a140a2f6d2388fa8)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public bool `[`Use`](#classCItemRefresh_1abc9fb77a79144d9f01240e4a6ec7ad25)`(CPlayer * pPlayer)` | 

## Members

#### `public inline  `[`CItemRefresh`](#classCItemRefresh_1aface0d243a742c48a140a2f6d2388fa8)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public bool `[`Use`](#classCItemRefresh_1abc9fb77a79144d9f01240e4a6ec7ad25)`(CPlayer * pPlayer)` 

# class `CItemRide` 

```
class CItemRide
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemRide`](#classCItemRide_1ab0dbab5248b49db64152db88d7afaef7)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public inline BYTE `[`GetRideType`](#classCItemRide_1aa219424f24541db4e26cb5c594cebaaf)`() const` | 
`public void `[`PutOn`](#classCItemRide_1abfb88d8bcb4bd6f3f806cb7037d91097)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemRide_1a13d46d91096135d1ccf2e4341267a3fc)`(CPlayer * pPlayer)` | 
`public bool `[`Use`](#classCItemRide_1a391f7f19c2f3f35bf5a27d64fcfecc5e)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemRide`](#classCItemRide_1ab0dbab5248b49db64152db88d7afaef7)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public inline BYTE `[`GetRideType`](#classCItemRide_1aa219424f24541db4e26cb5c594cebaaf)`() const` 

#### `public void `[`PutOn`](#classCItemRide_1abfb88d8bcb4bd6f3f806cb7037d91097)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemRide_1a13d46d91096135d1ccf2e4341267a3fc)`(CPlayer * pPlayer)` 

#### `public bool `[`Use`](#classCItemRide_1a391f7f19c2f3f35bf5a27d64fcfecc5e)`(CPlayer * pPlayer)` 

# class `CItemTeleport` 

```
class CItemTeleport
  : public CItemGeneral
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CItemTeleport`](#classCItemTeleport_1a13aafc70a585587a017807feb7aed820)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public bool `[`Use`](#classCItemTeleport_1ab79e41c5eded7010075ff8e42a0148f1)`(CPlayer * pPlayer)` | 

## Members

#### `public inline  `[`CItemTeleport`](#classCItemTeleport_1a13aafc70a585587a017807feb7aed820)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public bool `[`Use`](#classCItemTeleport_1ab79e41c5eded7010075ff8e42a0148f1)`(CPlayer * pPlayer)` 

# class `CItemTransform` 

```
class CItemTransform
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemTransform`](#classCItemTransform_1aa81efd06c90d5e5111d76f49ae883b20)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public void `[`PutOn`](#classCItemTransform_1a8bee1bfe36dae5512b8d7220d3465f8f)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemTransform_1a0ec282a4217e80726ecd7b6f0d95ee4f)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemTransform`](#classCItemTransform_1aa81efd06c90d5e5111d76f49ae883b20)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public void `[`PutOn`](#classCItemTransform_1a8bee1bfe36dae5512b8d7220d3465f8f)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemTransform_1a0ec282a4217e80726ecd7b6f0d95ee4f)`(CPlayer * pPlayer)` 

# class `CItemWeapon` 

```
class CItemWeapon
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemWeapon`](#classCItemWeapon_1a6d0e99ed4e946a04c36f786dd9477c22)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public inline WORD `[`GetAttackSpeed`](#classCItemWeapon_1a7b61754d6f4e1ffc3550b0ee1ac064f3)`() const` | 
`public inline WORD `[`GetRange`](#classCItemWeapon_1a43fa26612c536558143deed270c5698b)`() const` | 
`public void `[`PutOn`](#classCItemWeapon_1a94194adc4794ea181c21d9f56215af73)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemWeapon_1a2270510bc5c35fb8471bdff4c158a9f8)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemWeapon`](#classCItemWeapon_1a6d0e99ed4e946a04c36f786dd9477c22)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public inline WORD `[`GetAttackSpeed`](#classCItemWeapon_1a7b61754d6f4e1ffc3550b0ee1ac064f3)`() const` 

#### `public inline WORD `[`GetRange`](#classCItemWeapon_1a43fa26612c536558143deed270c5698b)`() const` 

#### `public void `[`PutOn`](#classCItemWeapon_1a94194adc4794ea181c21d9f56215af73)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemWeapon_1a2270510bc5c35fb8471bdff4c158a9f8)`(CPlayer * pPlayer)` 

# class `CItemYinyang` 

```
class CItemYinyang
  : public CItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CItemYinyang`](#classCItemYinyang_1a379efc3d9f39b3a2914802a3d913df7c)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` | 
`public void `[`PutOn`](#classCItemYinyang_1a6f53e13baa92fe4a3eff9fa772ae4495)`(CPlayer * pPlayer)` | 
`public void `[`PutOff`](#classCItemYinyang_1ad3e574020b8cda66e2e88f7959266a11)`(CPlayer * pPlayer)` | 

## Members

#### `public  `[`CItemYinyang`](#classCItemYinyang_1a379efc3d9f39b3a2914802a3d913df7c)`(ITEMINFO_DESC & desc,CItemInfo * pMacro)` 

#### `public void `[`PutOn`](#classCItemYinyang_1a6f53e13baa92fe4a3eff9fa772ae4495)`(CPlayer * pPlayer)` 

#### `public void `[`PutOff`](#classCItemYinyang_1ad3e574020b8cda66e2e88f7959266a11)`(CPlayer * pPlayer)` 

# class `CMacroDB` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CMainSocket` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CMap` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CMonster` 

```
class CMonster
  : public CCharacter
  : public ITimer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CMonster`](#classCMonster_1a32b5519b2c5d14881927b69436972c8f)`(CMonsterInfo * pMacro,int nX,int nY)` | 
`public  `[`~CMonster`](#classCMonster_1ab65729aa7d7b0e4f9092f8ae5e33b34d)`()` | 
`public Packet `[`GenerateCreatePacket`](#classCMonster_1aaebb18996775b6910623e8b468afb15b)`(bool bHero)` | 
`public Packet `[`GenerateDeletePacket`](#classCMonster_1a1421dbb2db974af7b5c3a2d167e8e793)`()` | 
`public Packet `[`GenerateMovePacket`](#classCMonster_1a36c4a1434097b4663dc9e425642759c5)`(BYTE byType,char byX,char byY,char byZ)` | 
`public inline WORD `[`GetStr`](#classCMonster_1a3ae5c18a6c0822c88f074e18e73e5875)`() const` | 
`public inline WORD `[`GetHth`](#classCMonster_1abe75aa7d1e1fc575329bf141d3968936)`() const` | 
`public inline WORD `[`GetInt`](#classCMonster_1abe6a411372dbc1f9ce80b349e125f068)`() const` | 
`public inline WORD `[`GetWis`](#classCMonster_1a703b84211544a29e42f664e4aaae06c5)`() const` | 
`public inline WORD `[`GetAgi`](#classCMonster_1a54207d4061d825c5702b1d2edf00acc1)`() const` | 
`public WORD `[`GetHit`](#classCMonster_1ae2baaa85bbc125cdcd97b87d6e2a4018)`() const` | 
`public WORD `[`GetDodge`](#classCMonster_1a8a259592a5dfb88fc087f0561b252f7d)`() const` | 
`public inline WORD `[`GetDefense`](#classCMonster_1a791be6bc0cb0b56486cae92b4398db89)`(BYTE byType) const` | 
`public inline BYTE `[`GetAbsorb`](#classCMonster_1a4c89df0e2e869953f069c025ff72affe)`() const` | 
`public DWORD `[`GetMaxHP`](#classCMonster_1a524e9af6974fae1133f6696bbc6b4b07)`() const` | 
`public WORD `[`GetMaxMP`](#classCMonster_1ae4af787fa0bca32d846f1710e1b788bf)`() const` | 
`public WORD `[`GetMinAttack`](#classCMonster_1a897e6cbae9eca095be13ee460d79803f)`() const` | 
`public WORD `[`GetMaxAttack`](#classCMonster_1a3b1074c3953f2cc5f37923bb2ed84c5d)`() const` | 
`public WORD `[`GetMinMagic`](#classCMonster_1afc4a6486c348db9411aa1246c6e18387)`() const` | 
`public WORD `[`GetMaxMagic`](#classCMonster_1abc571b26b8f78c5c0b7a000cbfcc7505)`() const` | 
`public WORD `[`GetResist`](#classCMonster_1a42c7bb7d9c13d7449a20daac57a99dc4)`(BYTE byResist) const` | 
`public inline WORD `[`GetIndex`](#classCMonster_1a1646f77a24fa39435d018715886b1a41)`() const` | 
`public inline BYTE `[`GetRace`](#classCMonster_1a5951e0b264526d6b693a79cfff5de93a)`() const` | 
`public inline BYTE `[`GetLevel`](#classCMonster_1a25481d93a1846d61c5669523a046b30e)`() const` | 
`public inline WORD `[`GetRange`](#classCMonster_1ac2f91ca1773289b6079dad01c4b00153)`() const` | 
`public inline WORD `[`GetWalkSpeed`](#classCMonster_1a0b2d80ce5652aea191e6f93931fe2e0a)`() const` | 
`public inline WORD `[`GetRunSpeed`](#classCMonster_1a51f0e1e2bdef76192d41ebc9245ecd33)`() const` | 
`public inline WORD `[`GetAttackSpeed`](#classCMonster_1a57f3ffe3d5cc777f141722234cc63053)`() const` | 
`public inline WORD `[`GetCloseSight`](#classCMonster_1aefd1e77d3ae282cf9c16c6513e31eccd)`() const` | 
`public inline WORD `[`GetFarSight`](#classCMonster_1ab70ab33fddbd8b75951316ab6fb2a513)`() const` | 
`public inline WORD `[`GetSize`](#classCMonster_1a43151e7805dab9ec7979a4d72b17d358)`() const` | 
`public void `[`SetTarget`](#classCMonster_1ab3bd3e1c4ce30e20e508d9710a303f09)`(CPlayer * pPlayer)` | 
`public inline CPlayer * `[`GetTarget`](#classCMonster_1a9882ba63a0c0d7e73ec92db540deac93)`() const` | 
`public virtual void `[`Tick`](#classCMonster_1a729a91a7d77275414420ca0b33c61698)`()` | 
`public inline virtual void `[`AI`](#classCMonster_1ade33da94e0ab0cf8cd2745a7eb8c0058)`(DWORD dwNow)` | 
`public void `[`Move`](#classCMonster_1a50baf7e342893c3fc492d3cc1edae898)`(char byX,char byY,BYTE byType)` | 
`public void `[`Attack`](#classCMonster_1a3da2c9537b0a47d96779d05f61685268)`(CPlayer * pTarget)` | 
`public bool `[`Chase`](#classCMonster_1ae490f08e7bfe5554be953ca8b29b7100)`()` | 
`public void `[`Damage`](#classCMonster_1a55b2fbb18cec0f6e079f30d2eb524496)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` | 
`public void `[`ScanSight`](#classCMonster_1a4564ee9d1505a874aefc283e1e620b07)`()` | 
`public void `[`OnWalk`](#classCMonster_1a32fa534488bc60df3006fd2f50b2be18)`()` | 
`public void `[`OnChase`](#classCMonster_1ad042edbe7a8b97cbdee38916d9925a6b)`()` | 
`public void `[`OnForceAttack`](#classCMonster_1a1d5aa5527a1275e23b59691510f9d3a9)`()` | 
`public void `[`OnAttack`](#classCMonster_1ae2b4d010e8adb89afe41b62d6ee07b1d)`()` | 
`public void `[`OnRemove`](#classCMonster_1a487dd6e938cf50ae39463f12930421ba)`()` | 
`public CPlayer * `[`GetClosestNormalPlayer`](#classCMonster_1a04207d77ca28962f187c7eb195c21502)`()` | 

## Members

#### `public  `[`CMonster`](#classCMonster_1a32b5519b2c5d14881927b69436972c8f)`(CMonsterInfo * pMacro,int nX,int nY)` 

#### `public  `[`~CMonster`](#classCMonster_1ab65729aa7d7b0e4f9092f8ae5e33b34d)`()` 

#### `public Packet `[`GenerateCreatePacket`](#classCMonster_1aaebb18996775b6910623e8b468afb15b)`(bool bHero)` 

#### `public Packet `[`GenerateDeletePacket`](#classCMonster_1a1421dbb2db974af7b5c3a2d167e8e793)`()` 

#### `public Packet `[`GenerateMovePacket`](#classCMonster_1a36c4a1434097b4663dc9e425642759c5)`(BYTE byType,char byX,char byY,char byZ)` 

#### `public inline WORD `[`GetStr`](#classCMonster_1a3ae5c18a6c0822c88f074e18e73e5875)`() const` 

#### `public inline WORD `[`GetHth`](#classCMonster_1abe75aa7d1e1fc575329bf141d3968936)`() const` 

#### `public inline WORD `[`GetInt`](#classCMonster_1abe6a411372dbc1f9ce80b349e125f068)`() const` 

#### `public inline WORD `[`GetWis`](#classCMonster_1a703b84211544a29e42f664e4aaae06c5)`() const` 

#### `public inline WORD `[`GetAgi`](#classCMonster_1a54207d4061d825c5702b1d2edf00acc1)`() const` 

#### `public WORD `[`GetHit`](#classCMonster_1ae2baaa85bbc125cdcd97b87d6e2a4018)`() const` 

#### `public WORD `[`GetDodge`](#classCMonster_1a8a259592a5dfb88fc087f0561b252f7d)`() const` 

#### `public inline WORD `[`GetDefense`](#classCMonster_1a791be6bc0cb0b56486cae92b4398db89)`(BYTE byType) const` 

#### `public inline BYTE `[`GetAbsorb`](#classCMonster_1a4c89df0e2e869953f069c025ff72affe)`() const` 

#### `public DWORD `[`GetMaxHP`](#classCMonster_1a524e9af6974fae1133f6696bbc6b4b07)`() const` 

#### `public WORD `[`GetMaxMP`](#classCMonster_1ae4af787fa0bca32d846f1710e1b788bf)`() const` 

#### `public WORD `[`GetMinAttack`](#classCMonster_1a897e6cbae9eca095be13ee460d79803f)`() const` 

#### `public WORD `[`GetMaxAttack`](#classCMonster_1a3b1074c3953f2cc5f37923bb2ed84c5d)`() const` 

#### `public WORD `[`GetMinMagic`](#classCMonster_1afc4a6486c348db9411aa1246c6e18387)`() const` 

#### `public WORD `[`GetMaxMagic`](#classCMonster_1abc571b26b8f78c5c0b7a000cbfcc7505)`() const` 

#### `public WORD `[`GetResist`](#classCMonster_1a42c7bb7d9c13d7449a20daac57a99dc4)`(BYTE byResist) const` 

#### `public inline WORD `[`GetIndex`](#classCMonster_1a1646f77a24fa39435d018715886b1a41)`() const` 

#### `public inline BYTE `[`GetRace`](#classCMonster_1a5951e0b264526d6b693a79cfff5de93a)`() const` 

#### `public inline BYTE `[`GetLevel`](#classCMonster_1a25481d93a1846d61c5669523a046b30e)`() const` 

#### `public inline WORD `[`GetRange`](#classCMonster_1ac2f91ca1773289b6079dad01c4b00153)`() const` 

#### `public inline WORD `[`GetWalkSpeed`](#classCMonster_1a0b2d80ce5652aea191e6f93931fe2e0a)`() const` 

#### `public inline WORD `[`GetRunSpeed`](#classCMonster_1a51f0e1e2bdef76192d41ebc9245ecd33)`() const` 

#### `public inline WORD `[`GetAttackSpeed`](#classCMonster_1a57f3ffe3d5cc777f141722234cc63053)`() const` 

#### `public inline WORD `[`GetCloseSight`](#classCMonster_1aefd1e77d3ae282cf9c16c6513e31eccd)`() const` 

#### `public inline WORD `[`GetFarSight`](#classCMonster_1ab70ab33fddbd8b75951316ab6fb2a513)`() const` 

#### `public inline WORD `[`GetSize`](#classCMonster_1a43151e7805dab9ec7979a4d72b17d358)`() const` 

#### `public void `[`SetTarget`](#classCMonster_1ab3bd3e1c4ce30e20e508d9710a303f09)`(CPlayer * pPlayer)` 

#### `public inline CPlayer * `[`GetTarget`](#classCMonster_1a9882ba63a0c0d7e73ec92db540deac93)`() const` 

#### `public virtual void `[`Tick`](#classCMonster_1a729a91a7d77275414420ca0b33c61698)`()` 

#### `public inline virtual void `[`AI`](#classCMonster_1ade33da94e0ab0cf8cd2745a7eb8c0058)`(DWORD dwNow)` 

#### `public void `[`Move`](#classCMonster_1a50baf7e342893c3fc492d3cc1edae898)`(char byX,char byY,BYTE byType)` 

#### `public void `[`Attack`](#classCMonster_1a3da2c9537b0a47d96779d05f61685268)`(CPlayer * pTarget)` 

#### `public bool `[`Chase`](#classCMonster_1ae490f08e7bfe5554be953ca8b29b7100)`()` 

#### `public void `[`Damage`](#classCMonster_1a55b2fbb18cec0f6e079f30d2eb524496)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` 

#### `public void `[`ScanSight`](#classCMonster_1a4564ee9d1505a874aefc283e1e620b07)`()` 

#### `public void `[`OnWalk`](#classCMonster_1a32fa534488bc60df3006fd2f50b2be18)`()` 

#### `public void `[`OnChase`](#classCMonster_1ad042edbe7a8b97cbdee38916d9925a6b)`()` 

#### `public void `[`OnForceAttack`](#classCMonster_1a1d5aa5527a1275e23b59691510f9d3a9)`()` 

#### `public void `[`OnAttack`](#classCMonster_1ae2b4d010e8adb89afe41b62d6ee07b1d)`()` 

#### `public void `[`OnRemove`](#classCMonster_1a487dd6e938cf50ae39463f12930421ba)`()` 

#### `public CPlayer * `[`GetClosestNormalPlayer`](#classCMonster_1a04207d77ca28962f187c7eb195c21502)`()` 

# class `CMonsterMaguni` 

```
class CMonsterMaguni
  : public CMonster
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CMonsterMaguni`](#classCMonsterMaguni_1a746ef64815005361d9e14f7bfe1f7990)`(CMonsterInfo * pMacro,int nX,int nY)` | 
`public void `[`Die`](#classCMonsterMaguni_1a835b6b8524f862cfce79232167475a27)`()` | 

## Members

#### `public inline  `[`CMonsterMaguni`](#classCMonsterMaguni_1a746ef64815005361d9e14f7bfe1f7990)`(CMonsterInfo * pMacro,int nX,int nY)` 

#### `public void `[`Die`](#classCMonsterMaguni_1a835b6b8524f862cfce79232167475a27)`()` 

# class `CMonsterReal` 

```
class CMonsterReal
  : public CMonster
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CMonsterReal`](#classCMonsterReal_1a5f870bceef461c11ac5dba3bc0d4d44c)`(CMonsterInfo * pMacro,int nX,int nY)` | 
`public void `[`Die`](#classCMonsterReal_1a9bec24d9b20c0bf8722892ccd70694ed)`()` | 

## Members

#### `public inline  `[`CMonsterReal`](#classCMonsterReal_1a5f870bceef461c11ac5dba3bc0d4d44c)`(CMonsterInfo * pMacro,int nX,int nY)` 

#### `public void `[`Die`](#classCMonsterReal_1a9bec24d9b20c0bf8722892ccd70694ed)`()` 

# class `CNPC` 

```
class CNPC
  : public CCharacter
```  

Class representation of NPC such as merchants and more.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CNPC`](#classCNPC_1a441f45b092391de84d52b07392c5de7b)`(NPC_DESC & desc)` | Basic constructor for NPC. Assigns macro values from InitNPC.xml. 
`public inline int `[`GetHTML`](#classCNPC_1a2068c2b84830ac3951ea25ac88fc4bd7)`() const` | Example: if X is returned, could be used to open e.pk s00000X.dat 
`public Packet `[`GenerateCreatePacket`](#classCNPC_1a80eaf3493958ca2de09e590ed0b27f77)`(bool bHero)` | Generates packet with information how NPC looks and behave. It is required to distribute this packet to clients each time they appear in sight. 
`public Packet `[`GenerateDeletePacket`](#classCNPC_1aa2ade1c301076c2d0b838dd17602f14b)`()` | Generates information about NPC deletion. Prepares packet for distribution among clients that disappear from its sight. 

## Members

#### `public  `[`CNPC`](#classCNPC_1a441f45b092391de84d52b07392c5de7b)`(NPC_DESC & desc)` 

Basic constructor for NPC. Assigns macro values from InitNPC.xml. 
#### Parameters
* `desc` Description struct loaded from InitNPC.xml

#### `public inline int `[`GetHTML`](#classCNPC_1a2068c2b84830ac3951ea25ac88fc4bd7)`() const` 

Example: if X is returned, could be used to open e.pk s00000X.dat 
#### Returns
File index linked to e.pk.

#### `public Packet `[`GenerateCreatePacket`](#classCNPC_1a80eaf3493958ca2de09e590ed0b27f77)`(bool bHero)` 

Generates packet with information how NPC looks and behave. It is required to distribute this packet to clients each time they appear in sight. 
#### Parameters
* `bHero` Neither true or false does not affect NPC. 

#### Returns
Generated packet ready to be sent.

#### `public Packet `[`GenerateDeletePacket`](#classCNPC_1aa2ade1c301076c2d0b838dd17602f14b)`()` 

Generates information about NPC deletion. Prepares packet for distribution among clients that disappear from its sight. 
#### Returns
Generated packet ready to be sent.

# class `CParty` 

Class representation of ingame Party. Group of Players playing together.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Access `[`m_Access`](#classCParty_1ac3e5b32446a861d0c6995821bcfa3f24) | Keeps track if instance is busy or not.
`public  `[`CParty`](#classCParty_1a872fa5aa5fd489176e7292b6710c2fac)`(CPlayer * pLeader,CPlayer * pPlayer)` | Basic party constructor. Takes two players which start a new party. 
`public  `[`~CParty`](#classCParty_1af644bea4e9858a9f6611da9530d67068)`()` | Basic destructor. Removes party from global party list before destruction.
`public void `[`Teleport`](#classCParty_1a05f3b32e5c3a3eb0b4dd6622b557ad73)`(int nX,int nY,int nSpread)` | Teleports all party members to given position. Given spread value, it will randomize position in certain distance. 
`public inline int `[`GetID`](#classCParty_1a16b86dbcb785c1a1a27ccff53a065f66)`() const` | Retrieves party ID assigned while creation. Party IDs are assigned starting from 1 up to MAX INT value. 
`public inline int `[`GetSize`](#classCParty_1ad1f129c94a89a24cfa47c9be9b9f8713)`() const` | #### Returns
`public bool `[`IsHead`](#classCParty_1a7c9f05fdf9bb4010b2158c96383d8fe0)`(CPlayer * pPlayer)` | Finds out whether player is currently a leader or not. Leadership may change during party lifetime. 
`public void `[`Discard`](#classCParty_1a705e833cada5faed26ce8b5c04f3b4e2)`()` | Removes last member from party. Should be called only once per party, right before deletion. WARNING: Depreciated
`public CPlayer * `[`FindLeader`](#classCParty_1a52f4a3135d2eab55983e22cb1860d5a8)`()` | Finds leader of the party. Grants access, so it **must** be released after usage. 
`public void `[`AddMember`](#classCParty_1ac13046f8b7e23785cc9962728fe3e6a0)`(CPlayer * pPlayer)` | Adds member to last position of the party. Assigns party ID to player and resets his party invitation ID. Additionally, it distributes new player list packet among all party members. 
`public void `[`RemoveMember`](#classCParty_1ab9a01f6cf295c33c4cf79659c966557f)`(CPlayer * pPlayer)` | If given player is a member, removes him. Resets player party ID and sends party exit packet. Broadcasts new party list packet to other party members. 
`public void `[`UpdateMemberHP`](#classCParty_1aea4bf8fe276d1e3ce497a00af4842ea7)`(CPlayer * pPlayer)` | Sends packet with CurHP & MaxHP update information to all party members. 
`public void `[`UpdateMemberLevel`](#classCParty_1a18e32064380190344131144f41e1f6f7)`(CPlayer * pPlayer)` | Send packet with level update information to all party members. 
`public void `[`SendPartyInfo`](#classCParty_1a255416d9ffe853b5bd7b0af497f00132)`()` | Sends information about ID, Name, Class, Level, CurHP, MaxHP of all party members to all party members. Does nothing if party is invalid (size smaller than 2). Client uses the information to update party window.
`public void `[`SendPositionInfo`](#classCParty_1a5883da3a529af5b03909a8a3489942b4)`()` | Sends information about position (ID, X, Y) of all party members to all party members. Does nothing if party is invalid (size smaller than 2). Client uses the information to update minimap.
`public void `[`Tick`](#classCParty_1a1efabe746539b197733a150bb5f04f3c)`()` | Gets executed once a second.
`public void `[`Broadcast`](#classCParty_1aa6308c6b9659b2033852efa4dae3b75f)`(BYTE byType,...)` | Distributes packet among all party members. 
`public void `[`Broadcast`](#classCParty_1af2141329a51494ea76985442dcddd0d9)`(Packet & packet)` | Distributes packet among all party members. 

## Members

#### `public Access `[`m_Access`](#classCParty_1ac3e5b32446a861d0c6995821bcfa3f24) 

Keeps track if instance is busy or not.

#### `public  `[`CParty`](#classCParty_1a872fa5aa5fd489176e7292b6710c2fac)`(CPlayer * pLeader,CPlayer * pPlayer)` 

Basic party constructor. Takes two players which start a new party. 
#### Parameters
* `pLeader` Leader of newly created party. 

* `pPlayer` Second player of newly created party.

#### `public  `[`~CParty`](#classCParty_1af644bea4e9858a9f6611da9530d67068)`()` 

Basic destructor. Removes party from global party list before destruction.

#### `public void `[`Teleport`](#classCParty_1a05f3b32e5c3a3eb0b4dd6622b557ad73)`(int nX,int nY,int nSpread)` 

Teleports all party members to given position. Given spread value, it will randomize position in certain distance. 
#### Parameters
* `nX` X map coordinate. 

* `nY` Y map coordinate. 

* `nSpread` Distance around X and Y.

#### `public inline int `[`GetID`](#classCParty_1a16b86dbcb785c1a1a27ccff53a065f66)`() const` 

Retrieves party ID assigned while creation. Party IDs are assigned starting from 1 up to MAX INT value. 
#### Returns
Party ID

#### `public inline int `[`GetSize`](#classCParty_1ad1f129c94a89a24cfa47c9be9b9f8713)`() const` 

#### Returns
Amount of members currently in the party.

#### `public bool `[`IsHead`](#classCParty_1a7c9f05fdf9bb4010b2158c96383d8fe0)`(CPlayer * pPlayer)` 

Finds out whether player is currently a leader or not. Leadership may change during party lifetime. 
#### Parameters
* `pPlayer` Player to be checked for leadership 

#### Returns
true if player is head, false otherwise

#### `public void `[`Discard`](#classCParty_1a705e833cada5faed26ce8b5c04f3b4e2)`()` 

Removes last member from party. Should be called only once per party, right before deletion. WARNING: Depreciated

#### `public CPlayer * `[`FindLeader`](#classCParty_1a52f4a3135d2eab55983e22cb1860d5a8)`()` 

Finds leader of the party. Grants access, so it **must** be released after usage. 
#### Returns
NULL if party is empty, leader player otherwise

#### `public void `[`AddMember`](#classCParty_1ac13046f8b7e23785cc9962728fe3e6a0)`(CPlayer * pPlayer)` 

Adds member to last position of the party. Assigns party ID to player and resets his party invitation ID. Additionally, it distributes new player list packet among all party members. 
#### Parameters
* `pPlayer` New player to be added to party

#### `public void `[`RemoveMember`](#classCParty_1ab9a01f6cf295c33c4cf79659c966557f)`(CPlayer * pPlayer)` 

If given player is a member, removes him. Resets player party ID and sends party exit packet. Broadcasts new party list packet to other party members. 
#### Parameters
* `pPlayer` Player to be removed from party

#### `public void `[`UpdateMemberHP`](#classCParty_1aea4bf8fe276d1e3ce497a00af4842ea7)`(CPlayer * pPlayer)` 

Sends packet with CurHP & MaxHP update information to all party members. 
#### Parameters
* `pPlayer` Player whose HP has been changed Client uses the information to update party window.

#### `public void `[`UpdateMemberLevel`](#classCParty_1a18e32064380190344131144f41e1f6f7)`(CPlayer * pPlayer)` 

Send packet with level update information to all party members. 
#### Parameters
* `pPlayer` Player whose level has been changed Client uses the information to update party window.

#### `public void `[`SendPartyInfo`](#classCParty_1a255416d9ffe853b5bd7b0af497f00132)`()` 

Sends information about ID, Name, Class, Level, CurHP, MaxHP of all party members to all party members. Does nothing if party is invalid (size smaller than 2). Client uses the information to update party window.

#### `public void `[`SendPositionInfo`](#classCParty_1a5883da3a529af5b03909a8a3489942b4)`()` 

Sends information about position (ID, X, Y) of all party members to all party members. Does nothing if party is invalid (size smaller than 2). Client uses the information to update minimap.

#### `public void `[`Tick`](#classCParty_1a1efabe746539b197733a150bb5f04f3c)`()` 

Gets executed once a second.

#### `public void `[`Broadcast`](#classCParty_1aa6308c6b9659b2033852efa4dae3b75f)`(BYTE byType,...)` 

Distributes packet among all party members. 
#### Parameters
* `byType` Packet header ID (from MainProtocol.h) 

* `...` First goes data format (ex. "bddb") and then values matching that format. Example: Broadcast(S2C_CHATTING, "sd", "String", 150);

#### `public void `[`Broadcast`](#classCParty_1af2141329a51494ea76985442dcddd0d9)`(Packet & packet)` 

Distributes packet among all party members. 
#### Parameters
* `packet` Generated packet ready to be sent.

# class `CPlayer` 

```
class CPlayer
  : public CCharacter
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CPlayer`](#classCPlayer_1a188a2d1ddfae18bd1281031fbb4d5e38)`(int nCID,D2S_LOADPLAYER_DESC & desc)` | 
`public  `[`~CPlayer`](#classCPlayer_1ad02df04887bccfe3b82298895da24af6)`()` | 
`public inline int `[`GetAID`](#classCPlayer_1a048b7e0a5eb6324a6396c79ac19f1fa7)`() const` | 
`public inline int `[`GetPID`](#classCPlayer_1a8b3eeffe39bd10c1ca442abf522c3d3a)`() const` | 
`public inline int `[`GetCID`](#classCPlayer_1ae63162d22c160863a7cfc575b8e04722)`() const` | 
`public inline WORD `[`GetStr`](#classCPlayer_1a12b1cc4176b930081cd65578850adec4)`() const` | 
`public inline WORD `[`GetHth`](#classCPlayer_1a95334779906a25556f928c11e56f7b56)`() const` | 
`public inline WORD `[`GetInt`](#classCPlayer_1af72d874a5af5b52d9ec2938779c3fbfa)`() const` | 
`public inline WORD `[`GetWis`](#classCPlayer_1a47548e6b4199eb573d8d10127a074145)`() const` | 
`public inline WORD `[`GetAgi`](#classCPlayer_1a7a38f160048d70f365307223f5759692)`() const` | 
`public inline WORD `[`GetPUPoint`](#classCPlayer_1a34efe8d8fd94399e34ed86e3f8d4216f)`() const` | 
`public inline WORD `[`GetSUPoint`](#classCPlayer_1a24b7234e0c8d14ef168c94bc7fe76af5)`() const` | 
`public inline WORD `[`GetContribute`](#classCPlayer_1ad4df1acf599fe2d577fe792b0bacdb93)`() const` | 
`public inline int `[`GetAnger`](#classCPlayer_1a3831255da9326e7c263de568fbf63257)`() const` | 
`public inline BYTE `[`GetLevel`](#classCPlayer_1ad10ef4ef34dd4e1035d94e9240a5c09b)`() const` | 
`public WORD `[`GetHit`](#classCPlayer_1a81798f3557fcdf8494da043e3c1b6c82)`() const` | 
`public WORD `[`GetDodge`](#classCPlayer_1a578c2e4f1ed228c4685e425995e910ac)`() const` | 
`public WORD `[`GetDefense`](#classCPlayer_1ad85bbb2de0adf0ac6cce72b207bb2583)`(BYTE byType) const` | 
`public inline BYTE `[`GetAbsorb`](#classCPlayer_1aae6df796a50ca12187e3e8b6c9913ac7)`() const` | 
`public DWORD `[`GetMaxHP`](#classCPlayer_1a076c69138624fb583d71fa3cc934d40e)`() const` | 
`public WORD `[`GetMaxMP`](#classCPlayer_1a0d60b187885fb7fae265ec9765787cdf)`() const` | 
`public WORD `[`GetMinAttack`](#classCPlayer_1aac4c02f19a838eaaeaa99e49b3715214)`() const` | 
`public WORD `[`GetMaxAttack`](#classCPlayer_1a27c50b595315a28a4bdd386d43e7a0de)`() const` | 
`public WORD `[`GetMinMagic`](#classCPlayer_1a02aa68f148233dc6b2583679d2e09e85)`() const` | 
`public WORD `[`GetMaxMagic`](#classCPlayer_1a57ee4479d9479c05e417fecd8db4f72b)`() const` | 
`public WORD `[`GetResist`](#classCPlayer_1a49683c0d44dd50bf2fd04da12c35f22a)`(BYTE byResist) const` | 
`public inline WORD `[`GetSize`](#classCPlayer_1a210b68fc20059faf22ee6db112059564)`() const` | 
`public inline __int64 `[`GetExp`](#classCPlayer_1acca893ea6247ff70bc6e6867ab4e766b)`() const` | 
`public inline BYTE `[`GetGrade`](#classCPlayer_1a04d9afd2b1373b1b1faa47956ff59496)`() const` | 
`public inline std::string `[`GetGuildName`](#classCPlayer_1a80103fc73f68c01bf2ca828ca21b8b06)`() const` | 
`public inline std::string `[`GetGuildClass`](#classCPlayer_1a5da8be16c93e8fa15ac2fe14dff41eaf)`() const` | 
`public inline int `[`GetGID`](#classCPlayer_1a3462bdefacb2ffa40bf5ddfb298193e9)`() const` | 
`public inline BYTE `[`GetGRole`](#classCPlayer_1afc3ba28f3219207b2611a8438b9a498a)`() const` | 
`public inline std::string `[`GetName`](#classCPlayer_1a9800223dcf5110569422872cdcd26777)`() const` | 
`public inline BYTE `[`GetSpecialty`](#classCPlayer_1a18b06e272e8ae2327c28f5b032058991)`() const` | 
`public inline BYTE `[`GetHair`](#classCPlayer_1a724bbfffe8b8c25639ef965f25be1958)`() const` | 
`public inline BYTE `[`GetFace`](#classCPlayer_1ae538e492b44fcd7779cb96db1163c5ae)`() const` | 
`public inline BYTE `[`GetFlag`](#classCPlayer_1a195d618ca74e78d773c931ef437e301b)`() const` | 
`public inline int `[`GetFlagItem`](#classCPlayer_1a38cba46d6a535fa7241dc2cc0f3fd4b7)`() const` | 
`public inline int `[`GetHonorGrade`](#classCPlayer_1ac20c08fe8b5d6f1c489e97d0092eba89)`() const` | 
`public inline int `[`GetHonorOption`](#classCPlayer_1a90d37bce7d8eeed5e16e07afd61f21fc)`() const` | 
`public inline BYTE `[`GetTrigramLevel`](#classCPlayer_1a1f1b456ff15b8ee7e4b0557812d984cb)`() const` | 
`public inline int `[`GetGear`](#classCPlayer_1a9869086cc18c037d35d8ce89b4329bd2)`(BYTE byType) const` | 
`public void `[`OnPutOnGear`](#classCPlayer_1af73f72d6dbea618f8abf94fcfefa4604)`(CItem * pItem)` | 
`public void `[`OnPutOffGear`](#classCPlayer_1ae95e4f94f9302b5f68809195a5f6a32f)`(CItem * pItem)` | 
`public inline bool `[`IsWState`](#classCPlayer_1abe3edf815b4200d626e1d388d64d622c)`(__int64 n64WState) const` | 
`public inline bool `[`IsAnyTrigramState`](#classCPlayer_1afec9b8f2aa3338355faa46932704b0c3)`() const` | 
`public inline bool `[`IsAllTrigramState`](#classCPlayer_1a2a3d2c22aca7de4e7d53316b4c23e97d)`() const` | 
`public inline void `[`AddWState`](#classCPlayer_1af02ed0fe00a02c621e51feff73aa2d6a)`(__int64 n64WState)` | 
`public inline void `[`SubWState`](#classCPlayer_1a3198e19e08884be776026742ee77e468)`(__int64 n64WState)` | 
`public WORD `[`GetReqPU`](#classCPlayer_1a9974f64ad73cb961fc2e60ea439adbdd)`(BYTE * byStats)` | 
`public bool `[`Write`](#classCPlayer_1ad7b5f46be6d153bb65c39d0375520107)`(BYTE byType,...)` | 
`public void `[`SendPacket`](#classCPlayer_1a4c247e341ba63d7a87c98ae88ab026c2)`(Packet & packet)` | 
`public Packet `[`GenerateCreatePacket`](#classCPlayer_1a00b932835db9866881bc96756abc3657)`(bool bHero)` | 
`public Packet `[`GeneratePetPacket`](#classCPlayer_1a52bfdfdcfc96a0fbf5009a9de583ee04)`()` | 
`public Packet `[`GenerateDeletePacket`](#classCPlayer_1a7e4b4e01e827869456f0066f9f25a81b)`()` | 
`public Packet `[`GenerateMovePacket`](#classCPlayer_1afb5c71e1a2c66d3a71d315760d4082ed)`(BYTE byType,char byX,char byY,char byZ)` | 
`public void `[`Process`](#classCPlayer_1a618e99ee1c2a0ae81130a2468748838e)`(Packet packet)` | 
`public void `[`Tick`](#classCPlayer_1ae4c64cd8d2e808114db23593ff6c5816)`()` | 
`public void `[`OnLoadPlayer`](#classCPlayer_1a44552908ba4a38ae9c69e68962376d43)`()` | 
`public void `[`OnLoadItems`](#classCPlayer_1a73e13fe05b734d20b9fc2222285afc21)`(char * p)` | 
`public void `[`GameStart`](#classCPlayer_1a6be7062c85dcdbbdee4f1e50f4240c3f)`()` | 
`public void `[`GameRestart`](#classCPlayer_1ade947d3c70f95c6b0d06f1910a0c4570)`()` | 
`public bool `[`CanMove`](#classCPlayer_1a266c70cd463694f6b6a85df3879abaea)`()` | 
`public bool `[`CanAttack`](#classCPlayer_1aa0d84ab2dfc47ffc72482a9aca7d2fa4)`(CCharacter * pTarget) const` | 
`public void `[`OnMove`](#classCPlayer_1a09cd92ba2e8c02fc988e131451b71947)`(char byX,char byY,char byZ,char byType)` | 
`public void `[`Rest`](#classCPlayer_1a94fc77afb40ef82347dba19d2f5bf6f5)`(BYTE byType)` | 
`public void `[`ProcessMsg`](#classCPlayer_1a88c5bae35d7e2c53454b4f51024ede89)`(char * szMsg)` | 
`public void `[`ChatCommand`](#classCPlayer_1ad521bb1c30a2c4a898a780b9c56d1937)`(char * szCommand)` | 
`public void `[`UpdateProperty`](#classCPlayer_1a8f8e7e0a865b2ffafe7c2b6dbd810133)`(BYTE byProperty,__int64 n64Amount)` | 
`public void `[`Teleport`](#classCPlayer_1a097558aaa187c826ec56582625a985ae)`(int nX,int nY,int nSpread,int nZ)` | 
`public void `[`OnTeleport`](#classCPlayer_1aa99497fd4a25d00c58c1679916fe05cf)`(BYTE byAnswer,int nZ)` | 
`public void `[`InsertItem`](#classCPlayer_1a8950f3ae31c929fe3ef291cc19de7deb)`(WORD wIndex,int nNum,BYTE byLogType,bool bOwn,bool bForceSingular,BYTE byPrefix,BYTE byXAttack,BYTE byXMagic,BYTE byXHit,BYTE byEBlow,int nInfo,BYTE byXDodge,BYTE byXDefense,FUSION_DESC * pFuse,BYTE byShot,WORD wPerforation,int nGongLeft,int nGongRight)` | 
`public bool `[`MergeItem`](#classCPlayer_1a9e6e45ebe10f4ed34ba5a8431c7c5faf)`(WORD wIndex,int nNum,BYTE byLogType,bool bOwn)` | 
`public bool `[`UseItem`](#classCPlayer_1abe919deb009679672f8b749100fcad9c)`(CItem * pItem)` | 
`public void `[`PutOnItem`](#classCPlayer_1ab76927857016659cdd172c1e480b4c29)`(CItem * pItem)` | 
`public void `[`PutOffItem`](#classCPlayer_1ac78ab733d3fdc84a855b93ea0165647c)`(CItem * pItem)` | 
`public void `[`Damage`](#classCPlayer_1ade03bd4c423364b93dbbb87c9f1701ef)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` | 
`public void `[`Die`](#classCPlayer_1aea5393068e04bd1f5ee2f37f28650de5)`()` | 
`public void `[`Revival`](#classCPlayer_1a6388bcc9a284184363be8d01f83db44f)`()` | 
`public void `[`Attack`](#classCPlayer_1a6b6dbcc48f145d2731ba99653d383d15)`(CCharacter * pTarget)` | 
`public bool `[`CheckBlock`](#classCPlayer_1a3a02754b59bc6283583797ea15ebbfe7)`(CCharacter * pAttacker) const` | 
`public bool `[`RemoveItem`](#classCPlayer_1a01ccc12f76a762f0024d1dc6a54bf6cd)`(CItem * pItem,int nNum,BYTE byLogType)` | 
`public void `[`RemoveItem`](#classCPlayer_1a2c5a636b4bca0d2843199ea09f0accfa)`(WORD wIndex,int nNum,BYTE byLogType)` | 
`public void `[`SaveAllProperty`](#classCPlayer_1aaa8c88a78b3562a82459de23e6b9ad77)`()` | 
`public void `[`SendProperty`](#classCPlayer_1ab20b931268d1e2fa873f21fd4d19ab45)`()` | 
`public void `[`ApplySpec`](#classCPlayer_1a20c76a872e4b67be38755eaa3ccbe3d7)`(CItem * pItem)` | 
`public void `[`FreeSpec`](#classCPlayer_1ac35c72e50408c7ed7a519d45c06f1a39)`(CItem * pItem)` | 
`public inline int `[`GetPartyID`](#classCPlayer_1a41f01f7472f592975eba70265d9b6eca)`() const` | 
`public inline void `[`SetPartyID`](#classCPlayer_1ae9801e3bf59477037d93cfdf1d155592)`(int nID)` | 
`public inline void `[`SetPartyInviterID`](#classCPlayer_1ade6b21dfe81ae894f58d206904f5d7b8)`(int nID)` | 
`public inline int `[`GetPartyInviterID`](#classCPlayer_1ad656bf549083b5009bac49c4baa5c6d5)`() const` | 
`public inline bool `[`HasParty`](#classCPlayer_1a2a6260ab8ce10eeb3df9443c7b62c449)`() const` | 
`public void `[`AskParty`](#classCPlayer_1a6230984fa6040d6decb1793c883b746a)`(CPlayer * pPlayer)` | 
`public void `[`LeaveParty`](#classCPlayer_1a1382ab608b108bf4dd4dd8ddb55e3d91)`()` | 
`public void `[`RemoveAggro`](#classCPlayer_1a542f63a05b151ea4fa6688d201448f11)`()` | 
`public void `[`IntoInven`](#classCPlayer_1ac604286ac82475d0afee168e5374f785)`(CItem * pItem)` | 
`public void `[`OutofInven`](#classCPlayer_1a63166723e4154efed1c48a67051da82d)`(CItem * pItem)` | 
`public void `[`EmptyInven`](#classCPlayer_1a4daa6280bc84d3e3633d92832594dea6)`()` | 
`public CItem * `[`FindItem`](#classCPlayer_1a002feea76f8ff73aae3d19504b2d4335)`(WORD wIndex,BYTE byOwn)` | 
`public CItem * `[`FindItemByIID`](#classCPlayer_1a140483d4beb5a9dae7a929d2562feaa0)`(int nIID)` | 

## Members

#### `public  `[`CPlayer`](#classCPlayer_1a188a2d1ddfae18bd1281031fbb4d5e38)`(int nCID,D2S_LOADPLAYER_DESC & desc)` 

#### `public  `[`~CPlayer`](#classCPlayer_1ad02df04887bccfe3b82298895da24af6)`()` 

#### `public inline int `[`GetAID`](#classCPlayer_1a048b7e0a5eb6324a6396c79ac19f1fa7)`() const` 

#### `public inline int `[`GetPID`](#classCPlayer_1a8b3eeffe39bd10c1ca442abf522c3d3a)`() const` 

#### `public inline int `[`GetCID`](#classCPlayer_1ae63162d22c160863a7cfc575b8e04722)`() const` 

#### `public inline WORD `[`GetStr`](#classCPlayer_1a12b1cc4176b930081cd65578850adec4)`() const` 

#### `public inline WORD `[`GetHth`](#classCPlayer_1a95334779906a25556f928c11e56f7b56)`() const` 

#### `public inline WORD `[`GetInt`](#classCPlayer_1af72d874a5af5b52d9ec2938779c3fbfa)`() const` 

#### `public inline WORD `[`GetWis`](#classCPlayer_1a47548e6b4199eb573d8d10127a074145)`() const` 

#### `public inline WORD `[`GetAgi`](#classCPlayer_1a7a38f160048d70f365307223f5759692)`() const` 

#### `public inline WORD `[`GetPUPoint`](#classCPlayer_1a34efe8d8fd94399e34ed86e3f8d4216f)`() const` 

#### `public inline WORD `[`GetSUPoint`](#classCPlayer_1a24b7234e0c8d14ef168c94bc7fe76af5)`() const` 

#### `public inline WORD `[`GetContribute`](#classCPlayer_1ad4df1acf599fe2d577fe792b0bacdb93)`() const` 

#### `public inline int `[`GetAnger`](#classCPlayer_1a3831255da9326e7c263de568fbf63257)`() const` 

#### `public inline BYTE `[`GetLevel`](#classCPlayer_1ad10ef4ef34dd4e1035d94e9240a5c09b)`() const` 

#### `public WORD `[`GetHit`](#classCPlayer_1a81798f3557fcdf8494da043e3c1b6c82)`() const` 

#### `public WORD `[`GetDodge`](#classCPlayer_1a578c2e4f1ed228c4685e425995e910ac)`() const` 

#### `public WORD `[`GetDefense`](#classCPlayer_1ad85bbb2de0adf0ac6cce72b207bb2583)`(BYTE byType) const` 

#### `public inline BYTE `[`GetAbsorb`](#classCPlayer_1aae6df796a50ca12187e3e8b6c9913ac7)`() const` 

#### `public DWORD `[`GetMaxHP`](#classCPlayer_1a076c69138624fb583d71fa3cc934d40e)`() const` 

#### `public WORD `[`GetMaxMP`](#classCPlayer_1a0d60b187885fb7fae265ec9765787cdf)`() const` 

#### `public WORD `[`GetMinAttack`](#classCPlayer_1aac4c02f19a838eaaeaa99e49b3715214)`() const` 

#### `public WORD `[`GetMaxAttack`](#classCPlayer_1a27c50b595315a28a4bdd386d43e7a0de)`() const` 

#### `public WORD `[`GetMinMagic`](#classCPlayer_1a02aa68f148233dc6b2583679d2e09e85)`() const` 

#### `public WORD `[`GetMaxMagic`](#classCPlayer_1a57ee4479d9479c05e417fecd8db4f72b)`() const` 

#### `public WORD `[`GetResist`](#classCPlayer_1a49683c0d44dd50bf2fd04da12c35f22a)`(BYTE byResist) const` 

#### `public inline WORD `[`GetSize`](#classCPlayer_1a210b68fc20059faf22ee6db112059564)`() const` 

#### `public inline __int64 `[`GetExp`](#classCPlayer_1acca893ea6247ff70bc6e6867ab4e766b)`() const` 

#### `public inline BYTE `[`GetGrade`](#classCPlayer_1a04d9afd2b1373b1b1faa47956ff59496)`() const` 

#### `public inline std::string `[`GetGuildName`](#classCPlayer_1a80103fc73f68c01bf2ca828ca21b8b06)`() const` 

#### `public inline std::string `[`GetGuildClass`](#classCPlayer_1a5da8be16c93e8fa15ac2fe14dff41eaf)`() const` 

#### `public inline int `[`GetGID`](#classCPlayer_1a3462bdefacb2ffa40bf5ddfb298193e9)`() const` 

#### `public inline BYTE `[`GetGRole`](#classCPlayer_1afc3ba28f3219207b2611a8438b9a498a)`() const` 

#### `public inline std::string `[`GetName`](#classCPlayer_1a9800223dcf5110569422872cdcd26777)`() const` 

#### `public inline BYTE `[`GetSpecialty`](#classCPlayer_1a18b06e272e8ae2327c28f5b032058991)`() const` 

#### `public inline BYTE `[`GetHair`](#classCPlayer_1a724bbfffe8b8c25639ef965f25be1958)`() const` 

#### `public inline BYTE `[`GetFace`](#classCPlayer_1ae538e492b44fcd7779cb96db1163c5ae)`() const` 

#### `public inline BYTE `[`GetFlag`](#classCPlayer_1a195d618ca74e78d773c931ef437e301b)`() const` 

#### `public inline int `[`GetFlagItem`](#classCPlayer_1a38cba46d6a535fa7241dc2cc0f3fd4b7)`() const` 

#### `public inline int `[`GetHonorGrade`](#classCPlayer_1ac20c08fe8b5d6f1c489e97d0092eba89)`() const` 

#### `public inline int `[`GetHonorOption`](#classCPlayer_1a90d37bce7d8eeed5e16e07afd61f21fc)`() const` 

#### `public inline BYTE `[`GetTrigramLevel`](#classCPlayer_1a1f1b456ff15b8ee7e4b0557812d984cb)`() const` 

#### `public inline int `[`GetGear`](#classCPlayer_1a9869086cc18c037d35d8ce89b4329bd2)`(BYTE byType) const` 

#### `public void `[`OnPutOnGear`](#classCPlayer_1af73f72d6dbea618f8abf94fcfefa4604)`(CItem * pItem)` 

#### `public void `[`OnPutOffGear`](#classCPlayer_1ae95e4f94f9302b5f68809195a5f6a32f)`(CItem * pItem)` 

#### `public inline bool `[`IsWState`](#classCPlayer_1abe3edf815b4200d626e1d388d64d622c)`(__int64 n64WState) const` 

#### `public inline bool `[`IsAnyTrigramState`](#classCPlayer_1afec9b8f2aa3338355faa46932704b0c3)`() const` 

#### `public inline bool `[`IsAllTrigramState`](#classCPlayer_1a2a3d2c22aca7de4e7d53316b4c23e97d)`() const` 

#### `public inline void `[`AddWState`](#classCPlayer_1af02ed0fe00a02c621e51feff73aa2d6a)`(__int64 n64WState)` 

#### `public inline void `[`SubWState`](#classCPlayer_1a3198e19e08884be776026742ee77e468)`(__int64 n64WState)` 

#### `public WORD `[`GetReqPU`](#classCPlayer_1a9974f64ad73cb961fc2e60ea439adbdd)`(BYTE * byStats)` 

#### `public bool `[`Write`](#classCPlayer_1ad7b5f46be6d153bb65c39d0375520107)`(BYTE byType,...)` 

#### `public void `[`SendPacket`](#classCPlayer_1a4c247e341ba63d7a87c98ae88ab026c2)`(Packet & packet)` 

#### `public Packet `[`GenerateCreatePacket`](#classCPlayer_1a00b932835db9866881bc96756abc3657)`(bool bHero)` 

#### `public Packet `[`GeneratePetPacket`](#classCPlayer_1a52bfdfdcfc96a0fbf5009a9de583ee04)`()` 

#### `public Packet `[`GenerateDeletePacket`](#classCPlayer_1a7e4b4e01e827869456f0066f9f25a81b)`()` 

#### `public Packet `[`GenerateMovePacket`](#classCPlayer_1afb5c71e1a2c66d3a71d315760d4082ed)`(BYTE byType,char byX,char byY,char byZ)` 

#### `public void `[`Process`](#classCPlayer_1a618e99ee1c2a0ae81130a2468748838e)`(Packet packet)` 

#### `public void `[`Tick`](#classCPlayer_1ae4c64cd8d2e808114db23593ff6c5816)`()` 

#### `public void `[`OnLoadPlayer`](#classCPlayer_1a44552908ba4a38ae9c69e68962376d43)`()` 

#### `public void `[`OnLoadItems`](#classCPlayer_1a73e13fe05b734d20b9fc2222285afc21)`(char * p)` 

#### `public void `[`GameStart`](#classCPlayer_1a6be7062c85dcdbbdee4f1e50f4240c3f)`()` 

#### `public void `[`GameRestart`](#classCPlayer_1ade947d3c70f95c6b0d06f1910a0c4570)`()` 

#### `public bool `[`CanMove`](#classCPlayer_1a266c70cd463694f6b6a85df3879abaea)`()` 

#### `public bool `[`CanAttack`](#classCPlayer_1aa0d84ab2dfc47ffc72482a9aca7d2fa4)`(CCharacter * pTarget) const` 

#### `public void `[`OnMove`](#classCPlayer_1a09cd92ba2e8c02fc988e131451b71947)`(char byX,char byY,char byZ,char byType)` 

#### `public void `[`Rest`](#classCPlayer_1a94fc77afb40ef82347dba19d2f5bf6f5)`(BYTE byType)` 

#### `public void `[`ProcessMsg`](#classCPlayer_1a88c5bae35d7e2c53454b4f51024ede89)`(char * szMsg)` 

#### `public void `[`ChatCommand`](#classCPlayer_1ad521bb1c30a2c4a898a780b9c56d1937)`(char * szCommand)` 

#### `public void `[`UpdateProperty`](#classCPlayer_1a8f8e7e0a865b2ffafe7c2b6dbd810133)`(BYTE byProperty,__int64 n64Amount)` 

#### `public void `[`Teleport`](#classCPlayer_1a097558aaa187c826ec56582625a985ae)`(int nX,int nY,int nSpread,int nZ)` 

#### `public void `[`OnTeleport`](#classCPlayer_1aa99497fd4a25d00c58c1679916fe05cf)`(BYTE byAnswer,int nZ)` 

#### `public void `[`InsertItem`](#classCPlayer_1a8950f3ae31c929fe3ef291cc19de7deb)`(WORD wIndex,int nNum,BYTE byLogType,bool bOwn,bool bForceSingular,BYTE byPrefix,BYTE byXAttack,BYTE byXMagic,BYTE byXHit,BYTE byEBlow,int nInfo,BYTE byXDodge,BYTE byXDefense,FUSION_DESC * pFuse,BYTE byShot,WORD wPerforation,int nGongLeft,int nGongRight)` 

#### `public bool `[`MergeItem`](#classCPlayer_1a9e6e45ebe10f4ed34ba5a8431c7c5faf)`(WORD wIndex,int nNum,BYTE byLogType,bool bOwn)` 

#### `public bool `[`UseItem`](#classCPlayer_1abe919deb009679672f8b749100fcad9c)`(CItem * pItem)` 

#### `public void `[`PutOnItem`](#classCPlayer_1ab76927857016659cdd172c1e480b4c29)`(CItem * pItem)` 

#### `public void `[`PutOffItem`](#classCPlayer_1ac78ab733d3fdc84a855b93ea0165647c)`(CItem * pItem)` 

#### `public void `[`Damage`](#classCPlayer_1ade03bd4c423364b93dbbb87c9f1701ef)`(CCharacter * pAttacker,DWORD & dwDamage,BYTE & byType)` 

#### `public void `[`Die`](#classCPlayer_1aea5393068e04bd1f5ee2f37f28650de5)`()` 

#### `public void `[`Revival`](#classCPlayer_1a6388bcc9a284184363be8d01f83db44f)`()` 

#### `public void `[`Attack`](#classCPlayer_1a6b6dbcc48f145d2731ba99653d383d15)`(CCharacter * pTarget)` 

#### `public bool `[`CheckBlock`](#classCPlayer_1a3a02754b59bc6283583797ea15ebbfe7)`(CCharacter * pAttacker) const` 

#### `public bool `[`RemoveItem`](#classCPlayer_1a01ccc12f76a762f0024d1dc6a54bf6cd)`(CItem * pItem,int nNum,BYTE byLogType)` 

#### `public void `[`RemoveItem`](#classCPlayer_1a2c5a636b4bca0d2843199ea09f0accfa)`(WORD wIndex,int nNum,BYTE byLogType)` 

#### `public void `[`SaveAllProperty`](#classCPlayer_1aaa8c88a78b3562a82459de23e6b9ad77)`()` 

#### `public void `[`SendProperty`](#classCPlayer_1ab20b931268d1e2fa873f21fd4d19ab45)`()` 

#### `public void `[`ApplySpec`](#classCPlayer_1a20c76a872e4b67be38755eaa3ccbe3d7)`(CItem * pItem)` 

#### `public void `[`FreeSpec`](#classCPlayer_1ac35c72e50408c7ed7a519d45c06f1a39)`(CItem * pItem)` 

#### `public inline int `[`GetPartyID`](#classCPlayer_1a41f01f7472f592975eba70265d9b6eca)`() const` 

#### `public inline void `[`SetPartyID`](#classCPlayer_1ae9801e3bf59477037d93cfdf1d155592)`(int nID)` 

#### `public inline void `[`SetPartyInviterID`](#classCPlayer_1ade6b21dfe81ae894f58d206904f5d7b8)`(int nID)` 

#### `public inline int `[`GetPartyInviterID`](#classCPlayer_1ad656bf549083b5009bac49c4baa5c6d5)`() const` 

#### `public inline bool `[`HasParty`](#classCPlayer_1a2a6260ab8ce10eeb3df9443c7b62c449)`() const` 

#### `public void `[`AskParty`](#classCPlayer_1a6230984fa6040d6decb1793c883b746a)`(CPlayer * pPlayer)` 

#### `public void `[`LeaveParty`](#classCPlayer_1a1382ab608b108bf4dd4dd8ddb55e3d91)`()` 

#### `public void `[`RemoveAggro`](#classCPlayer_1a542f63a05b151ea4fa6688d201448f11)`()` 

#### `public void `[`IntoInven`](#classCPlayer_1ac604286ac82475d0afee168e5374f785)`(CItem * pItem)` 

#### `public void `[`OutofInven`](#classCPlayer_1a63166723e4154efed1c48a67051da82d)`(CItem * pItem)` 

#### `public void `[`EmptyInven`](#classCPlayer_1a4daa6280bc84d3e3633d92832594dea6)`()` 

#### `public CItem * `[`FindItem`](#classCPlayer_1a002feea76f8ff73aae3d19504b2d4335)`(WORD wIndex,BYTE byOwn)` 

#### `public CItem * `[`FindItemByIID`](#classCPlayer_1a140483d4beb5a9dae7a929d2562feaa0)`(int nIID)` 

# class `CServer` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `CTile` 

Represents square tile of 1024x1024 cells. Keeps track of all dynamic objects on that area.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`CTile`](#classCTile_1a80f91c7e0977f6f6bceae1fb79024b6b)`()` | Basic constructor.
`public void `[`Add`](#classCTile_1ae1d1eba417f121bd5a1b3bf7f656898b)`(CCharacter * pCharacter)` | Adds character to tile. Gets called when player enters this tile or enters game. 
`public void `[`Remove`](#classCTile_1a70bd90fe9bf75fd5240a024716f08e8a)`(CCharacter * pCharacter)` | Removes character from tile. Gets called when player enters another tile or quits the game completely. 
`public inline void `[`Lock`](#classCTile_1ab3fd197f9c845168067def319945ebbd)`()` | Locks access to instance.
`public inline void `[`Unlock`](#classCTile_1aa79119f95d52b30ed0b3e4e2418ee8a3)`()` | Unlocks access to instance
`public void `[`GetCharacterListAround`](#classCTile_1a001742dc06c5ca432e0bd1e8f7df4c9f)`(CCharacter * pCharacter,int nDistance,CharacterList & list)` | Retrieves all characters around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
`public void `[`GetPlayerListAround`](#classCTile_1a06c572865aef65b63a2665f93ee1560b)`(CCharacter * pCharacter,int nDistance,PlayerList & list)` | Retrieves all players around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
`public void `[`GetMonsterListAround`](#classCTile_1a500887d419a5fa9b93f2885a82180eb2)`(CCharacter * pCharacter,int nDistance,MonsterList & list)` | Retrieves all monsters around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
`public void `[`SendPacket`](#classCTile_1aa9c2599bc4e1e6f951bb887d30aba111)`(CCharacter * pCharacter,Packet & packet)` | Sends packet to all players on tile within sight of certain character. 
`public void `[`SendMoveAction`](#classCTile_1a34f85c8e4a1be51229b723fcadb72aa4)`(CCharacter * pCharacter,char byX,char byY,Packet & createPacket,Packet & petPacket,Packet & deletePacket,Packet & movePacket)` | Distributes appear/pet appear/disappear/move packets to players nearby. Decides who to send depending on character kind. 
`public void `[`ExchangeMoveActionWithPlayers`](#classCTile_1a6f71e25bfc3f826639300abc127fdd25)`(CCharacter * pCharacter,char byX,char byY,Packet & createPacket,Packet & petPacket,Packet & deletePacket,Packet & movePacket)` | Exchanges appear/pet appear/disappear/move packets with players nearby. Decides what to send depending on distance between objects. 
`public void `[`ExchangeMoveActionWithMonsters`](#classCTile_1ae7f50d3589419005ffb900182fd3d488)`(CPlayer * pPlayer,char byX,char byY)` | Exchanges appear/pet appear/disappear/move packets with monsters nearby. Decides what to send depending on distance between objects. 
`public void `[`ExchangeMoveActionWithNPCs`](#classCTile_1a30da262666aa379fa7f436496e8150c7)`(CPlayer * pPlayer,char byX,char byY)` | Exchanges appear/pet appear/disappear/move packets with NPCs nearby. Decides what to send depending on distance between objects. 

## Members

#### `public inline  `[`CTile`](#classCTile_1a80f91c7e0977f6f6bceae1fb79024b6b)`()` 

Basic constructor.

#### `public void `[`Add`](#classCTile_1ae1d1eba417f121bd5a1b3bf7f656898b)`(CCharacter * pCharacter)` 

Adds character to tile. Gets called when player enters this tile or enters game. 
#### Parameters
* `pCharacter` Object to add.

#### `public void `[`Remove`](#classCTile_1a70bd90fe9bf75fd5240a024716f08e8a)`(CCharacter * pCharacter)` 

Removes character from tile. Gets called when player enters another tile or quits the game completely. 
#### Parameters
* `pCharacter` Object to remove.

#### `public inline void `[`Lock`](#classCTile_1ab3fd197f9c845168067def319945ebbd)`()` 

Locks access to instance.

#### `public inline void `[`Unlock`](#classCTile_1aa79119f95d52b30ed0b3e4e2418ee8a3)`()` 

Unlocks access to instance

#### `public void `[`GetCharacterListAround`](#classCTile_1a001742dc06c5ca432e0bd1e8f7df4c9f)`(CCharacter * pCharacter,int nDistance,CharacterList & list)` 

Retrieves all characters around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
#### Parameters
* `pCharacter` Character to find objects around it. 

* `nDistance` Max distance from character. 

* `list` Empty list that will get populated with found characters.

#### `public void `[`GetPlayerListAround`](#classCTile_1a06c572865aef65b63a2665f93ee1560b)`(CCharacter * pCharacter,int nDistance,PlayerList & list)` 

Retrieves all players around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
#### Parameters
* `pCharacter` Character to find players around it. 

* `nDistance` Max distance from character. 

* `list` Empty list that will get populated with found players.

#### `public void `[`GetMonsterListAround`](#classCTile_1a500887d419a5fa9b93f2885a82180eb2)`(CCharacter * pCharacter,int nDistance,MonsterList & list)` 

Retrieves all monsters around certain character on a tile. Grants access to each one, so it is a **MUST** to release it after usage. 
#### Parameters
* `pCharacter` Character to find monsters around it. 

* `nDistance` Max distance from character. 

* `list` Empty list that will get populated with found monsters.

#### `public void `[`SendPacket`](#classCTile_1aa9c2599bc4e1e6f951bb887d30aba111)`(CCharacter * pCharacter,Packet & packet)` 

Sends packet to all players on tile within sight of certain character. 
#### Parameters
* `pCharacter` Character to send packet around it. 

* `packet` Packet to be sent.

#### `public void `[`SendMoveAction`](#classCTile_1a34f85c8e4a1be51229b723fcadb72aa4)`(CCharacter * pCharacter,char byX,char byY,Packet & createPacket,Packet & petPacket,Packet & deletePacket,Packet & movePacket)` 

Distributes appear/pet appear/disappear/move packets to players nearby. Decides who to send depending on character kind. 
#### Parameters
* `pCharacter` Character to exchange packets with. 

* `byX` X coordinate movement delta. 

* `byY` Y coordinate movement delta. 

* `createPacket` Pre-generated appear packet for distribution. 

* `petPacket` Pre-generated pet appear packet for distribution. 

* `deletePacket` Pre-generated disappear packet for distribution. 

* `movePacket` Pre-generated move packet for distribution.

#### `public void `[`ExchangeMoveActionWithPlayers`](#classCTile_1a6f71e25bfc3f826639300abc127fdd25)`(CCharacter * pCharacter,char byX,char byY,Packet & createPacket,Packet & petPacket,Packet & deletePacket,Packet & movePacket)` 

Exchanges appear/pet appear/disappear/move packets with players nearby. Decides what to send depending on distance between objects. 
#### Parameters
* `pCharacter` Character to exchange packets with. 

* `byX` X coordinate movement delta. 

* `byY` Y coordinate movement delta. 

* `createPacket` Pre-generated appear packet for distribution. 

* `petPacket` Pre-generated pet appear packet for distribution. 

* `deletePacket` Pre-generated disappear packet for distribution. 

* `movePacket` Pre-generated move packet for distribution.

#### `public void `[`ExchangeMoveActionWithMonsters`](#classCTile_1ae7f50d3589419005ffb900182fd3d488)`(CPlayer * pPlayer,char byX,char byY)` 

Exchanges appear/pet appear/disappear/move packets with monsters nearby. Decides what to send depending on distance between objects. 
#### Parameters
* `pPlayer` Player to exchange packets with. 

* `byX` X coordinate movement delta. 

* `byY` Y coordinate movement delta.

#### `public void `[`ExchangeMoveActionWithNPCs`](#classCTile_1a30da262666aa379fa7f436496e8150c7)`(CPlayer * pPlayer,char byX,char byY)` 

Exchanges appear/pet appear/disappear/move packets with NPCs nearby. Decides what to send depending on distance between objects. 
#### Parameters
* `pPlayer` Player to exchange packets with. 

* `byX` X coordinate movement delta. 

* `byY` Y coordinate movement delta.

# class `CZone` 

Represents square zone of 8192x8192 cells. Encapsulates one .KSM (Kal Server Map) file per instance.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CZone`](#classCZone_1a4c64e50a14487f26be0aad93c9e8db19)`(int nZoneX,int nZoneY)` | Declares zone X & Y for further loading from file: n_00X_00Y.ksm. 
`public inline  `[`~CZone`](#classCZone_1a75025deee91dd73ae426684166cb92a1)`()` | Destructor that deallocates .KSM data if exists.
`public bool `[`Load`](#classCZone_1aeb1f1a05c2792822c3e453e2faa58638)`()` | Loads data from .KSM file. Deallocates previous data if any. NOT thread-safe, so do not reload after server start. 
`public bool `[`Check`](#classCZone_1a67fd3fc015cae984f5d934212d62a7e4)`(int nX,int nY,BYTE byType)` | Tests certain cell (X, Y) for zone type. Available tests:

## Members

#### `public  `[`CZone`](#classCZone_1a4c64e50a14487f26be0aad93c9e8db19)`(int nZoneX,int nZoneY)` 

Declares zone X & Y for further loading from file: n_00X_00Y.ksm. 
#### Parameters
* `nZoneX` X zone coordinate (WorldX / 8192). 

* `nZoneY` Y zone coordinate (WorldY / 8192).

#### `public inline  `[`~CZone`](#classCZone_1a75025deee91dd73ae426684166cb92a1)`()` 

Destructor that deallocates .KSM data if exists.

#### `public bool `[`Load`](#classCZone_1aeb1f1a05c2792822c3e453e2faa58638)`()` 

Loads data from .KSM file. Deallocates previous data if any. NOT thread-safe, so do not reload after server start. 
#### Returns
false if file does not exist or file size mismatches, true otherwise

#### `public bool `[`Check`](#classCZone_1a67fd3fc015cae984f5d934212d62a7e4)`(int nX,int nY,BYTE byType)` 

Tests certain cell (X, Y) for zone type. Available tests:

* ZT_MONSTER: area free for monsters for walk and chase;

* ZT_SAFEZONE: area with entry prohibition for monsters;

* ZT_CASTLE: castle siege area;

* ZT_TOWN: city/town area;

* ZT_PKFREE: area with entry prohibition for assasins. 
#### Returns
false if prohibited, true otherwise

# struct `CItemInfo` 

```
struct CItemInfo
  : public CMacro
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public WORD `[`m_wIndex`](#structCItemInfo_1a76934b07053447467ac7cc6d0a293df1) | 
`public BYTE `[`m_byClass`](#structCItemInfo_1a2439bdfe283e25ae066084dee37c9e35) | 
`public BYTE `[`m_bySubClass`](#structCItemInfo_1aa6373a624fecb0957b50ec98450b1a7d) | 
`public BYTE `[`m_byLevel`](#structCItemInfo_1a9daf58f73e2ee03d7f825f44424b2427) | 
`public bool `[`m_bWear`](#structCItemInfo_1a700234e12c866e8471fd576a74314c32) | 
`public BYTE `[`m_byReqClass`](#structCItemInfo_1a6ceef77eff51d0aebb093257a237f0a4) | 
`public BYTE `[`m_byReqLevel`](#structCItemInfo_1a3fb4da114f8d4f563d31b7a016b2cbe0) | 
`public int `[`m_nRange`](#structCItemInfo_1ab2247b3d4b23f521920029ff550d5a57) | 
`public int `[`m_nBuy`](#structCItemInfo_1a19bcf28fb6d3ee7c62ccdd0eae2a4b67) | 
`public int `[`m_nSell`](#structCItemInfo_1a1314a803259248085444fc0beef2d735) | 
`public BYTE `[`m_byEndurance`](#structCItemInfo_1af1a7e5251f8148a42767c3edf8c92218) | 
`public bool `[`m_bPlural`](#structCItemInfo_1a480c1cff45290d84cc8bd62b91eb3f3c) | 
`public bool `[`m_bUse`](#structCItemInfo_1ae54533224232f7ef1ca6daaadb4e902c) | 
`public int `[`m_nCooltime`](#structCItemInfo_1ad36c89d3ea744f4f746e4e8a77836301) | 
`public BYTE `[`m_byEffect`](#structCItemInfo_1aacbba761386ebfd931e34a857dfe4716) | 
`public int `[`m_nRefresh`](#structCItemInfo_1ab32ef75c6bc26ac30ffbc837cd534aed) | 
`public int `[`m_nBuffId`](#structCItemInfo_1afd3262a03d0fa3cc25b343d6f102c448) | 
`public int `[`m_nBuffTime`](#structCItemInfo_1a475df8ea73d83cd8a0bb1373c7da8fe0) | 
`public int `[`m_nBuffValue`](#structCItemInfo_1a55716f963c98983b29f86d15d74f11e9) | 
`public WORD `[`m_wAttackSpeed`](#structCItemInfo_1a09a882345fa8394eb74e810fa1a2465a) | 
`public WORD `[`m_wRange`](#structCItemInfo_1a1b336b764676b28d844de7a41d53110c) | 
`public WORD `[`m_wDefense`](#structCItemInfo_1a29883d0a4939508980ecb89a32cbeb98) | 
`public WORD `[`m_wHit`](#structCItemInfo_1a22b9c583d90fc8a6e95eba4d60a4b3ed) | 
`public WORD `[`m_wDodge`](#structCItemInfo_1a5709beccfc3a9fe9a73c7921ab997a91) | 
`public WORD `[`m_wAbsorb`](#structCItemInfo_1a68b2665eab373021688916a2c2e57ccb) | 
`public WORD `[`m_wResistFire`](#structCItemInfo_1a699b3e66037b53735ca99be91a6bfe77) | 
`public WORD `[`m_wResistIce`](#structCItemInfo_1aa26de24aa9420cd4c46e3a8ca89fe756) | 
`public WORD `[`m_wResistLitning`](#structCItemInfo_1a67551a98cd7ae370c097349cf26bcd6a) | 
`public WORD `[`m_wResistCurse`](#structCItemInfo_1ab683ac93d924c1b0cbc5073c1d3580b2) | 
`public WORD `[`m_wResistPalsy`](#structCItemInfo_1a7c8cc72fca71a28fb52fa34829dac0a3) | 
`public DWORD `[`m_dwHP`](#structCItemInfo_1aabaeaf2061db64a150a05ba9bf44339f) | 
`public DWORD `[`m_dwMP`](#structCItemInfo_1ac53394d540206014ee89d2aa2d0245b3) | 
`public int `[`m_nTeleport`](#structCItemInfo_1aa2502047d88ffbbbfd67cae7cc6d6658) | 
`public WORD `[`m_wMinAttack`](#structCItemInfo_1ab5dc077635bdab3db04a0075477f8237) | 
`public WORD `[`m_wMaxAttack`](#structCItemInfo_1a06c9e0c51e956b5d16b055a683f5058e) | 
`public WORD `[`m_wMinMagic`](#structCItemInfo_1a5ac42935c959abf4e0aa16ce2a45137c) | 
`public WORD `[`m_wMaxMagic`](#structCItemInfo_1a2fc639e34056e5397bec89a2fd309391) | 
`public WORD `[`m_wStr`](#structCItemInfo_1ab3828a32ae0cc4718c965d10e703a852) | 
`public WORD `[`m_wHth`](#structCItemInfo_1aecf4da12e1bcde7a12b3b89bff3f8596) | 
`public WORD `[`m_wInt`](#structCItemInfo_1a1aa7cb7639769f0565f5406d6bdff54d) | 
`public WORD `[`m_wWis`](#structCItemInfo_1a407be745faf5785d3ff968271606796c) | 
`public WORD `[`m_wDex`](#structCItemInfo_1aabd05081ae1ec47d7273f22b4d5a34a0) | 
`public inline  `[`CItemInfo`](#structCItemInfo_1a1c40648b42e421bebf1666b450650f44)`()` | 

## Members

#### `public WORD `[`m_wIndex`](#structCItemInfo_1a76934b07053447467ac7cc6d0a293df1) 

#### `public BYTE `[`m_byClass`](#structCItemInfo_1a2439bdfe283e25ae066084dee37c9e35) 

#### `public BYTE `[`m_bySubClass`](#structCItemInfo_1aa6373a624fecb0957b50ec98450b1a7d) 

#### `public BYTE `[`m_byLevel`](#structCItemInfo_1a9daf58f73e2ee03d7f825f44424b2427) 

#### `public bool `[`m_bWear`](#structCItemInfo_1a700234e12c866e8471fd576a74314c32) 

#### `public BYTE `[`m_byReqClass`](#structCItemInfo_1a6ceef77eff51d0aebb093257a237f0a4) 

#### `public BYTE `[`m_byReqLevel`](#structCItemInfo_1a3fb4da114f8d4f563d31b7a016b2cbe0) 

#### `public int `[`m_nRange`](#structCItemInfo_1ab2247b3d4b23f521920029ff550d5a57) 

#### `public int `[`m_nBuy`](#structCItemInfo_1a19bcf28fb6d3ee7c62ccdd0eae2a4b67) 

#### `public int `[`m_nSell`](#structCItemInfo_1a1314a803259248085444fc0beef2d735) 

#### `public BYTE `[`m_byEndurance`](#structCItemInfo_1af1a7e5251f8148a42767c3edf8c92218) 

#### `public bool `[`m_bPlural`](#structCItemInfo_1a480c1cff45290d84cc8bd62b91eb3f3c) 

#### `public bool `[`m_bUse`](#structCItemInfo_1ae54533224232f7ef1ca6daaadb4e902c) 

#### `public int `[`m_nCooltime`](#structCItemInfo_1ad36c89d3ea744f4f746e4e8a77836301) 

#### `public BYTE `[`m_byEffect`](#structCItemInfo_1aacbba761386ebfd931e34a857dfe4716) 

#### `public int `[`m_nRefresh`](#structCItemInfo_1ab32ef75c6bc26ac30ffbc837cd534aed) 

#### `public int `[`m_nBuffId`](#structCItemInfo_1afd3262a03d0fa3cc25b343d6f102c448) 

#### `public int `[`m_nBuffTime`](#structCItemInfo_1a475df8ea73d83cd8a0bb1373c7da8fe0) 

#### `public int `[`m_nBuffValue`](#structCItemInfo_1a55716f963c98983b29f86d15d74f11e9) 

#### `public WORD `[`m_wAttackSpeed`](#structCItemInfo_1a09a882345fa8394eb74e810fa1a2465a) 

#### `public WORD `[`m_wRange`](#structCItemInfo_1a1b336b764676b28d844de7a41d53110c) 

#### `public WORD `[`m_wDefense`](#structCItemInfo_1a29883d0a4939508980ecb89a32cbeb98) 

#### `public WORD `[`m_wHit`](#structCItemInfo_1a22b9c583d90fc8a6e95eba4d60a4b3ed) 

#### `public WORD `[`m_wDodge`](#structCItemInfo_1a5709beccfc3a9fe9a73c7921ab997a91) 

#### `public WORD `[`m_wAbsorb`](#structCItemInfo_1a68b2665eab373021688916a2c2e57ccb) 

#### `public WORD `[`m_wResistFire`](#structCItemInfo_1a699b3e66037b53735ca99be91a6bfe77) 

#### `public WORD `[`m_wResistIce`](#structCItemInfo_1aa26de24aa9420cd4c46e3a8ca89fe756) 

#### `public WORD `[`m_wResistLitning`](#structCItemInfo_1a67551a98cd7ae370c097349cf26bcd6a) 

#### `public WORD `[`m_wResistCurse`](#structCItemInfo_1ab683ac93d924c1b0cbc5073c1d3580b2) 

#### `public WORD `[`m_wResistPalsy`](#structCItemInfo_1a7c8cc72fca71a28fb52fa34829dac0a3) 

#### `public DWORD `[`m_dwHP`](#structCItemInfo_1aabaeaf2061db64a150a05ba9bf44339f) 

#### `public DWORD `[`m_dwMP`](#structCItemInfo_1ac53394d540206014ee89d2aa2d0245b3) 

#### `public int `[`m_nTeleport`](#structCItemInfo_1aa2502047d88ffbbbfd67cae7cc6d6658) 

#### `public WORD `[`m_wMinAttack`](#structCItemInfo_1ab5dc077635bdab3db04a0075477f8237) 

#### `public WORD `[`m_wMaxAttack`](#structCItemInfo_1a06c9e0c51e956b5d16b055a683f5058e) 

#### `public WORD `[`m_wMinMagic`](#structCItemInfo_1a5ac42935c959abf4e0aa16ce2a45137c) 

#### `public WORD `[`m_wMaxMagic`](#structCItemInfo_1a2fc639e34056e5397bec89a2fd309391) 

#### `public WORD `[`m_wStr`](#structCItemInfo_1ab3828a32ae0cc4718c965d10e703a852) 

#### `public WORD `[`m_wHth`](#structCItemInfo_1aecf4da12e1bcde7a12b3b89bff3f8596) 

#### `public WORD `[`m_wInt`](#structCItemInfo_1a1aa7cb7639769f0565f5406d6bdff54d) 

#### `public WORD `[`m_wWis`](#structCItemInfo_1a407be745faf5785d3ff968271606796c) 

#### `public WORD `[`m_wDex`](#structCItemInfo_1aabd05081ae1ec47d7273f22b4d5a34a0) 

#### `public inline  `[`CItemInfo`](#structCItemInfo_1a1c40648b42e421bebf1666b450650f44)`()` 

# struct `CMacro` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `CMonsterInfo` 

```
struct CMonsterInfo
  : public CMacro
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public WORD `[`m_wIndex`](#structCMonsterInfo_1ac05f39a8c3b2a0cadc15a36d00289232) | 
`public BYTE `[`m_byRace`](#structCMonsterInfo_1aa6a0da27614bb6e12ce24e5b8a267bcc) | 
`public BYTE `[`m_byLevel`](#structCMonsterInfo_1af51dd9f92e3c39cff3d2586f29c3bae5) | 
`public BYTE `[`m_byAI`](#structCMonsterInfo_1abeb38493bf01835786a3526818e3148f) | 
`public WORD `[`m_wRange`](#structCMonsterInfo_1ab6672eaa7c9dcd23d4125412950dfebb) | 
`public WORD `[`m_wCloseSight`](#structCMonsterInfo_1a3ad06f707931eed8844497793e8b581f) | 
`public WORD `[`m_wFarSight`](#structCMonsterInfo_1a92cb55f43d52be5d7b28a202aa69430e) | 
`public __int64 `[`m_n64Exp`](#structCMonsterInfo_1aad4403f33d4255623b03cec89e98194b) | 
`public WORD `[`m_wWalkSpeed`](#structCMonsterInfo_1ad529ddd263cf9e68e5227b7fa50cce25) | 
`public WORD `[`m_wRunSpeed`](#structCMonsterInfo_1ac51bd28674f8c9cae8498e2cc1b9fb7c) | 
`public WORD `[`m_wAttackSpeed`](#structCMonsterInfo_1a2606ae8216541893d3f329e4fffc8cda) | 
`public WORD `[`m_wStr`](#structCMonsterInfo_1a077bcb6158ca1d0a45d930cbccb33a46) | 
`public WORD `[`m_wHth`](#structCMonsterInfo_1a762fb128f9a62ef821f4fb7009e97d3f) | 
`public WORD `[`m_wInt`](#structCMonsterInfo_1a73e33b8accdfbcbe4c795bc630227f93) | 
`public WORD `[`m_wWis`](#structCMonsterInfo_1a064d63f4c02d248c717a121c30ad31d4) | 
`public WORD `[`m_wDex`](#structCMonsterInfo_1ab1807b81fe8094f6865a5d8a77d17d35) | 
`public DWORD `[`m_dwHP`](#structCMonsterInfo_1a69c5f25dd2d7c3f6deb51a699503c04f) | 
`public DWORD `[`m_dwMP`](#structCMonsterInfo_1af7f153f9283f6f054561e72947b37ec5) | 
`public WORD `[`m_wDefense`](#structCMonsterInfo_1a1fd73643476380c69bd6cc9c6ab74812) | 
`public WORD `[`m_wHit`](#structCMonsterInfo_1a530d7d3f47411f6ec37caf0f72f6e7f4) | 
`public WORD `[`m_wDodge`](#structCMonsterInfo_1a6f71e397f1739739ed5e3cbd174f3bd1) | 
`public WORD `[`m_wAbsorb`](#structCMonsterInfo_1a0ae2b56523913590649148f335b7c4d3) | 
`public WORD `[`m_wResistFire`](#structCMonsterInfo_1ab90f43b23fb76bef8cfb07b43173b72f) | 
`public WORD `[`m_wResistIce`](#structCMonsterInfo_1a70f8a1a41f3c4badb17731f476dbb237) | 
`public WORD `[`m_wResistLitning`](#structCMonsterInfo_1a0a2ff1d3742794e0da57f676b25f424b) | 
`public WORD `[`m_wResistCurse`](#structCMonsterInfo_1aad4764813468a16db18c5ab65e659f48) | 
`public WORD `[`m_wResistPalsy`](#structCMonsterInfo_1ac29435267add159dc68881fe385a6f80) | 
`public WORD `[`m_wMinAttack`](#structCMonsterInfo_1ab24c395f81ab71caefff657c8af6d700) | 
`public WORD `[`m_wMaxAttack`](#structCMonsterInfo_1a8591f1a3a2fb809a2e36c10fb14b191a) | 
`public WORD `[`m_wMinMagic`](#structCMonsterInfo_1a039745d705c73743ae62f624bcf7b7b7) | 
`public WORD `[`m_wMaxMagic`](#structCMonsterInfo_1abffd3931f2a166c64302ee5ac2a37c6e) | 
`public WORD `[`m_wSize`](#structCMonsterInfo_1afbe8ef3d7e35dee06c309bee0d1107fa) | 
`public inline  `[`CMonsterInfo`](#structCMonsterInfo_1a8dde7a427a752dd840a9911379d66a51)`()` | 

## Members

#### `public WORD `[`m_wIndex`](#structCMonsterInfo_1ac05f39a8c3b2a0cadc15a36d00289232) 

#### `public BYTE `[`m_byRace`](#structCMonsterInfo_1aa6a0da27614bb6e12ce24e5b8a267bcc) 

#### `public BYTE `[`m_byLevel`](#structCMonsterInfo_1af51dd9f92e3c39cff3d2586f29c3bae5) 

#### `public BYTE `[`m_byAI`](#structCMonsterInfo_1abeb38493bf01835786a3526818e3148f) 

#### `public WORD `[`m_wRange`](#structCMonsterInfo_1ab6672eaa7c9dcd23d4125412950dfebb) 

#### `public WORD `[`m_wCloseSight`](#structCMonsterInfo_1a3ad06f707931eed8844497793e8b581f) 

#### `public WORD `[`m_wFarSight`](#structCMonsterInfo_1a92cb55f43d52be5d7b28a202aa69430e) 

#### `public __int64 `[`m_n64Exp`](#structCMonsterInfo_1aad4403f33d4255623b03cec89e98194b) 

#### `public WORD `[`m_wWalkSpeed`](#structCMonsterInfo_1ad529ddd263cf9e68e5227b7fa50cce25) 

#### `public WORD `[`m_wRunSpeed`](#structCMonsterInfo_1ac51bd28674f8c9cae8498e2cc1b9fb7c) 

#### `public WORD `[`m_wAttackSpeed`](#structCMonsterInfo_1a2606ae8216541893d3f329e4fffc8cda) 

#### `public WORD `[`m_wStr`](#structCMonsterInfo_1a077bcb6158ca1d0a45d930cbccb33a46) 

#### `public WORD `[`m_wHth`](#structCMonsterInfo_1a762fb128f9a62ef821f4fb7009e97d3f) 

#### `public WORD `[`m_wInt`](#structCMonsterInfo_1a73e33b8accdfbcbe4c795bc630227f93) 

#### `public WORD `[`m_wWis`](#structCMonsterInfo_1a064d63f4c02d248c717a121c30ad31d4) 

#### `public WORD `[`m_wDex`](#structCMonsterInfo_1ab1807b81fe8094f6865a5d8a77d17d35) 

#### `public DWORD `[`m_dwHP`](#structCMonsterInfo_1a69c5f25dd2d7c3f6deb51a699503c04f) 

#### `public DWORD `[`m_dwMP`](#structCMonsterInfo_1af7f153f9283f6f054561e72947b37ec5) 

#### `public WORD `[`m_wDefense`](#structCMonsterInfo_1a1fd73643476380c69bd6cc9c6ab74812) 

#### `public WORD `[`m_wHit`](#structCMonsterInfo_1a530d7d3f47411f6ec37caf0f72f6e7f4) 

#### `public WORD `[`m_wDodge`](#structCMonsterInfo_1a6f71e397f1739739ed5e3cbd174f3bd1) 

#### `public WORD `[`m_wAbsorb`](#structCMonsterInfo_1a0ae2b56523913590649148f335b7c4d3) 

#### `public WORD `[`m_wResistFire`](#structCMonsterInfo_1ab90f43b23fb76bef8cfb07b43173b72f) 

#### `public WORD `[`m_wResistIce`](#structCMonsterInfo_1a70f8a1a41f3c4badb17731f476dbb237) 

#### `public WORD `[`m_wResistLitning`](#structCMonsterInfo_1a0a2ff1d3742794e0da57f676b25f424b) 

#### `public WORD `[`m_wResistCurse`](#structCMonsterInfo_1aad4764813468a16db18c5ab65e659f48) 

#### `public WORD `[`m_wResistPalsy`](#structCMonsterInfo_1ac29435267add159dc68881fe385a6f80) 

#### `public WORD `[`m_wMinAttack`](#structCMonsterInfo_1ab24c395f81ab71caefff657c8af6d700) 

#### `public WORD `[`m_wMaxAttack`](#structCMonsterInfo_1a8591f1a3a2fb809a2e36c10fb14b191a) 

#### `public WORD `[`m_wMinMagic`](#structCMonsterInfo_1a039745d705c73743ae62f624bcf7b7b7) 

#### `public WORD `[`m_wMaxMagic`](#structCMonsterInfo_1abffd3931f2a166c64302ee5ac2a37c6e) 

#### `public WORD `[`m_wSize`](#structCMonsterInfo_1afbe8ef3d7e35dee06c309bee0d1107fa) 

#### `public inline  `[`CMonsterInfo`](#structCMonsterInfo_1a8dde7a427a752dd840a9911379d66a51)`()` 

# struct `MapInfo` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public WORD `[`wTileX`](#structMapInfo_1ad09be2746b03c866a544869de5c90248) | 
`public WORD `[`wTileY`](#structMapInfo_1a3a5692bd2b8adfd6c1f0cedf7d78ec1a) | 
`public WORD `[`wOffsetX`](#structMapInfo_1ae77c7f414d52c8a3ee3904002e20727b) | 
`public WORD `[`wOffsetY`](#structMapInfo_1a8713aa23c30689f52612c1ee3cc24a7d) | 
`public WORD `[`wZoneX`](#structMapInfo_1a927975fcd72b751fe6f2e5bfbd2a927e) | 
`public WORD `[`wZoneY`](#structMapInfo_1ad01330bf6cc1f3490d994c7820be838d) | 
`public inline bool `[`equalTile`](#structMapInfo_1af521faa869e28cf4084e13ed0d50478b)`(MapInfo & mapInfo)` | 
`public inline bool `[`equalZone`](#structMapInfo_1ae1149cacce1743d3fe3d8d771588afca)`(MapInfo & mapInfo)` | 

## Members

#### `public WORD `[`wTileX`](#structMapInfo_1ad09be2746b03c866a544869de5c90248) 

#### `public WORD `[`wTileY`](#structMapInfo_1a3a5692bd2b8adfd6c1f0cedf7d78ec1a) 

#### `public WORD `[`wOffsetX`](#structMapInfo_1ae77c7f414d52c8a3ee3904002e20727b) 

#### `public WORD `[`wOffsetY`](#structMapInfo_1a8713aa23c30689f52612c1ee3cc24a7d) 

#### `public WORD `[`wZoneX`](#structMapInfo_1a927975fcd72b751fe6f2e5bfbd2a927e) 

#### `public WORD `[`wZoneY`](#structMapInfo_1ad01330bf6cc1f3490d994c7820be838d) 

#### `public inline bool `[`equalTile`](#structMapInfo_1af521faa869e28cf4084e13ed0d50478b)`(MapInfo & mapInfo)` 

#### `public inline bool `[`equalZone`](#structMapInfo_1ae1149cacce1743d3fe3d8d771588afca)`(MapInfo & mapInfo)` 

Generated by [Moxygen](https://sourcey.com/moxygen)