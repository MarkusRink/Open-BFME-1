// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
// partial score=0.76 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Clean C++ recovery of TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE.
// Retail RVA 0x002FE110, 273 bytes.  The executeAction arm names this body;
// BFME's implementation is a compact nearest-object rewrite of the ZH action.

#include "StringInline.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;

class ObjectTypes;
class Player;
class Team;
class ThingTemplate;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// Team lookup passes this one-word view by value.  The constructor is the
// retail AsciiString copy helper, rather than a ZH reference argument.
class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// Slot 17 is getTeamNamed and slot 20 is getObjectTypes in the BFME vtable.
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class CommandButton
{
public:
	Bool isReady(const Object *sourceObject) const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

// The two fields used by the retail override chain are at +4 in the
// Overridable subobject.  Keep this view separate from the incomplete object
// layout supplied by ObjectDlinkPmf.h.
class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// The BFME target calls the already-recovered anonymous member-action helper
// after placing the button in EDI and the current team member in ESI.  Its
// generated declaration has no C++ parameters, so retain that symbol while
// supplying the one stack template argument expected by the retail body.
extern void d_002fdac0();

static __forceinline void bfmeApplyNearestAction(
	const ThingTemplate *thingTemplate)
{
	typedef void (*Function)(const ThingTemplate *);
	union { void (*raw)(void); Function typed; } fn;
	fn.raw = d_002fdac0;
	fn.typed(thingTemplate);
}

class ScriptActions;

extern BfmeScriptEngineVtbl_44_50 *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern ControlBar *TheControlBar;
extern void j_0002990b();
extern void j_000414d9();
extern void j_000022bb();

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	class BfmeTeamEstimatePositionCall
	{
	public:
		Coord3D *getEstimateTeamPosition(Coord3D *) const;
	};
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002990b;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		fn.member)(position);
}

static __forceinline Object *bfmeFindClosestObject(ScriptActions *actions,
	const Coord3D *position, ObjectTypes *objectTypes, Player *player)
{
	class BfmeFindClosestObjectCall
	{
	public:
		Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
	};
	typedef Object *(BfmeFindClosestObjectCall::*Function)(
		const Coord3D *, ObjectTypes *, Player *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000414d9;
	return (reinterpret_cast<BfmeFindClosestObjectCall *>(actions)->*
		fn.member)(position, objectTypes, player);
}

static __forceinline const ThingTemplate *bfmeGetFinalOverride(
	const ThingTemplate *thingTemplate)
{
	typedef const BfmeOverridable *(BfmeOverridable::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000022bb;
	return (const ThingTemplate *)
		(reinterpret_cast<const BfmeOverridable *>(thingTemplate)->*
		fn.member)();
}

class ScriptActions
{
protected:
	void doTeamUseCommandButtonOnNearestObjectType(
		const AsciiString &teamName, const AsciiString &commandName,
		const AsciiString &objectTypeName);

	Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
};

// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doTeamUseCommandButtonOnNearestObjectType(
	const AsciiString &teamName, const AsciiString &commandName,
	const AsciiString &objectTypeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	register const CommandButton *commandButton =
		TheControlBar->findCommandButton(commandName);
	if (!commandButton)
		return;

	const ThingTemplate *thingTemplate = 0;
	if (ObjectTypes *objectTypes =
		TheScriptEngine->getObjectTypes(objectTypeName))
	{
		Coord3D teamPosition;
		Object *nearest = bfmeFindClosestObject(this,
			bfmeGetEstimateTeamPosition(team, &teamPosition), objectTypes, 0);
		if (!nearest)
			return;

		thingTemplate = *(const ThingTemplate **)((char *)nearest + 4);
		if (thingTemplate &&
			*(const void **)((const char *)thingTemplate + 4))
		{
			thingTemplate = bfmeGetFinalOverride(thingTemplate);
		}
	}
	else
	{
		thingTemplate = TheThingFactory->findTemplate(objectTypeName);
	}

	if (!thingTemplate)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *member = iter.cur();
		if (commandButton->isReady(member))
			bfmeApplyNearestAction(thingTemplate);
	}
}
