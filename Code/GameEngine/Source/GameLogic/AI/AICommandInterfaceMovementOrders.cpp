// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface orders that send a unit somewhere or take
// it out of where it is.
//
//   ?aiMoveToPosition@         0x000D86C0, AICMD 0x00
//   ?aiIdle@                   0x000D87E0, AICMD 0x05
//   ?aiHunt@                   0x000D88D0, AICMD 0x12
//   ?aiEnter@                  0x000D89C0, AICMD 0x17
//   ?aiEvacuate@               0x000D8AC0, AICMD 0x1B
//   ?aiAttackMoveToPosition@   0x00153AF0, AICMD 0x0F
//
// The first four are one contiguous run in the retail image; the fifth is the
// same builder emitted elsewhere. All five are compiled with exceptions on and
// without /DWIN32, which is what separates this TU from the /DWIN32 command
// bodies that define _STLP_NO_EXCEPTIONS -- the same command family, two
// compilation modes, not mergeable across.
//
// The five carried four different accounts of AICommandParms between them and
// no two agreed on how much of it to name. aiEvacuate described the block
// entirely by position -- `char m_beforeCoords[0x20]`, the vector, `char
// m_beforeIntValue[0x08]`, then the integer -- which is correct arithmetic and
// says nothing about what the skipped bytes are. aiAttackMoveToPosition named
// nine members and cut the tail at +0x38. aiEnter and the object commands named
// six and cut it at +0x2C, so in those files the waypoint, polygon and integer
// slots did not exist at all. They are the same 0x9C block every time, and it is
// written out once below.
//
// DamageInfo at +0x38 is opaque here because no body in this TU touches it; the
// reconstructed classes are in AICommandInterfaceAttackCommands.cpp, next to
// aiGoProne, which does. std::vector is STLport's own vector -- the same
// _STL::vector the /DWIN32 TUs spell explicitly.
#include <vector>

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_MOVE_TO_POSITION = 0x00,
	AICMD_IDLE = 0x05,
	AICMD_ATTACKMOVE_TO_POSITION = 0x0F,
	AICMD_HUNT = 0x12,
	AICMD_ENTER = 0x17,
	AICMD_EVACUATE = 0x1B
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType cmdSource );	// ILT 0x00030EA4

	AICommandType m_cmd;					// +0x00
	CommandSourceType m_cmdSource;			// +0x04
	Coord3D m_pos;							// +0x08
	Object *m_obj;							// +0x14
	Object *m_otherObj;						// +0x18
	const Team *m_team;						// +0x1C
	std::vector<Coord3D> m_coords;			// +0x20
	const Waypoint *m_waypoint;				// +0x2C
	const PolygonTrigger *m_polygon;		// +0x30
	int m_intValue;							// +0x34
	DamageInfo m_damage;					// +0x38
	const CommandButton *m_commandButton;	// +0x94
	Path *m_path;							// +0x98
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;

	void aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource );
	void aiIdle( CommandSourceType cmdSource );
	void aiHunt( CommandSourceType cmdSource );
	void aiEnter( Object *obj, CommandSourceType cmdSource );
	void aiEvacuate( bool exposeStealthUnits, CommandSourceType cmdSource );
	void aiAttackMoveToPosition( const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource );
};

void AICommandInterface::aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_MOVE_TO_POSITION, cmdSource );
	parms.m_pos = *pos;
	aiDoCommand( &parms );
}

void AICommandInterface::aiIdle( CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_IDLE, cmdSource );
	aiDoCommand( &parms );
}

void AICommandInterface::aiHunt( CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_HUNT, cmdSource );
	aiDoCommand( &parms );
}

void AICommandInterface::aiEnter( Object *obj, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_ENTER, cmdSource );
	parms.m_obj = obj;
	aiDoCommand( &parms );
}

void AICommandInterface::aiEvacuate( bool exposeStealthUnits, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_EVACUATE, cmdSource );
	if ( exposeStealthUnits )
		parms.m_intValue = 1;
	else
		parms.m_intValue = 0;
	aiDoCommand( &parms );
}

void AICommandInterface::aiAttackMoveToPosition( const Coord3D *pos,
	int maxShotsToFire, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_ATTACKMOVE_TO_POSITION, cmdSource );
	parms.m_pos = *pos;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand( &parms );
}
