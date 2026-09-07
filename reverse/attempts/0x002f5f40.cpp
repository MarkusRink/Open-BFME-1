// ?doTeamMoveToNearestObjectOfType@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.93 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// TEAM_MOVE_TO_NEAREST_OBJECT_OF_TYPE, retail RVA 0x002F5F40 (280 bytes).
// executeAction arm 393 calls ILT 0x0002D0EC, whose body is this action.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Player;
class ThingTemplate;
class ObjectTypes;
class AIGroup;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
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

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) {}
	virtual ~PartitionFilter(void) {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: m_thingTemplate(thingTemplate), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class Rva0020AA00Registry
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *) const;
	void getTeamAsAIGroup(AIGroup *group);
};

class AI
{
public:
	AIGroup *createGroup(void);
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class Rva0015A190Packet
{
public:
	void *m_first;
	unsigned char m_flag;
	union
	{
		void *m_objA;
		Real m_scratchZ;
	};
};

class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, Int command);
};

class Object
{
public:
	virtual void slot0(void);

	unsigned char m_unreconstructed[0x34];
	Coord3D m_position;

	const Coord3D *getPosition(void) const { return &m_position; }
};

extern ScriptEngine *TheScriptEngine;
extern Rva0020AA00Registry *Rva0020AA00TheRegistry;
extern PartitionManager *ThePartitionManager;
extern AI *TheAI;

class ScriptActions;
extern void j_000414d9(void);

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
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_000414d9;
	return (reinterpret_cast<BfmeFindClosestObjectCall *>(actions)->*
		fn.member)(position, objectTypes, player);
}

class ScriptActions
{
protected:
	void doTeamMoveToNearestObjectOfType(const AsciiString &teamName,
		const AsciiString &objectType);
};

// ?doTeamMoveToNearestObjectOfType@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamMoveToNearestObjectOfType(
	const AsciiString &teamName, const AsciiString &objectType)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	ObjectTypes *objectTypes;
	Coord3D teamPosition;
	team->getEstimateTeamPosition_000EDCD0(&teamPosition);

	objectTypes = TheScriptEngine->getObjectTypes(objectType);
	Object *object = 0;
	if (objectTypes)
	{
		object = bfmeFindClosestObject(this, &teamPosition, objectTypes, 0);
	}
	else
	{
		const ThingTemplate *thingTemplate =
			Rva0020AA00TheRegistry->findTemplate(objectType);
		if (!thingTemplate)
			return;

		PartitionFilterThing thingFilter(thingTemplate, true);
		object = ThePartitionManager->getClosestObject(&teamPosition,
			1000000.0f, 0, &thingFilter);
	}

	if (!object)
		return;

	{
		AIGroup *group = TheAI->createGroup();
		if (!group)
			return;

		team->getTeamAsAIGroup(group);
		Rva0015A190Packet packet;
		packet.m_first = (void *)object->getPosition();
		packet.m_flag = 0;
		packet.m_objA = 0;
		((Rva0015A190Owner *)group)->applyPacket(&packet, 1);
	}
}
