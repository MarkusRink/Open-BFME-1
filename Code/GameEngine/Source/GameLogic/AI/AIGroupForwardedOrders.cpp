// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the AIGroup orders that walk the member list and forward one
// command to each member's own AICommandInterface.
//
//   ?groupFollowWaypointPathAsTeam@  0x00155A80, 85 bytes
//   ?groupHunt@                      0x00156270, 53 bytes
//   ?groupGuardPosition@             0x00156840, 77 bytes
//   ?groupBfmeCommand44@             0x001569C0, 85 bytes
//
// One walk, four commands. The member list is the node pointer at AIGroup+0x04,
// walked as an STLport sentinel ring -- next is begin, the node itself is end --
// with the member object at node+0x08, its AI at object+0x204 and the command
// interface at AI+0x20. Four files each drew that chain of four structs out in
// full; it is one chain and it is drawn once here.
//
// Around the walk they differ only in the guard: groupHunt has none,
// groupGuardPosition and groupBfmeCommand44 drop out on a null argument, and
// groupFollowWaypointPathAsTeam asks isReady() first and then runs a group prep
// before the loop.
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

struct Coord3D;
class Waypoint;
class PolygonTrigger;

enum GuardMode { BFME_GUARD_MODE_NORMAL };
enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
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

class BfmeGroupMember
{
public:
	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;					// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	BfmeGroupMember *m_bfmeValue;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	// Nested for groupGuardPosition alone -- see the note at the top of this file.
	enum GuardMode { BFME_AIGROUP_GUARD_MODE };
	enum CommandSourceType { BFME_AIGROUP_COMMAND_SOURCE };

	void groupFollowWaypointPathAsTeam(const Waypoint *way, ::CommandSourceType cmdSource);
	void groupHunt(::CommandSourceType cmdSource);
	void groupGuardPosition(const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource);
	void groupBfmeCommand44(const PolygonTrigger *poly, int value,
			::CommandSourceType cmdSource, const Coord3D *pos);

	char isReady();								// ILT 0x000104B0
	void prepFollow(::CommandSourceType cmdSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;			// +0x04
};

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
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

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
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

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
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

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
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

		if (ai)
			ai->m_bfmeCommands.aiBfmeCommand44(poly, value, cmdSource, pos);
	}
}
