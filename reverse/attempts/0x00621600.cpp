// ?GameInfoToAsciiString@@YA?AVAsciiString@@PBVGameInfo@@_N@Z
// partial score=0.95 date=2026-09-07
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include <string>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#ifndef FALSE
#define FALSE false
#define TRUE true
#endif

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		unsigned short m_length;
		unsigned short m_pad;
		T m_data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

	void concat(const T *source, int length);
	void concat(T source);
	void set(const T *source, int length);

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	static AsciiString TheEmptyString;
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString format, ...);
	const char *str() const
	{
		return m_data ? (const char *)m_data->m_data : "";
	}
	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}
	void concat(const char *source, int length)
	{
		StringBase<char>::concat(source, length);
	}
	void concat(char source)
	{
		StringBase<char>::concat(&source, 1);
	}
	void concat(const AsciiString &source)
	{
		StringBase<char>::concat(source.str(), source.getLength());
	}
	void set(const char *source, int length)
	{
		StringBase<char>::set(source, length);
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	const unsigned short *str(void) const
	{
		return m_data ? (const unsigned short *)((const char *)m_data + 8) : (const unsigned short *)L"";
	}
};

class GameSlot
{
public:
	virtual void _bfme_slot0(void) = 0;
	UnicodeString getName(void) const;
	Int getState(void) const { return m_state; }
	Bool isAccepted(void) const { return m_isAccepted != 0; }
	Bool hasMap(void) const { return m_hasMap != 0; }
	Int getColor(void) const { return m_color; }
	Int getPlayerTemplate(void) const { return m_playerTemplate; }
	Int getStartPos(void) const { return m_startPos; }
	Int getTeamNumber(void) const { return m_teamNumber; }
	UnsignedInt getIP(void) const { return m_ip; }
	UnsignedShort getPort(void) const { return m_port; }
	UnsignedInt getNATBehavior(void) const { return m_nat; }

	private:
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	unsigned char m_pad0b;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	void *m_name;
	void *m_ipString;
	UnsignedInt m_ip;
	UnsignedShort m_port;
	UnsignedShort m_portPad;
	UnsignedInt m_nat;
};

class GameInfo
{
public:
	AsciiString getMap(void) const;
	const GameSlot *getConstSlot(Int slotNum) const
	{
		if (slotNum < 0 || slotNum >= 8)
			return 0;
		return m_slots[slotNum];
	}

	Int getMapContentsMask(void) const { return m_mapMask; }
	UnsignedInt getMapCRC(void) const { return m_mapCRC; }
	UnsignedInt getMapSize(void) const { return m_mapSize; }
	Int getSeed(void) const { return m_seed; }

	void *m_vptr;
	Int m_preorderMask;
	Int m_crcInterval;
	Bool m_inGame;
	Bool m_inProgress;
	Bool m_surrendered;
	unsigned char m_pad0f;
	Int m_gameID;
	GameSlot *m_slots[8];
	UnsignedInt m_localIP;
	UnsignedInt m_bfme38;
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
	Int m_mapMask;
	Int m_seed;
};

extern AsciiString formatMapPath(const AsciiString &mapName, Bool useDisplayName);
extern std::string WideCharStringToMultiByte(const unsigned short *orig);
extern const char g_Rva0107301CEmptyString[];

static const char slotListID = 'S';

AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots)
{
	if (!game)
		return AsciiString::TheEmptyString;

	AsciiString newMapName = formatMapPath(game->getMap(), FALSE);
	AsciiString optionsString;
	optionsString.format("M=%3.3x%s;MC=%X;MS=%d;SD=%d;",
		game->getMapContentsMask(), newMapName.str(), game->getMapCRC(), game->getMapSize(), game->getSeed());

	optionsString.concat(slotListID);
	optionsString.concat('=');
	for (Int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = game->getConstSlot(i);
		AsciiString str;
		if (slot && slot->getState() == 5)
		{
			AsciiString name = WideCharStringToMultiByte(slot->getName().str()).c_str();
			str.format("H%s,%X,%d,%c%c,%d,%d,%d,%d,%d:",
				includeSlots ? name.str() : g_Rva0107301CEmptyString,
				slot->getIP(), slot->getPort(),
				slot->isAccepted() ? 'T' : 'F', slot->hasMap() ? 'T' : 'F',
				slot->getColor(), slot->getPlayerTemplate(), slot->getStartPos(),
				slot->getTeamNumber(), slot->getNATBehavior());
		}
		else if (slot && (slot->getState() == 2 || slot->getState() == 3 || slot->getState() == 4))
		{
			char c;
			if (slot->getState() == 2)
				c = 'E';
			else if (slot->getState() == 3)
				c = 'M';
			else
				c = 'H';
			str.format("C%c,%d,%d,%d,%d:", c, slot->getColor(), slot->getPlayerTemplate(),
				slot->getStartPos(), slot->getTeamNumber());
		}
		else if (slot && slot->getState() == 0)
		{
			str.set("O:", 2);
		}
		else if (slot && slot->getState() == 1)
		{
			str.set("X:", 2);
		}
		else
		{
			str.set("X:", 2);
		}
		optionsString.concat(str);
	}
	optionsString.concat(';');
	return optionsString;
}
