// cl: /DNDEBUG /MD
//
// Retail 0x00271800: AIUpdateInterface::privateExitInstantly.
// The preceding 0x00271760 body is privateDock.  This body uses the object's
// contain interface at Object+0x1fc and its BFME horde exit view before it
// falls back to the AI exit-instantly state at 0x26.

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_EXIT_INSTANTLY = 0x26
};

class Object;

class HordeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void exitObject(Object *, CommandSourceType) = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Object
{
public:
	unsigned char m_unreconstructed_000[0x1fc];
	ContainModuleInterface *m_contain;
	unsigned char m_unreconstructed_200[0x14];
	Object *m_containedBy;
};

class StateMachine
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void clear() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void setState(StateID) = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual void slot2C() = 0; virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *) = 0;
};

class AIUpdateInterface
{
protected:
	virtual void privateExitInstantly(Object *objectToExit, CommandSourceType cmdSource);

	unsigned char m_unreconstructed_000[4];
	Object *m_object;
	unsigned char m_unreconstructed_00c[0x30 - 0x0c];
	StateMachine *m_stateMachine;
	unsigned char m_unreconstructed_034[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::privateExitInstantly(Object *objectToExit, CommandSourceType cmdSource)
{
	Object *us = m_object;
	if (!objectToExit)
		objectToExit = us->m_containedBy;

	if (!objectToExit)
		return;

	ContainModuleInterface *contain = us->m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->exitObject(objectToExit, cmdSource);
			return;
		}
	}

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(objectToExit);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_EXIT_INSTANTLY);
}
