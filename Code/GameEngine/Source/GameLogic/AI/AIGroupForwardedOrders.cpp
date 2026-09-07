// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the AIGroup orders that walk the member list and forward one
// command to each member's own AICommandInterface.
//
//   ?groupTightenToPosition@         0x00155720, 295 bytes
//   ?groupFollowWaypointPathAsTeam@  0x00155A80,  85 bytes
//   ?groupHunt@                      0x00156270,  53 bytes
//   ?groupGuardPosition@             0x00156840,  77 bytes
//   ?groupBfmeCommand44@             0x001569C0,  85 bytes
//   ?groupStealthIdle@               0x00156B10, 173 bytes
//
// One walk, six commands. The member list is the node pointer at AIGroup+0x04,
// walked as an STLport sentinel ring -- next is begin, the node itself is end --
// with the member object at node+0x08, its AI at object+0x204 and the command
// interface at AI+0x20. Four files each drew that chain of four structs out in
// full; it is one chain and it is drawn once here.
//
// Around the walk they differ in the guard and in what they do with the member:
// groupHunt has none, groupGuardPosition and groupBfmeCommand44 drop out on a
// null argument, groupFollowWaypointPathAsTeam asks isReady() first and runs a
// group prep, groupStealthIdle skips any member without a StealthUpdate module,
// and groupTightenToPosition does not forward from the walk at all -- it uses the
// walk only to fill a heap SimpleObjectIterator with each member's squared
// distance to the target, sorts NEAR_TO_FAR, and forwards from THAT, which is
// what the extra 200 bytes buy. (It never deletes the iterator.)
//
// The member class had two names and one layout. Four of the six called it
// BfmeGroupMember and described it as `char m_bfmeHead[0x204]` with the AI
// pointer behind it; groupStealthIdle and groupTightenToPosition called it Object
// and named fields inside that head -- a vptr at +0x00, the template at +0x04,
// the position at +0x38, the disabled mask at +0x1A4 -- all of which the opaque
// head simply swallowed. One class, named Object, below.
//
// groupGuardPosition is the one that could not simply share an enum with its
// three neighbours, and this is the reason the file has two of each. Its
// decorated name is
//   ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
// -- the `@1@` says BOTH enums are nested inside AIGroup -- while groupHunt is
//   ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
// with the same-named enum at file scope, and the callees on the far side of
// every one of these calls take the file-scope spelling too. So AIGroup carries
// its own nested GuardMode and CommandSourceType for the one method whose
// mangled name demands them, the other three qualify their parameter as
// `::CommandSourceType`, and groupGuardPosition casts across at the call. Two
// types with one name is not a mistake here; it is what the retail symbols say.
//
// this is spilled to the frame and reloaded after every call in
// groupGuardPosition, and the end of the list is re-read from it each trip,
// because a guard order can change the membership underneath the walk.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Waypoint;
class PolygonTrigger;

enum GuardMode { BFME_GUARD_MODE_NORMAL };

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum IterOrderType { ITER_FASTEST = 0, ITER_SORTED_NEAR_TO_FAR = 1 };
enum KindOfType { KINDOF_IMMOBILE = 2 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	// ILT 0x000022BB

	Overridable *m_nextOverride;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];				// +0xC8
};

class StealthUpdate
{
public:
	void update002AD250();					// ILT 0x000272AF -> 0x002AD250; RVA-derived
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, float numeric);
	void sort(IterOrderType order);

