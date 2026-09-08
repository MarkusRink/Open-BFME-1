// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	virtual ~State();

protected:
	unsigned char m_head[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	unsigned char m_body[0x2C];
};

struct Coord3D
{
	Coord3D() : x(0.0f), y(0.0f), z(0.0f) {}

	float x;
	float y;
	float z;
};

// upstream source and layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	AIAttackPursueTargetState(StateMachine *machine, bool follow, bool attackingObject, bool forceAttacking);
	virtual bool isAttack() const;

private:
	Coord3D m_prevVictimPos;
	unsigned int m_approachTimestamp;
	bool m_follow;
	bool m_isAttackingObject;
	bool m_stopIfInRange;
	bool m_isInitialApproach;
	bool m_isForceAttacking;
};

// ??0AIAttackPursueTargetState@@QAE@PAVStateMachine@@_N11@Z
AIAttackPursueTargetState::AIAttackPursueTargetState(
	StateMachine *machine,
	bool follow,
	bool attackingObject,
	bool forceAttacking) :
	AIInternalMoveToState(machine, "AIAttackPursueTargetState"),
	m_prevVictimPos(),
	m_approachTimestamp(0),
	m_follow(follow),
	m_isAttackingObject(attackingObject),
	m_stopIfInRange(false),
	m_isInitialApproach(true),
	m_isForceAttacking(forceAttacking)
{
}
