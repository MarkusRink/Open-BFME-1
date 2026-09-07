// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The two readable command-button actions:
//
//   0x002F4A20  doTeamUseCommandButtonAbility  arm 245, TEAM_USE_COMMANDBUTTON_ABILITY
//   0x002F54C0  doTeamUseCommandButtonOnNamed  the same, aimed at a named unit
//
// Both resolve the team at slot 17, ask ControlBar for the button by name, and
// hand it to the team's AIGroup. The on-named form does more first: it works out
// which member of the group is the source -- by special-power id when the button
// has a template, by command type otherwise -- and asks the button whether it is
// valid to use on the target before issuing the order.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AIGroup;
class CommandButton;
class Object;
class Team;
struct Coord3D;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}

private:
	void *m_memoryPoolVTable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getID() const
	{
		return getFinalOverride()->m_id;
	}

private:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	AsciiString m_name;
	UnsignedInt m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	Bool isValidToUseOn(const Object *, const Object *, const Coord3D *, CommandSourceType) const;

private:
	unsigned char m_beforeCommand[0x10];
	GUICommandType m_command;
	unsigned char m_beforeSpecialPower[0x20];
	const SpecialPowerTemplate *m_specialPower;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoCommandButton(const CommandButton *button, CommandSourceType cmd);
	void groupDoCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType);
	Object *getSpecialPowerSourceObject(UnsignedInt);
	Object *getCommandButtonSourceObject(GUICommandType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

extern AI *TheAI;
extern ControlBar *TheControlBar;
extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamUseCommandButtonAbility(const AsciiString &team,
		const AsciiString &ability);
	void doTeamUseCommandButtonOnNamed(
		const AsciiString &, const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamUseCommandButtonAbility(const AsciiString &team,
	const AsciiString &ability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (theTeam)
	{
		const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
		if (commandButton)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupDoCommandButton(commandButton, CMD_FROM_SCRIPT);
			}
		}
	}
}

// ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doTeamUseCommandButtonOnNamed(
	const AsciiString &teamName, const AsciiString &commandAbility, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = 0;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(
			commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	if (commandButton->isValidToUseOn(srcObj, obj, 0, CMD_FROM_SCRIPT)) {
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}
