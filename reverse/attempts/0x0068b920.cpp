// ?handleInActive@LANAPI@@IAEXPAULANMessage@@I@Z
// partial score=0.65 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

// BFME LANAPI::handleInActive, RVA 0x0068B920, complete 323 bytes.
//
// The retail handler is the inactive-player path from the Zero Hour
// LANAPIhandlers.cpp family.  BFME keeps the same control flow, but the
// message name, LANGameInfo progress byte, LANAPI fields, address-pair slot,
// and two LANAPI virtual slots are all taken from matched BFME siblings below.
// The existing matched comparator at RVA 0x000970A0 is already
// Gen_000970a0::bfmeEquals; this TU reuses that landed identity through its
// ILT and does not add an unknown ABI probe.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;
#define FALSE 0

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(void);
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString
{
public:
	AsciiString(void) { m_data = 0; }
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class UnicodeString
{
public:
	UnicodeString(void) { m_data = 0; }
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
			*(const StringBase<WideChar> *)&other);
	}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=(const WideChar *text);

private:
	void releaseBuffer();
	WideChar *m_data;
};

// The assignment is the already-matched UnicodeString forwarder at ILT
// 0x0002C56B.  Its body is independently named in reverse/functions.csv.

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
	UnsignedShort m_padding;
};

#pragma pack(push, 1)
struct LANMessage
{
	Int m_type;
	WideChar name[13];
};
#pragma pack(pop)

class GameSlot
{
public:
	void unAccept();

	private:
	unsigned char m_beforeAddress[0x30];

	public:
	BfmeNetAddress m_address;
};

class LANGameInfo
{
public:
	Int getSlotNum(UnicodeString userName);
	GameSlot *getSlot(Int player);
	Bool isGameInProgress(void) const { return m_inProgress != 0; }

	private:
	unsigned char m_beforeProgress[0x0d];

	public:
	Bool m_inProgress;
	unsigned char m_beforeSlots[0x58 - 0x0e];
};

// The matched 0x0068D4A0 body is still carried by its existing neutral
// BfmeThing935B spelling.  Its +0x0C flag and +0x58 nested host-slot test are
// exactly the predicate called here through ILT 0x000329B1; this TU does not
// promote that spelling to LANGameInfo::amIHost.
class BfmeThing935B
{
public:
	char bfmeGo935B();
};

class BfmeHostGame : public LANGameInfo
{
public:
	Bool amIHost(void) { return ((BfmeThing935B *)this)->bfmeGo935B() != 0; }
};

// The matched address-pair comparator at 0x00684B60 is reused under its
// already-landed identity.  Both address views are the same eight-byte BFME
// transport record.
class BfmeKeyXW
{
public:
	Int bfmeDiffersXW(const BfmeKeyXW *other) const;
};

// The complete two-field comparator at body RVA 0x000970A0 is already matched
// as Gen_000970a0::bfmeEquals.  Its existing ILT 0x0002A72A is the local
// address check's exact route; this use does not add a second identity.
class Gen_000970a0
{
public:
	Int bfmeEquals(const Gen_000970a0 *other) const;
};

#pragma comment(linker, "/alternatename:??4UnicodeString@@QAEAAV0@PBG@Z=?j_0002c56b@@YAXXZ")

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
	virtual void RequestGameOptions(AsciiString options, Bool isPublic,
		UnsignedInt ip = 0) = 0; // vtable +0x50; LANAPI.h's defaulted third arg
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
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
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *getLocalAddress(void) = 0; // vtable +0xdc

protected:
	void handleInActive(LANMessage *msg, UnsignedInt senderIP);

	unsigned char m_beforeGameStart[0x1c - 4];
	UnsignedInt m_gameStartTime; // +0x1c
	unsigned char m_beforeLobby[0x3d - 0x20];
	Bool m_inLobby; // +0x3d
	unsigned char m_beforeCurrent[2];
	LANGameInfo *m_currentGame; // +0x40
};

extern LANAPI *TheLAN;
extern AsciiString GenerateGameOptionsString(void);
extern void processInactiveLanMessages(void);

#pragma comment(linker, "/alternatename:?GenerateGameOptionsString@@YA?AVAsciiString@@XZ=?j_00027485@@YAXXZ")

// ?handleInActive@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleInActive(LANMessage *msg, UnsignedInt senderIP)
{
	if (m_inLobby == FALSE && m_currentGame != 0 &&
		m_currentGame->isGameInProgress() == FALSE)
	{
		if (((BfmeHostGame *)m_currentGame)->amIHost() == FALSE)
			return;

		UnicodeString playerName;
		playerName = msg->name;

		Int slotNum = m_currentGame->getSlotNum(playerName);
		if (slotNum < 0)
			return;

		GameSlot *slot = m_currentGame->getSlot(slotNum);
		if (slot == 0)
			return;

		const BfmeNetAddress *sender = (const BfmeNetAddress *)senderIP;
		if (((const BfmeKeyXW *)sender)->bfmeDiffersXW(
			(const BfmeKeyXW *)&slot->m_address))
			return;

		if (((const Gen_000970a0 *)sender)->bfmeEquals(
			(const Gen_000970a0 *)TheLAN->getLocalAddress()))
			return;

		if (m_gameStartTime != 0)
			return;

		slot->unAccept();
		AsciiString options = GenerateGameOptionsString();
		RequestGameOptions(options, FALSE);
		processInactiveLanMessages();
	}
}
