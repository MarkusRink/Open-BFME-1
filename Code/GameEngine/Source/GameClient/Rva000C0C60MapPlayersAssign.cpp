// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Retail 0x000C0C60 assigns the eight 20-byte player records embedded at
// MapMetaData +0x54.  The surrounding MapMetaData copy/assignment bodies prove
// the count, stride, and member location; the last twelve bytes are the
// String-keyed STLport set whose assignment is reached through ILT 0x0001D10B.

#include <stl/_config.h>
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <set>

typedef unsigned char Rva000C0C60Bool;

struct Rva000C0C60PlayerRecord
{
	Rva000C0C60Bool m_human;
	Rva000C0C60Bool m_computer;
	Rva000C0C60Bool m_loadAIScripts;
	int m_forcePlayerTeam;
	std::set<AsciiString> m_factionSet;
};

class Rva000C0C60MapPlayers
{
public:
	Rva000C0C60MapPlayers &operator=(const Rva000C0C60MapPlayers &other);

private:
	Rva000C0C60PlayerRecord m_items[8];
};

Rva000C0C60MapPlayers &Rva000C0C60MapPlayers::operator=(
	const Rva000C0C60MapPlayers &other)
{
	for (int i = 0; i < 8; ++i)
	{
		m_items[i] = other.m_items[i];
	}
	return *this;
}
