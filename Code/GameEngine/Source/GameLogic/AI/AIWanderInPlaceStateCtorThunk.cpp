// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: AIWanderInPlaceState constructor, retail 0x0017FB80, 63 bytes.

#include "Common/AsciiString.h"

class StateMachine;

class State
{
public:
	State(StateMachine *machine, AsciiString name);
	virtual ~State();

private:
	unsigned char m_head[0x20];
};

class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	unsigned char m_body[0x2C];
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero(void)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	AIWanderInPlaceState(StateMachine *machine);

private:
	Coord3D m_origin;
	int m_waitFrames;
	int m_timer;
};

// ??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z
AIWanderInPlaceState::AIWanderInPlaceState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIWanderInPlaceState")
{
	m_origin.zero();
	m_waitFrames = 0;
	m_timer = 0;
}
