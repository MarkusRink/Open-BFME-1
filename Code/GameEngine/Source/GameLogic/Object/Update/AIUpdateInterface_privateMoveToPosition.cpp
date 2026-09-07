// cl: /DNDEBUG /MD
//
// Retail 0x00278280: AIUpdateInterface::privateMoveToPosition.
// BFME rejects mine-clearing details, preserves the active goal for an AI
// move, and uses a 100-frame temporary move state when the unit is busy.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_INTERNAL = 2
};

enum StateID
{
	BFME_AI_MOVE_TO = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class WeaponSetFlags
{
public:
	Bool test(int type) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

class Object
{
public:
	Bool isMobile() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

class Rva001B5CC0
{
public:
	void set(const char *other);
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

class Rva0016AD50
{
public:
	void bfmeSnapshot();
};

#pragma comment(linker, "/alternatename:?bfmeSnapshot@Rva0016AD50@@QAEXXZ=?j_0002d308@@YAXXZ")

class Rva0016AD90
{
public:
	void setTemporaryState(StateID state, int frameCount);
};

#pragma comment(linker, "/alternatename:?setTemporaryState@Rva0016AD90@@QAEXW4StateID@@H@Z=?j_00044319@@YAXXZ")

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

protected:
	virtual void privateMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void playMoveVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x16C - 0x4C];
	int m_blockedFrames;
	unsigned char m_unmodelled_170[0x1CC - 0x170];
	Rva001B5CC0 *m_curLocomotor;
	unsigned char m_unmodelled_1D0[0x325 - 0x1D0];
	unsigned char m_isBlocked;
	unsigned char m_isBlockedAndStuck;
};

void AIUpdateInterface::privateMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	if (!isIdle() && cmdSource == CMD_FROM_INTERNAL)
	{
		reinterpret_cast<Rva0016AD50 *>(m_stateMachine)->bfmeSnapshot();
		reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
		m_blockedFrames = 0;
		m_isBlocked = 0;
		m_isBlockedAndStuck = 0;
		reinterpret_cast<Rva0016AD90 *>(m_stateMachine)->setTemporaryState(BFME_AI_MOVE_TO, 100);
		return;
	}

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}
