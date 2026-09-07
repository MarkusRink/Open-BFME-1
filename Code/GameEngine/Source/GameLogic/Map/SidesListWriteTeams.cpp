// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/DataChunk.h"
#include "Common/Dict.h"
#include "Common/NameKeyGenerator.h"

extern const StaticNameKey TheKey_teamLibraryMapName;

struct BfmeTeamInfoSlot
{
	short next;
	short previous;
	short reserved;
	short free;
	Int generation;
	Dict dict;
};

class SidesList
{
public:
	void writeTeams(DataChunkOutput &chunkWriter);

private:
	char m_prefix[0x63c];
	BfmeTeamInfoSlot *m_teams;
};

__forceinline Dict::DataType bfmeTeamType(BfmeTeamInfoSlot *teams, Int index, NameKeyType key)
{
	return teams[index].dict.getType(key);
}

void SidesList::writeTeams(DataChunkOutput &chunkWriter)
{
	chunkWriter.openDataChunk("Teams", 1);
	int count = 0;
	register Int index = m_teams[0].next;
	register BfmeTeamInfoSlot *teams = m_teams;
	while (index != 0)
	{
		if (bfmeTeamType(teams, index, TheKey_teamLibraryMapName.key()) != Dict::DICT_ASCIISTRING)
			++count;
		teams = m_teams;
		index = teams[index].next;
	}
	chunkWriter.writeInt(count);
	teams = m_teams;
	index = teams[0].next;
	while (index != 0)
	{
		BfmeTeamInfoSlot &team = teams[index];
		if (team.dict.getType(TheKey_teamLibraryMapName.key()) != Dict::DICT_ASCIISTRING)
			chunkWriter.writeDict(team.dict);
		teams = m_teams;
		index = teams[index].next;
	}
	chunkWriter.closeDataChunk();
}
