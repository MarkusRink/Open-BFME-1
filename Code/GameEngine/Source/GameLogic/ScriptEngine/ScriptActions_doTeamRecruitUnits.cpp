// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_RECRUIT_UNITS at retail RVA 0x002F5BE0.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Team;
class ObjectTypes;
class ThingTemplate;

class BfmeScriptEngineVtbl_44_50
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeAIData
{
public:
	unsigned char m_unreconstructed_000[0x5c];
	Real m_maxRecruitDistance;
};

class BfmeAI
{
public:
	unsigned char m_unreconstructed_000[0x14];
	BfmeAIData *m_aiData;
};

class BfmeTeamHasAnyObjects
{
public:
	Bool hasAnyObjects(Bool includeDead);
};

class BfmeTeamRecruitHelper
{
public:
	void recruit(const ThingTemplate *, ObjectTypes *, Int, Real);
};

extern BfmeScriptEngineVtbl_44_50 *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern BfmeAI *TheAI;
extern void j_0001478b();
extern void j_000439d2();

static __forceinline Bool bfmeHasAnyObjects(Team *team)
{
	typedef Bool (BfmeTeamHasAnyObjects::*Function)(Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001478b;
	return (reinterpret_cast<BfmeTeamHasAnyObjects *>(team)->*fn.member)(false);
}

static __forceinline void bfmeRecruitUnits(Team *team,
	const ThingTemplate *thingTemplate, ObjectTypes *objectTypes,
	Int count, Real maxDistance)
{
	typedef void (BfmeTeamRecruitHelper::*Function)(const ThingTemplate *,
		ObjectTypes *, Int, Real);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000439d2;
	(reinterpret_cast<BfmeTeamRecruitHelper *>(team)->*fn.member)(
		thingTemplate, objectTypes, count, maxDistance);
}

class ScriptActions
{
protected:
	void doTeamRecruitUnits(const AsciiString &, Int, const AsciiString &);
};

// ?doTeamRecruitUnits@ScriptActions@@IAEXABVAsciiString@@H0@Z
void ScriptActions::doTeamRecruitUnits(const AsciiString &teamName,
	Int count, const AsciiString &objectTypeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team) {
		return;
	}

	const ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(objectTypeName);
	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectTypeName);
	if (bfmeHasAnyObjects(team)) {
		bfmeRecruitUnits(team, thingTemplate, objectTypes, count,
			TheAI->m_aiData->m_maxRecruitDistance);
	} else {
		bfmeRecruitUnits(team, thingTemplate, objectTypes, count,
			1000000.0f);
	}
}
