// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "../../../../reference/shims/stringinline/StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	WideChar name[13];
	char userName[2];
	char hostName[2];
	union
	{
		struct
		{
			WideChar gameName[17];
			Int chatType;
			WideChar message[101];
		} Chat;
		UnsignedByte m_bfmeRest[0x1BA];
	};
};
#pragma pack(pop)

class BfmeM1079
{
public:
	char bfmeChk1079(void);
};

class LANPlayer
{
public:
	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	BfmeNetAddress m_address;
};

class GameSlot
{
public:
	Bool isHuman(void) const;

	UnsignedByte m_bfmeBeforeAddress[0x30];
	BfmeNetAddress m_address;
	UnsignedByte m_bfmeAfterAddress[0x0c];
};

class LANGameSlot : public GameSlot
{
public:
	UnsignedByte m_bfmeBeforeLastHeard[0x20];
	UnsignedInt m_lastHeard;
};

class GameInfo
{
protected:
	UnsignedByte m_bfmeBody[0x58];
};

class LANGameInfo : public GameInfo
{
public:
	LANGameSlot m_LANSlot[8];

	BfmeNetAddress *getIP(Int player)
	{
		return &m_LANSlot[player].m_address;
	}

	LANGameSlot *getLANSlot(Int player)
	{
		return &m_LANSlot[player];
	}
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot0a(void) = 0;
	virtual void _bfme_slot0b(void) = 0;
	virtual void _bfme_slot0c(void) = 0;
	virtual void _bfme_slot0d(void) = 0;
	virtual void _bfme_slot0e(void) = 0;
	virtual void _bfme_slot0f(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot1a(void) = 0;
	virtual void _bfme_slot1b(void) = 0;
	virtual void _bfme_slot1c(void) = 0;
	virtual void _bfme_slot1d(void) = 0;
	virtual void _bfme_slot1e(void) = 0;
	virtual void _bfme_slot1f(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, Int chatType) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual LANGameInfo *LookupGame(UnicodeString gameName) = 0;
	virtual void _bfme_slot2a(void) = 0;
	virtual void _bfme_slot2b(void) = 0;
	virtual void _bfme_slot2c(void) = 0;
	virtual void _bfme_slot2d(void) = 0;
	virtual void _bfme_slot2e(void) = 0;
	virtual void _bfme_slot2f(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;

protected:
	void handleChat(LANMessage *msg, UnsignedInt senderIP);

	UnsignedByte m_bfmeBeforeLobby[0x3d - 4];
	Bool m_inLobby;
	LANGameInfo *m_currentGame;
};

// ?handleChat@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleChat(LANMessage *msg, UnsignedInt senderIP)
{
	if (m_inLobby)
	{
		LANPlayer *player;
		if ((player = LookupPlayer((BfmeNetAddress *)senderIP)) != 0)
		{
			OnChat(UnicodeString(player->m_name), &player->m_address,
				UnicodeString(msg->Chat.message), msg->Chat.chatType);
			player->m_lastHeard = timeGetTime();
		}
	}
	else
	{
		if (LookupGame(UnicodeString((WideChar *)((UnsignedByte *)msg + 0x22))) != m_currentGame)
			return;

		int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slotAddress = m_currentGame->getIP(player);
			if (m_currentGame &&
				slotAddress->m_ip == ((BfmeNetAddress *)senderIP)->m_ip &&
				slotAddress->m_port == ((BfmeNetAddress *)senderIP)->m_port)
			{
				UnsignedInt now = timeGetTime();
				LANGameInfo *game = m_currentGame;
				if (((BfmeM1079 *)&game->m_LANSlot[player])->bfmeChk1079())
					game->m_LANSlot[player].m_lastHeard = now;

				LANMessage *chat = msg;
				OnChat(UnicodeString(chat->name),
					m_currentGame->getIP(player),
					UnicodeString(chat->Chat.message), chat->Chat.chatType);
				break;
			}
		}
	}
}
