// ??0AIGuardRetaliateMachine@@
// partial score=0.97 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class State;

typedef bool (*StateTransFuncPtr)( State *, void * );

struct StateConditionInfo
{
	StateConditionInfo( StateTransFuncPtr testFunction, unsigned int stateID, void *data )
		: test( testFunction ), toStateID( stateID ), userData( data ) {}

	StateTransFuncPtr test;
	unsigned int toStateID;
	void *userData;
};

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );
	virtual ~StateMachine();

protected:
	void defineState( unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions );

private:
	char m_layout[ 0x40 ];
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

class Rva0015F070GuardState
{
public:
	Rva0015F070GuardState( StateMachine *machine );

private:
	char m_layout[ 0x48 ];
};

extern int g_AIGuardRetaliateReturnStateVTable;

class AIGuardRetaliateReturnState : public Rva0014F280StateBase
{
public:
	AIGuardRetaliateReturnState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile unsigned int m_nextReturnScanTime;
};

AIGuardRetaliateReturnState::AIGuardRetaliateReturnState( StateMachine *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIGuardRetaliateReturn" ) )
{
	m_vftable = &g_AIGuardRetaliateReturnStateVTable;
	m_nextReturnScanTime = 0;
}

bool bfmeHasAttackedMeAndICanReturnFire( State *, void * );

class AIGuardRetaliateMachine : public StateMachine
{
public:
	AIGuardRetaliateMachine( Object *owner );

protected:
	virtual void crc( void *xfer );
	virtual void xfer( void *xfer );
	virtual void loadPostProcess();

private:
	volatile float m_positionToGuardX;
	volatile float m_positionToGuardY;
	volatile float m_positionToGuardZ;
	volatile unsigned int m_nemesisToAttack;
};

// ??0AIGuardRetaliateMachine@@QAE@PAVObject@@@Z
AIGuardRetaliateMachine::AIGuardRetaliateMachine( Object *owner )
	: StateMachine( owner, AsciiString( "AIGuardRetaliateMachine" ), false ),
	  m_nemesisToAttack( 0 )
{
	m_positionToGuardX = 0.0f;
	m_positionToGuardY = 0.0f;
	m_positionToGuardZ = 0.0f;

	static const StateConditionInfo attackAggressors[] =
	{
		StateConditionInfo( bfmeHasAttackedMeAndICanReturnFire, 5005, 0 ),
		StateConditionInfo( 0, 0, 0 )
	};

	Rva0015F070GuardState *attack = new Rva0015F070GuardState( this );
	defineState( 5005, (State *)attack, 5003, 5003, 0 );

	AIGuardRetaliateReturnState *returnState = new AIGuardRetaliateReturnState( this );
	defineState( 5003, (State *)returnState, 9998, 5005, attackAggressors );
}
