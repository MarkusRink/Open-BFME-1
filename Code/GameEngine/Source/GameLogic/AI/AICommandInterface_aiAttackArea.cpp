// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiAttackArea, retail 0x00153C10, 203 bytes.
//
// One of the reference's inline command builders, out of line here: build the
// parameter block, put the polygon in the polygon slot, then
// aiDoCommand at vtable slot 0 -- the frame
// AICommandInterface_aiAttackObject.cpp measured.
//
// AICMD_ATTACK_AREA is 0x23. BFME's command list is the reference's with the
// two ALLOW_SURRENDER prisoner commands dropped and one position command added
// after DOCK, which is what carries ATTACK_OBJECT 0x0B, ATTACKMOVE 0x0F and
// HUNT 0x12 through unchanged while GET_HEALED lands at 0x15, ENTER at 0x17 and
// EVACUATE at 0x1B -- and with two commands inserted later (0x19 and 0x20) the
// list realigns with the reference exactly from GUARD_AREA 0x21 on.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;

	void zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

enum AICommandType { AICMD_ATTACK_AREA = 0x23 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

enum DamageType
{
	DAMAGE_EXPLOSION = 0,
	DAMAGE_PARTICLE_BEAM = 0x16,
	DAMAGE_UNRESISTABLE = 0x0B
};

enum DeathType { DEATH_NORMAL = 0, DEATH_BFME_DEFAULT = 0x0F };
typedef Int ObjectID;
const ObjectID INVALID_ID = 0;

class Snapshot
{
protected:
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

struct DamageInfoInputTail
{
	Int m_z0;
	Int m_z1;
	Int m_z2;
	Int m_z3;
	Int m_z4;
	Int m_z5;
	Real m_shockWaveTaperOff;

	void initialize()
	{
		m_z0 = 0;
		m_z1 = 0;
		m_z2 = 0;
		m_z3 = 0;
		m_z4 = 0;
		m_z5 = 0;
		m_shockWaveTaperOff = 1.0f;
	}
};

class DamageInfoInput : public Snapshot
{
public:
	__forceinline DamageInfoInput()
	{
		m_sourceID = INVALID_ID;
		m_unk08 = 0;
		m_amount = 0;
		m_fxOverride = 0;
		m_kill = false;
		m_shock0 = 0;
		m_shock1 = 0;
		m_shock2 = 0;
		m_damageType = DAMAGE_PARTICLE_BEAM;
		m_deathType = DEATH_BFME_DEFAULT;
		m_unk59 = true;
		m_tail.initialize();
	}

	ObjectID m_sourceID;
	unsigned short m_unk08;
	unsigned short m_pad0A;
	DamageType m_damageType;
	DeathType m_deathType;
	Real m_amount;
	Int m_fxOverride;
	Bool m_kill;
	Bool m_unk59;
	unsigned short m_pad1E;
	Int m_shock0;
	Int m_shock1;
	Int m_shock2;
	DamageInfoInputTail m_tail;
};

class DamageInfoOutput : public Snapshot
{
public:
	__forceinline DamageInfoOutput()
	{
		m_actualDamageDealt = 0;
		m_actualDamageClipped = 0;
		m_noEffect = false;
	}

	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo : public Snapshot
{
public:
	__forceinline DamageInfo() {}

	DamageInfoInput in;
	DamageInfoOutput out;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	AICommandType						m_cmd;			// +0x00
	CommandSourceType				m_cmdSource;		// +0x04
	Coord3D									m_pos;			// +0x08
	Object									*m_obj;			// +0x14
	Object									*m_otherObj;		// +0x18
	const Team							*m_team;		// +0x1C
	_STL::vector<Coord3D>		m_coords;			// +0x20
	const Waypoint					*m_waypoint;		// +0x2C
	const PolygonTrigger		*m_polygon;			// +0x30
	Int											m_intValue;		// +0x34
	DamageInfo							m_damage;		// +0x38
	const CommandButton			*m_commandButton;	// +0x94
	Path										*m_path;		// +0x98

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);	// ILT 0x00030EA4
};

// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z
AICommandParms::AICommandParms(AICommandType cmd, CommandSourceType cmdSource)
	: m_cmd(cmd),
	  m_cmdSource(cmdSource),
	  m_obj(0),
	  m_otherObj(0),
	  m_team(0),
	  m_waypoint(0),
	  m_polygon(0),
	  m_intValue(0),
	  m_commandButton(0),
	  m_path(0)
{
	m_pos.zero();
	m_coords.clear();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType cmdSource);
};

void AICommandInterface::aiAttackArea( const PolygonTrigger *areaToGuard, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_ATTACK_AREA, cmdSource);
	parms.m_polygon = areaToGuard;
	aiDoCommand(&parms);
}
