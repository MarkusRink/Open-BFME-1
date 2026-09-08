// cl: /DNDEBUG /MD /EHsc
// Retail 0x00189760 is slot 6 in vtable 0x0109B370.
// The same vtable uses AIMoveToPositionAndEnterState::onEnter at slot 4.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

class Object;

template <int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

class AICommandInterface
{
public:
	void aiEnter(Object *, CommandSourceType);

private:
	char m_unreconstructed[4];
};

class AIUpdateInterface : public BFMEVirtualSlots<128>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0;

	AICommandInterface *commands()
	{
		return (AICommandInterface *)((char *)this + 0x20);
	}
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *, const Object *, CommandSourceType,
		CanEnterType, bool *);
};

struct ObjectView
{
	char m_unreconstructed[0x204];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_unreconstructed[0x10];
	Object *m_owner;
};

class AIMoveToState
{
protected:
	char m_unreconstructed[0x18];
	StateMachine *m_machine;

public:
	virtual StateReturnType update();
};

class AIMoveToPositionAndEnterState : public AIMoveToState
{
public:
	virtual StateReturnType update();
};

extern BFMEActionManager *TheActionManager;

StateReturnType AIMoveToPositionAndEnterState::update()
{
	ObjectView *obj = (ObjectView *)m_machine->m_owner;
	Object *goal = m_machine->getGoalObject();
	AIUpdateInterface *ai = obj->m_ai;
	if (ai && !TheActionManager->canEnterObject(
		(Object *)obj, goal, ai->getLastCommandSource(), CHECK_CAPACITY, 0))
		return STATE_FAILURE;

	StateReturnType result = AIMoveToState::update();
	if (result == STATE_SUCCESS)
	{
		ai = ((ObjectView *)m_machine->m_owner)->m_ai;
		goal = m_machine->getGoalObject();
		ai->commands()->aiEnter(goal, ai->getLastCommandSource());
	}
	return result;
}