private:
	char m_bfmePad[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);			// ILT 0x00024D70
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
	void aiGuardPosition(const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource);			// ILT 0x0000A033
	void aiBfmeCommand44(const PolygonTrigger *poly, int value,
			CommandSourceType cmdSource, const Coord3D *pos);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;			// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

	bool isKindOf(KindOfType t) const
	{
		return getTemplate()->isKindOf(t);
	}

	float getPosX(void) const { return m_position.x; }
	float getPosY(void) const { return m_position.y; }
	BfmeGroupAI *getAI(void) { return m_ai; }
	unsigned char getDisabledMask(void) const { return m_disabledMask; }

	StealthUpdate *findUpdateModule(NameKeyType key);	// ILT 0x0002AE23

	virtual ~Object();
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;					// +0x38
	unsigned char m_unreconstructed_44[0x1A4 - 0x44];
	unsigned char m_disabledMask;				// +0x1A4
	unsigned char m_unreconstructed_1A5[0x204 - 0x1A5];
	BfmeGroupAI *m_ai;					// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;					// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	// Nested for groupGuardPosition alone -- see the note at the top of this file.
	enum GuardMode { BFME_AIGROUP_GUARD_MODE };
	enum CommandSourceType { BFME_AIGROUP_COMMAND_SOURCE };

	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
			::CommandSourceType cmdSource);
	void groupFollowWaypointPathAsTeam(const Waypoint *way, ::CommandSourceType cmdSource);
	void groupHunt(::CommandSourceType cmdSource);
	void groupGuardPosition(const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource);
	void groupBfmeCommand44(const PolygonTrigger *poly, int value,
			::CommandSourceType cmdSource, const Coord3D *pos);
	void groupStealthIdle();

	char isReady();								// ILT 0x000104B0
	void prepFollow(::CommandSourceType cmdSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;			// +0x04
};

// ?groupTightenToPosition@AIGroup@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
// The one that does not forward from the walk. Identity is the matched
// aiTightenToPosition callee (ILT 0x000438C9 -> 0x001527C0); the addWaypoint arm
// is aiFollowPathAppend (ILT 0x0000BAC8 -> 0x00153480).
void AIGroup::groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
		::CommandSourceType cmdSource)
{
	SimpleObjectIterator *iter = new SimpleObjectIterator;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		Coord3D unitPos;
		unitPos.x = obj->getPosX();
		unitPos.y = obj->getPosY();

		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getAI() == 0)
			continue;

		float dx = unitPos.x - pos->x;
		float dy = unitPos.y - pos->y;
		iter->insert(obj, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_NEAR_TO_FAR);

	for (Object *theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		BfmeGroupAI *ai = theUnit->getAI();
		if (!addWaypoint)
			ai->m_bfmeCommands.aiTightenToPosition(pos, cmdSource);
		else
			ai->m_bfmeCommands.aiFollowPathAppend(pos, cmdSource);
	}
}

// ?groupFollowWaypointPathAsTeam@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z
// The only one of the four with anything before the walk: a Bool gate at
// ILT 0x000104B0 and a group prep at ILT 0x0002E636 -> 0x0015AB50.
void AIGroup::groupFollowWaypointPathAsTeam(const Waypoint *way, ::CommandSourceType cmdSource)
{
	if (!isReady())
		return;

	prepFollow(cmdSource, 0);

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiFollowWaypointPathAsTeam(way, cmdSource);
	}
}

// ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
// The bare walk, and at 53 bytes the price of the walk itself. Identity is the
// matched aiHunt callee, ILT 0x0001C882 -> 0x000D88D0.
void AIGroup::groupHunt(::CommandSourceType cmdSource)
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiHunt(cmdSource);
	}
}

// ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
void AIGroup::groupGuardPosition(const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource)
{
	if (!pos)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiGuardPosition(pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource);
	}
}

// ?groupBfmeCommand44@AIGroup@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@PBUCoord3D@@@Z
// The callee is the matched 0x44 command builder at 0x001549A0, which
// AICommandInterfaceGuardCommands.cpp reads as a guard-area order carrying an
// extra position.
void AIGroup::groupBfmeCommand44(const PolygonTrigger *poly, int value,
		::CommandSourceType cmdSource, const Coord3D *pos)
{
	if (!poly)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiBfmeCommand44(poly, value, cmdSource, pos);
	}
}

// ?groupStealthIdle@AIGroup@@QAEXXZ
// Descriptive name: identity is the group walk plus the "StealthUpdate" string.
// It is not Zero Hour's groupIdle, which takes a CommandSourceType.
void AIGroup::groupStealthIdle()
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		if (!obj)
			continue;

		BfmeGroupAI *ai = obj->m_ai;
		static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
		StealthUpdate *stealth = obj->findUpdateModule(key_StealthUpdate);
		if (!stealth)
			continue;

		if (ai)
			ai->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		stealth->update002AD250();
	}
}
