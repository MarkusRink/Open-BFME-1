// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// readable body of ?evaluatePlayerHasComparisonPercentPower@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerDestroyedNOrMoreBuildings@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerCompareLightPoints@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerHasNOrFewerFactionBuildings@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerHasKilledKindOfUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// Every ScriptConditions condition that resolves a player parameter to a mask
// of players and then asks each of them one question:
//
//   0x003230C0  evaluatePlayerHasComparisonPercentPower    power supply ratio
//   0x003232D0  evaluatePlayerDestroyedNOrMoreBuildings    (never finished)
//   0x00323D50  evaluatePlayerCompareLightPoints           light points
//   0x00328590  evaluatePlayerHasNOrFewerFactionBuildings  faction buildings
//   0x003297F0  evaluatePlayerHasKilledKindOfUnits         kills of a KindOf
//
// All five open the same way -- a mask out of the resolver at 0x0034DB40, then
// PlayerList::getEachPlayerFromMask consuming it one player at a time -- and
// differ only in what they read off each player and how they compare it.
//
// They sat in five files, and the shared pair of callees appeared in them
// under four different names: the resolver as both unidentified_0034DB40 on
// ScriptEngine and bfmeNext1087 on a "BfmeP1087", the iterator as both
// getEachPlayerFromMask on PlayerList and bfmeLook1087 on a "BfmeD1087". The
// two Bfme classes were not other objects: g_bfmeP1087 is TheScriptEngine
// (0x00EF076C) and g_bfmeD1087 is ThePlayerList (0x00EED748), the same two
// globals under placeholder names. Named once, the family is visible.
//
// The Player they iterate had drifted the same way -- empty in two files, a
// "BfmeR1087" with a float at +0xA4 in a third, a 0x348 prefix before the
// kills in a fourth. One layout states all of it: the power supply at +0xA4
// and the kill counters at +0x348.
//
// unidentified_0034DB40 keeps its address-derived name: it forwards to
// TheScriptEngine's virtual at +0x4C and no identity has been proven for it.
// The same is true of the light-point reader, which is still reached through
// the thunk at 0x00047D34 rather than by name.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef unsigned short PlayerMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(void) {}
	BitFlags(BogusInitType, int idx) { m_bits._Unchecked_set((size_t)idx); }
	BitFlags(BogusInitType, int idx1, int idx2)
	{
		m_bits._Unchecked_set(idx1);
		m_bits._Unchecked_set(idx2);
	}

	void clear(void) { m_bits.reset(); }
	void set(int idx) { m_bits._Unchecked_set((size_t)idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	int m_int;						// this+0x08
	float m_real;
	AsciiString m_string;					// this+0x10
};

// The power supply ratio at retail 0x000C7DE0; still an address-derived name.
class Gen_000C7DE0
{
public:
	float bfmeRatio(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class PlayerKills
{
public:
	int getKillsOfKindOf(KindOfMaskType setMask, KindOfMaskType clearMask);	// retail 0x00036D72
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);	// retail 0x0001FF1E

	unsigned char m_beforeEnergy[0xA4];
	Gen_000C7DE0 m_energy;					// this+0xA4
	unsigned char m_beforeKills[0x348 - 0xA4 - sizeof(Gen_000C7DE0)];
	PlayerKills m_kills;					// this+0x348
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);	// retail 0x000DF4A0 via ILT 0x0002EE60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *playerParm);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern const KindOfMaskType KINDOFMASK_NONE;
extern void j_00047d34();

// The per-player light-point reader is only known as the thunk at 0x00047D34,
// so it is called through the thunk's address rather than by name.
class PlayerLightPoints
{
};

static __forceinline int getPlayerLightPoints(Player *player)
{
	typedef int (PlayerLightPoints::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00047d34;
	return (reinterpret_cast<PlayerLightPoints *>(player)->*fn.member)();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluatePlayerHasComparisonPercentPower(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerDestroyedNOrMoreBuildings(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerCompareLightPoints(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerHasNOrFewerFactionBuildings(Parameter *, Parameter *);
	Bool evaluatePlayerHasKilledKindOfUnits(Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerHasComparisonPercentPower@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasComparisonPercentPower(
	Parameter *playerParm, Parameter *cmpParm, Parameter *pctParm)
{
	float testRatio = pctParm->getInt() * 0.01f;

	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		float ratio = player->m_energy.bfmeRatio();

		switch (cmpParm->getInt()) {
		case 0:
			if (ratio < testRatio)
				return true;
			break;
		case 1:
			if (ratio <= testRatio)
				return true;
			break;
		case 2:
			if (ratio == testRatio)
				return true;
			break;
		case 3:
			if (ratio >= testRatio)
				return true;
			break;
		case 4:
			if (ratio > testRatio)
				return true;
			break;
		case 5:
			if (ratio != testRatio)
				return true;
			break;
		}
	}
	return false;
}

// ?evaluatePlayerDestroyedNOrMoreBuildings@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerDestroyedNOrMoreBuildings(
	Parameter *playerParm, Parameter *, Parameter *opponentParm)
{
	PlayerMaskType playerMask = TheScriptEngine->unidentified_0034DB40(playerParm);
	Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
	PlayerMaskType opponentMask = TheScriptEngine->unidentified_0034DB40(opponentParm);
	Player *opponent = ThePlayerList->getEachPlayerFromMask(opponentMask);
	if (!player || !opponent) {
		return false;
	}

	return false;
}

// ?evaluatePlayerCompareLightPoints@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerCompareLightPoints(
	Parameter *playerParm, Parameter *comparisonParm, Parameter *lightPointsParm)
{
	int lightPoints = 0;
	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	while (mask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			lightPoints += getPlayerLightPoints(player);
	}

	Bool comparison = false;
	switch (comparisonParm->getInt())
	{
	case 0:
		comparison = lightPoints < lightPointsParm->getInt();
		break;
	case 1:
		comparison = lightPoints <= lightPointsParm->getInt();
		break;
	case 2:
		comparison = lightPoints == lightPointsParm->getInt();
		break;
	case 3:
		comparison = lightPoints >= lightPointsParm->getInt();
		break;
	case 4:
		comparison = lightPoints > lightPointsParm->getInt();
		break;
	case 5:
		comparison = lightPoints != lightPointsParm->getInt();
		break;
	}
	return comparison;
}

// ?evaluatePlayerHasNOrFewerFactionBuildings@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluatePlayerHasNOrFewerFactionBuildings(
	Parameter *buildingCountParm, Parameter *playerParm)
{
	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	KindOfMaskType setMask(KindOfMaskType::kInit, 37, 7);
	int count = 0;
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			count += player->countObjects(setMask, KINDOFMASK_NONE);
		}
	}
	int limit = buildingCountParm->getInt();
	Bool result = limit >= count;
	return result;
}

// ?evaluatePlayerHasKilledKindOfUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasKilledKindOfUnits(
	Parameter *pPlayerParm, Parameter *pCountParm, Parameter *pKindOfParm)
{
	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
	if (thePlayer) {
		PlayerKills *kills = &thePlayer->m_kills;
		if (kills) {
			KindOfMaskType setMask;
			setMask.set(pKindOfParm->getInt());
			KindOfMaskType clearMask;
			clearMask.clear();
			int value = kills->getKillsOfKindOf(setMask, clearMask);
			return value >= pCountParm->getInt();
		}
	}

	return false;
}
