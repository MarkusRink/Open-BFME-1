// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: ScriptConditions::evaluatePlayerCompareLightPoints at retail RVA 0x00323D50.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned short UnsignedShort;

class Parameter
{
public:
	int getInt() const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	int m_int;
};

class ScriptEngine
{
public:
	UnsignedShort unidentified_0034DB40(Parameter *playerParm);
};

class Player;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

class PlayerLightPoints
{
};

class Player
{
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern void j_00047d34();

static __forceinline int getPlayerLightPoints(Player *player)
{
	typedef int (PlayerLightPoints::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00047d34;
	return (reinterpret_cast<PlayerLightPoints *>(player)->*fn.member)();
}

class ScriptConditions
{
protected:
	Bool evaluatePlayerCompareLightPoints(Parameter *playerParm,
		Parameter *comparisonParm, Parameter *lightPointsParm);
};

// ?evaluatePlayerCompareLightPoints@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerCompareLightPoints(
	Parameter *playerParm, Parameter *comparisonParm, Parameter *lightPointsParm)
{
	int lightPoints = 0;
	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParm);
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
