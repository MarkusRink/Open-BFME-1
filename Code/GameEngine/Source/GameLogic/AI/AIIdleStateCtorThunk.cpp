// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

protected:
	int *volatile m_vftable;
	unsigned char m_head[0x20];
};

extern int g_AIIdleStateVTable;

// upstream source and layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
// BFME retains the targeting mode and one cleared word after the three fields
// shared with the later Generals version; the retail constructor proves both.
class AIIdleState : public State
{
public:
	enum AIIdleTargetingType
	{
		LOOK_FOR_TARGETS,
		DO_NOT_LOOK_FOR_TARGETS
	};

	AIIdleState(StateMachine *machine, AIIdleTargetingType targetingType);

private:
	unsigned short m_initialSleepOffset;
	bool m_shouldLookForTargets;
	bool m_inited;
	AIIdleTargetingType m_targetingType;
	bool m_bfmeIdleState2C;
};

// ??0AIIdleState@@QAE@PAVStateMachine@@W4AIIdleTargetingType@0@@Z
AIIdleState::AIIdleState(StateMachine *machine, AIIdleTargetingType targetingType) :
	State(machine, "AIIdleState")
{
	m_inited = false;
	m_bfmeIdleState2C = false;
	m_shouldLookForTargets = true;
	m_initialSleepOffset = 0xFFFF;
	m_vftable = &g_AIIdleStateVTable;
	m_targetingType = targetingType;
}
