// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// BFME LANAPI::handleLobbyAnnounce, RVA 0x0068B1E0, complete 331-byte body.
// LANAPI::update dispatches MSG_LOBBY_ANNOUNCE (2) via table 0x00687A28
// to arm 0x0068721B. Its call at 0x00687223 follows ILT 0x00046001 here,
// passing a pointer to the sender address pair, not the Zero Hour bare IP.
// The final RET 8 at 0x0068B328 ends before INT3 padding at 0x0068B32B.
// Layout and virtual slots follow the independently matched RequestSetName
// reconstruction. LANPlayer is 0x1C bytes; its address pair is at +0x14,
// with a 16-bit port at +0x18 and an eight-byte whole-struct copy.
// Original semantic body: LANAPIhandlers.cpp. Existing StringBase adapters
// reproduce BFME's string calls without changing shared headers.
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
struct LANMessage
{
    unsigned int messageType; // +0x00
    wchar_t name[13];          // +0x04
    char userName[2];          // +0x1E
    char hostName[2];          // +0x20
    unsigned char rest[0x1dc - 0x22];
};
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
class LANPlayer
{
public:
	LANPlayer()
	{
		m_lastHeard = 0;
		m_next = 0;
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}

	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};
class LANAPI
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
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
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void RequestSetName(UnicodeString newName);			// slot 24
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void OnNameChange(BfmeNetAddress *from, UnicodeString newName) = 0;	// slot 41, vtable+0xA4
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;			// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;		// slot 54, vtable+0xD8
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;			// slot 55, vtable+0xDC

protected:
	void handleLobbyAnnounce(LANMessage *msg, BfmeNetAddress *sender);
	void removePlayer(LANPlayer *player);					// ILT thunk 0x0003BDF4
	void addPlayer(LANPlayer *player);					// ILT thunk 0x00045363

};
typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];
typedef char BfmePlayerSizeCheck[sizeof(LANPlayer) == 0x1C ? 1 : -1];
typedef char BfmeMessageSizeCheck[sizeof(LANMessage) == 0x1DC ? 1 : -1];

void LANAPI::handleLobbyAnnounce(LANMessage *msg, BfmeNetAddress *sender)
{
    LANPlayer *player = LookupPlayer(sender);
    if (!player) {
        player = new LANPlayer;
        player->m_address = *sender;
    } else {
        removePlayer(player);
    }
    player->m_name.set(UnicodeString(msg->name));
    player->m_host.translate(AsciiString(msg->hostName));
    player->m_login.translate(AsciiString(msg->userName));
    player->m_lastHeard = timeGetTime();
    addPlayer(player);
    OnNameChange(&player->m_address, player->m_name);
}
