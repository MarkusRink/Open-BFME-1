// ?evaluateUnitCanPathIntoPlayersNearestBase@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "Common/GameType.h"

#define __KINDOF_H_
#include "Common/BitFlags.h"

enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_PRELOAD = 119,
	KINDOF_COUNT = 192
};

typedef BitFlags<KINDOF_COUNT> KindOfMaskType;

extern KindOfMaskType KINDOFMASK_NONE;

#define MAKE_KINDOF_MASK(k) KindOfMaskType(KindOfMaskType::kInit, (k))

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

class Player;

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) {}
	virtual ~PartitionFilter(void) {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType& mustBeSet,
		const KindOfMaskType& mustBeClear);

	virtual Bool allow(Object *object);

private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float maxDistance,
		int distanceCalculation, PartitionFilter *filters);
};

class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *object, const Coord3D *from,
		const Coord3D *to, ObjectID blocker);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return *(Pathfinder **)((char *)this + 0x0c);
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(Parameter *) = 0;
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern AI *TheAI;

class ScriptConditions
{
protected:
	Bool evaluateUnitCanPathIntoPlayersNearestBase(Parameter *, Parameter *);
};

// ?evaluateUnitCanPathIntoPlayersNearestBase@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateUnitCanPathIntoPlayersNearestBase(
	Parameter *pUnitParm, Parameter *pPlayerParm)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theUnit) {
		return false;
	}

	PlayerMaskType playerMask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(pPlayerParm->getString(), 0);
	Player *player = ThePlayerList->getPlayerFromMask(playerMask);
	if (player) {
		return false;
	}

	PartitionFilterPlayer playerFilter(0, true);
	KindOfMaskType mustBeSet = MAKE_KINDOF_MASK(KINDOF_PRELOAD);
	PartitionFilterAcceptByKindOf kindFilter(mustBeSet, KINDOFMASK_NONE);

	Object *base = ThePartitionManager->getClosestObject(
		theUnit->getPosition(), 1000.0f, FROM_CENTER_2D,
		kindFilter.link(&playerFilter));
	if (!base) {
		return false;
	}

	return TheAI->pathfinder()->slowDoesPathExist(
		theUnit, theUnit->getPosition(), base->getPosition(), (ObjectID)0);
}
