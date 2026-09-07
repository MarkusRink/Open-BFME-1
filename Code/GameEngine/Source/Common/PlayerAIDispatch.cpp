// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// readable body of ?onStructureConstructionComplete@Player@@QAEXPAVObject@@0_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

// The three Player methods that reach the player's AIPlayer through the
// pointer at Player+0x220 and call it through its vtable:
//
//   0x000C9600  onStructureConstructionComplete  onStructureProduced   slot 8
//   0x000C9740  buildSpecificTeam                buildSpecificAITeam   slot 9
//   0x000C9790  recruitSpecificTeam              recruitSpecificAITeam slot 10
//
// They sat in three files, and each one declared AIPlayer's vtable cut off
// immediately after the slot it happened to call: eight slots then
// onStructureProduced, nine then buildSpecificAITeam, ten then
// recruitSpecificAITeam. Three files, three different pictures of one vtable,
// none of them wrong and none of them able to say so. Declared once, the three
// slots line up and the numbering checks itself: what the recruit file called
// its slot 9 is the build file's buildSpecificAITeam, and what the build file
// called its slot 8 is the construction file's onStructureProduced.
//
// The AI pointer had drifted only in spelling -- m_ai in two files and
// PlayerAI in the third, at the same +0x220 -- and the padding before it was
// spelled three ways for the same 0x220 bytes.
//
// notifyOfObjectCreationOrDestruction is not a Player method and does not
// belong to this family; it rides along because it is the callee that
// onStructureConstructionComplete opens with, exactly as it did in that
// method's own file. It stays __declspec(noinline) because retail calls it.
//
// The construction file built with /DNDEBUG /MD /EHsc where the two forwarders
// build with /O2 /Ob0 ...; it byte-verifies unchanged under theirs, which is
// what let the three share a TU.

typedef bool Bool;
typedef float Real;

struct Coord3D;
class Object;
class TeamPrototype;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void onStructureProduced(Object *, Object *);				// slot 8, vtable+0x20
	virtual void buildSpecificAITeam(TeamPrototype *, Bool);			// slot 9, vtable+0x24
	virtual void recruitSpecificAITeam(TeamPrototype *, Real, const Coord3D *);	// slot 10, vtable+0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	__declspec(noinline) void notifyOfObjectCreationOrDestruction();

private:
	char Pad[0x170D8];
	unsigned int FrameObjectCountChanged;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
private:
	char Pad[0x3C];

public:
	unsigned int Frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *);
	void addObjectToPathfindMap(Object *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
private:
	char Pad[0x0C];

public:
	Pathfinder *PathfinderInstance;
};

class StructureCompletionInterface
{
public:
	virtual void Slot0();
	virtual void Slot1();
	virtual void Slot2();
	virtual void onConstructionComplete(Object *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void friend_adjustPowerForPlayer(bool);
	StructureCompletionInterface *getStructureCompletionInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
private:
	char Pad[0x24];

public:
	bool UIDirty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	char m_unreconstructed[0x220];
	AIPlayer *m_ai;								// this+0x220

public:
	void onStructureConstructionComplete(Object *, Object *, bool);
	void buildSpecificTeam(TeamPrototype *);
	void recruitSpecificTeam(TeamPrototype *, Real, const Coord3D *);
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ControlBar *TheControlBar;

// ?notifyOfObjectCreationOrDestruction@ScriptEngine@@QAEXXZ
__declspec(noinline) void ScriptEngine::notifyOfObjectCreationOrDestruction()
{
	FrameObjectCountChanged = TheGameLogic->Frame;
}

// ?onStructureConstructionComplete@Player@@QAEXPAVObject@@0_N@Z
void Player::onStructureConstructionComplete(Object *builder, Object *structure, bool)
{
	TheScriptEngine->notifyOfObjectCreationOrDestruction();
	TheAI->PathfinderInstance->removeObjectFromPathfindMap(structure);
	TheAI->PathfinderInstance->addObjectToPathfindMap(structure);
	structure->friend_adjustPowerForPlayer(true);

	if (m_ai != 0) {
		m_ai->onStructureProduced(builder, structure);
	}

	if (TheControlBar != 0) {
		TheControlBar->UIDirty = true;
	}

	if (structure->getStructureCompletionInterface() != 0) {
		structure->getStructureCompletionInterface()->onConstructionComplete(builder);
	}
}

// ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z
void Player::buildSpecificTeam(TeamPrototype *teamPrototype)
{
	if (m_ai) {
		m_ai->buildSpecificAITeam(teamPrototype, true);
	}
}

// ?recruitSpecificTeam@Player@@QAEXPAVTeamPrototype@@MPBUCoord3D@@@Z
void Player::recruitSpecificTeam(
	TeamPrototype *teamPrototype, Real recruitRadius, const Coord3D *position)
{
	if (m_ai) {
		m_ai->recruitSpecificAITeam(teamPrototype, recruitRadius, position);
	}
}
