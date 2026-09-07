// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_RECRUIT_UNITS_FROM_TEAM at retail RVA 0x00303AC0.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Team;
class ObjectTypes;

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

class BfmeTeamRecruitHelper
{
public:
	int recruit(ObjectTypes *, Int, Team *);
};

extern BfmeScriptEngineVtbl_44_50 *TheScriptEngine;
extern void j_0000b866();
extern void j_0000534e();
extern void j_0003d415();
extern void j_0003eafe();

class BfmeObjectTypes
{
	unsigned char m_storage[0x14];

public:
	BfmeObjectTypes()
	{
		typedef void (BfmeObjectTypes::*Function)();
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0003d415;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)();
	}

	~BfmeObjectTypes()
	{
		typedef void (BfmeObjectTypes::*Function)();
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0003eafe;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)();
	}

	void addObjectType(const AsciiString &name)
	{
		typedef void (BfmeObjectTypes::*Function)(const AsciiString &);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0000534e;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)(name);
	}
};

static __forceinline void bfmeRecruitUnits(Team *team,
	ObjectTypes *objectTypes, Int count, Team *sourceTeam)
{
	typedef int (BfmeTeamRecruitHelper::*Function)(ObjectTypes *, Int, Team *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000b866;
	(reinterpret_cast<BfmeTeamRecruitHelper *>(team)->*fn.member)(
		objectTypes, count, sourceTeam);
}

class ScriptActions
{
protected:
	void doTeamRecruitUnitsFromTeam(const AsciiString &, Int,
		const AsciiString &, const AsciiString &);
};

// ?doTeamRecruitUnitsFromTeam@ScriptActions@@IAEXABVAsciiString@@H00@Z
void ScriptActions::doTeamRecruitUnitsFromTeam(const AsciiString &teamName,
	Int count, const AsciiString &objectTypeName,
	const AsciiString &sourceTeamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team) {
		return;
	}

	Team *sourceTeam = TheScriptEngine->getTeamNamed(sourceTeamName, false);
	if (!sourceTeam) {
		return;
	}

	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectTypeName);
	if (objectTypes) {
		bfmeRecruitUnits(team, objectTypes, count, sourceTeam);
	} else {
		BfmeObjectTypes singleObjectType;
		singleObjectType.addObjectType(objectTypeName);
		bfmeRecruitUnits(team, (ObjectTypes *)&singleObjectType, count,
			sourceTeam);
	}
}
