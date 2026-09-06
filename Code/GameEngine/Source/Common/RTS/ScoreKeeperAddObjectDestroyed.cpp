// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME ScoreKeeper::addObjectDestroyed(const Object *) at 0x000EA910.
// BFME skips objects under construction and uses the global unit-score filter
// for units instead of the Zero Hour infantry and vehicle KindOf checks.

#include <map>

typedef int Int;
typedef int Bool;

template <int Bits>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &mustBeSet, const BitFlags<Bits> &mustBeClear) const;
};

typedef BitFlags<116> KindOfMaskType;

extern const KindOfMaskType KINDOFMASK_NONE;
extern KindOfMaskType scoringBuildingMask;
extern KindOfMaskType scoringBuildingDestroyMask;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const
	{
		return m_kindOf.testSetAndClear(mustBeSet, mustBeClear);
	}

private:
	unsigned char m_pad[0xC0];
	KindOfMaskType m_kindOf;
};

class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }

private:
	unsigned char m_pad[0x24];
	Int m_playerIndex;
};

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	Player *getControllingPlayer(void) const;
	unsigned int getStatusBits(void) const { return m_status; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad[0x90];
	unsigned int m_status;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class GameLogic
{
public:
	bool isScoringEnabled(void) const { return m_isScoringEnabled != 0; }

private:
	unsigned char m_pad[0x90];
	unsigned char m_isScoringEnabled;
};

class BfmeRvaA760Object;

class BfmeRvaA760ProbeInterface
{
public:
	bool accepts(BfmeRvaA760Object *obj, Int arg);
};

class GlobalData
{
public:
	unsigned char m_pad[0x121C];
	BfmeRvaA760ProbeInterface m_unitScoreFilter;
};

extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

class ScoreKeeper
{
public:
	void addObjectDestroyed(const Object *o);

private:
	void *m_vtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[32];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[32];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
	Int m_heroesVetted;
	Int m_unitsVetted;
	Int m_powerPoints;
	Int m_pad128;
	Int m_regionCommandPoints;
	Int m_regionResources;
	Int m_regionPowerPoints;
	Int m_currentScore;
	unsigned int m_frameOverride;
	Int m_myPlayerIdx;
	ObjectCountMap m_objectsBuilt;
	ObjectCountMap m_objectsDestroyed[32];
};

void ScoreKeeper::addObjectDestroyed(const Object *o)
{
	ScoreKeeper *keeper = this;
	const Object *object = o;
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (object->getStatusBits() & 0x800)
		return;

	Player *player = object->getControllingPlayer();
	Int playerIdx = player->getPlayerIndex();
	Bool addToCount = false;
	if (object->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		++keeper->m_totalBuildingsDestroyed[playerIdx];
		addToCount = true;
	}
	else if (object->getTemplate()->isKindOfMulti(scoringBuildingDestroyMask, KINDOFMASK_NONE))
	{
		++keeper->m_totalBuildingsDestroyed[playerIdx];
		addToCount = true;
	}
	else if (TheWritableGlobalData->m_unitScoreFilter.accepts((BfmeRvaA760Object *)object, 0))
	{
		++keeper->m_totalUnitsDestroyed[playerIdx];
		addToCount = true;
	}
	if (addToCount)
	{
		Int existingCount = 0;
		ObjectCountMapIt it = keeper->m_objectsDestroyed[playerIdx].find(object->getTemplate());
		if (it != keeper->m_objectsDestroyed[playerIdx].end())
			existingCount = it->second;
		keeper->m_objectsDestroyed[playerIdx][object->getTemplate()] = existingCount + 1;
	}
}
