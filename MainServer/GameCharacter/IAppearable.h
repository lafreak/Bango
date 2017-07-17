#ifndef _IAPPEARABLE_
#define _IAPPEARABLE_

class IAppearable
{
public:
	virtual Packet GenerateCreatePacket(bool bHero = false);
	virtual Packet GeneratePetPacket();
	virtual Packet GenerateDeletePacket();
	virtual Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ = 0);
};

#endif
