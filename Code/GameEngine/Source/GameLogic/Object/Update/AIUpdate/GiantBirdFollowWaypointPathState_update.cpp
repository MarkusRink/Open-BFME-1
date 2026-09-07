// cl: /DNDEBUG /MD
//
// GiantBirdFollowWaypointPathState::update, retail RVA 0x002BF250.
// The state vtable at 0x010C79E0 stores thunk 0x000178D7 in slot 6, and that
// thunk jumps to this body.  The state routes its current goal, snaps the
// owner to the goal when the flight distance or pending waypoint requires it,
// then lets the shared waypoint helper decide whether movement continues.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

extern float BfmeZeroRange;

class Rva002BCB60Owner
{
public:
	void route(void *mode, Coord3D *position, int source);

	char m_gap00[0x46c];
	unsigned char m_pending46c;
	char m_gap46d[3];
	float m_height470;
	char m_gap474[4];
	int m_goalMode478;
	Coord3D m_goalPosition47c;
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
};

class Object
{
public:
	char m_gap00[0x38];
	Coord3D m_position;
	char m_gap44[0x1c0];
	Rva002BCB60Owner *m_ai;
	char m_gap208[0x13c];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	char m_gap00[0x10];
	Object *m_owner;
};

class GiantBirdFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter() = 0;
	virtual void onExit(int status) = 0;
	virtual StateReturnType update();

	char m_gap04[0x18];
	StateMachine *m_machine;

	bool updateWaypointGoal();
};

#pragma comment(linker, "/alternatename:?updateWaypointGoal@GiantBirdFollowWaypointPathState@@QAE_NXZ=?j_00031b47@@YAXXZ")

StateReturnType GiantBirdFollowWaypointPathState::update()
{
	Object *object = m_machine->m_owner;
	if ((object->m_flags344 & 1) != 0)
		return STATE_FAILURE;

	Rva002BCB60Owner *ai = object->m_ai;
	if (ai == 0)
		return STATE_FAILURE;

	ai->route((void *)ai->m_goalMode478, &ai->m_goalPosition47c, 0);
	float height = ai->m_height470;
	Coord3D goal = ai->m_goalPosition47c;
	float dx = object->m_position.x - goal.x;
	float dy = object->m_position.y - goal.y;
	float dz = object->m_position.z - goal.z;
	unsigned char farFromGoal = (unsigned char)(dx * dx + dy * dy + dz * dz < height * height);
	int pending = ai->m_pending46c;

	if (pending != BfmeZeroRange || farFromGoal)
	{
		((Thing *)object)->setPosition(&goal);
		if (!updateWaypointGoal())
			return STATE_SUCCESS;
		if (*(unsigned char *)((char *)ai + 0x424) == 0)
			return STATE_FAILURE;
	}

	return STATE_CONTINUE;
}
