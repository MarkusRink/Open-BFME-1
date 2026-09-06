// ?onEnter@AIMoveToState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIMoveToState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp

typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x, y, z;
};

struct Object;

struct AIUpdateInterface
{
	unsigned char m_unknown[0x164];

	int getIgnoredObstacleID();
};

struct Overridable
{
	void *m_vftable;
	Overridable *m_nextOverride;
};

struct ThingTemplate
{
	void *m_vftable;
	Overridable *m_override;
	unsigned char m_unknown[0xc0];
	unsigned int m_flags;
};

typedef ThingTemplate *(__fastcall *GetFinalOverride)(Overridable *);
extern void j_000022bb(void);

struct GeometryInfo
{
	Real getMaxHeightAbovePosition() const;
};

struct Object
{
	void *m_vftable;
	ThingTemplate *m_template;
	unsigned char m_unknown_008[0x30];
	Coord3D m_position;
	unsigned char m_unknown_044[0x30];
	unsigned int m_id;
	unsigned char m_unknown_078[0x18c];
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAI()
	{
		return m_ai;
	}

	unsigned int getID() const
	{
		return m_id;
	}

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_override)
			tmpl = (const ThingTemplate *)((GetFinalOverride)j_000022bb)(tmpl->m_override);
		return tmpl;
	}

	Coord3D *getPosition() const
	{
		return (Coord3D *)((unsigned char *)this + 0x38);
	}

	GeometryInfo *getGeometryInfo()
	{
		return (GeometryInfo *)((unsigned char *)this + 0xac);
	}
};

struct StateMachine
{
	unsigned char m_unknown_000[0x10];
	Object *m_owner;
	unsigned char m_unknown_014[0x10];
	Coord3D m_goalPosition;

	Object *getGoalObject();

	Coord3D *getGoalPosition()
	{
		return &m_goalPosition;
	}
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
extern void j_0000e570(void);
extern void j_0001a36b(void);

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
typedef int (__fastcall *GetIgnoredObstacleID)(AIUpdateInterface *);

class AIInternalMoveToState
{
protected:
	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	Coord3D m_goalPosition;
	unsigned char m_stateFields30[0x1c];
	unsigned char m_adjustDestinations;

public:
	virtual StateReturnType onEnter();
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIMoveToState::onEnter()
{
	AIUpdateInterface *ai;

	if (g_012F0239 && g_012ED4FC)
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 38");

	m_adjustDestinations = 1;
	ai = m_machine->m_owner->getAI();
	if (((GetGoalObject)j_0000e570)(m_machine))
	{
		if (ai && ((GetGoalObject)j_0000e570)(m_machine)->getID() ==
			((GetIgnoredObstacleID)j_0001a36b)(ai))
		{
			if (g_012F0239 && g_012ED4FC)
				((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
					"CritterDesync: setAdjustDestination(FALSE) 57");
			m_adjustDestinations = 0;
		}
	}

	StateMachine *machine;
	if (((GetGoalObject)j_0000e570)(m_machine))
	{
		m_goalPosition = *(((GetGoalObject)j_0000e570)(m_machine)->getPosition());
		machine = m_machine;
		ThingTemplate **templateSlot =
			(ThingTemplate **)((unsigned char *)machine->m_owner + 4);
		const ThingTemplate *ownerTemplate = *templateSlot;
		if (ownerTemplate && ownerTemplate->m_override)
			ownerTemplate = (const ThingTemplate *)
				((GetFinalOverride)j_000022bb)(ownerTemplate->m_override);
		if (ownerTemplate->m_flags & 0x02000000)
		{
			Real halfHeight = ((GetGoalObject)j_0000e570)(m_machine)->getGeometryInfo()->getMaxHeightAbovePosition() * 0.5f;
			m_goalPosition.z += halfHeight;
			if (((GetGoalObject)j_0000e570)(m_machine)->getPosition()->z < m_goalPosition.z)
				m_goalPosition.z += halfHeight;
		}
	}
	else
	{
		machine = m_machine;
		m_goalPosition = *machine->getGoalPosition();
	}

	return AIInternalMoveToState::onEnter();
}
