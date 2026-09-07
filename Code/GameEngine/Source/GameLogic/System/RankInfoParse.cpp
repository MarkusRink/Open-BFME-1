// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"

#include "Common/INI.h"
#include "Common/INIException.h"
#include "Common/Science.h"
#include "Common/UnicodeString.h"
#include "Common/STLTypedefs.h"

class Player;

extern "C" void free(void *);

class RankInfo : public Overridable
{
public:
	enum RankInfoMagicEnum { RankInfo_GLUE_NOT_IMPLEMENTED = 0 };

	inline void *operator new(size_t size, RankInfoMagicEnum)
	{
		return ::operator new(size);
	}

	inline void operator delete(void *pointer, RankInfoMagicEnum)
	{
		free(pointer);
	}

	RankInfo() throw();
	RankInfo &operator=(const RankInfo &);

	UnicodeString m_rankName;
	Int m_skillPointsNeeded;
	Int m_bfme_14;
	Int m_bfme_18;
	Int m_bfme_1c;
	Int m_bfme_20;
	Int m_bfme_24;
	Int m_sciencePurchasePointsGranted;
	ScienceVec m_sciencesGranted;
};

class RankInfoStore : public SubsystemInterface
{
public:
	virtual ~RankInfoStore();

	void init();
	void reset();
	void update() { }

	Int getRankLevelCount() const;
	const RankInfo* getRankInfo(Int level) const;
	static void friend_parseRankDefinition(INI* ini);

private:
	typedef std::vector<RankInfo*> RankInfoVec;
	RankInfoVec m_rankInfos;
};

extern RankInfoStore* TheRankInfoStore;

void RankInfoStore::friend_parseRankDefinition( INI* ini )
{
	if (TheRankInfoStore)
	{
		Int rank = INI::scanInt(ini->getNextToken());

		static const FieldParse myFieldParse[] =
		{
			{ "RankName", INI::parseAndTranslateLabel, NULL, offsetof( RankInfo, m_rankName ) },
			{ "SkillPointsNeeded", INI::parseInt, NULL, offsetof( RankInfo, m_skillPointsNeeded ) },
			{ "SciencesGranted", INI::parseScienceVector, NULL, offsetof( RankInfo, m_sciencesGranted ) },
			{ "SciencePurchasePointsGranted", INI::parseUnsignedInt, NULL, offsetof( RankInfo, m_sciencePurchasePointsGranted ) },
			{ 0, 0, 0, 0 }
		};

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		{
			if (rank < 1 || rank > TheRankInfoStore->m_rankInfos.size())
			{
				throw INIException( 3, "Rank not found in map.ini" );
			}

			RankInfo* info = TheRankInfoStore->m_rankInfos[rank-1];
			if (!info)
			{
				throw INIException( 3, "Rank not found in map.ini" );
			}

			RankInfo* newInfo = newInstance(RankInfo);
			info = (RankInfo*)(info->friend_getFinalOverride());

			*newInfo = *info;
			info->setNextOverride(newInfo);
			newInfo->markAsOverride();

			ini->initFromINI(newInfo, myFieldParse);
		}
		else
		{
			if (rank != TheRankInfoStore->m_rankInfos.size() + 1)
			{
				throw INIException( 3, "Ranks must increase monotonically" );
			}
			RankInfo* info = newInstance(RankInfo);
			ini->initFromINI(info, myFieldParse);
			TheRankInfoStore->m_rankInfos.push_back(info);
		}
	}
}
