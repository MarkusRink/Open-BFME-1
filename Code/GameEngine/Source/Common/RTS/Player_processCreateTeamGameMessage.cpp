// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x000D29C0. Create a hotkey team from the object IDs in a GameMessage.

#include "PreRTS.h"

#include "Common/MessageStream.h"
#include "Common/Player.h"

class Gen_0018B850
{
public:
	void bfmeClear(void);
};

class Rva0018B9A0Holder
{
public:
	void addObject(Object *object);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID objectID);
};

extern GameLogic *TheGameLogic;

void Player::processCreateTeamGameMessage(Int hotkeyNum, GameMessage *msg)
{
	if ((hotkeyNum < 0) || (hotkeyNum >= NUM_HOTKEY_SQUADS))
		return;

	struct BFMEPlayerHotkeySquads
	{
		char pad[0x654];
		Rva0018B9A0Holder *m_squads[NUM_HOTKEY_SQUADS];
	};
	((Gen_0018B850 *)((BFMEPlayerHotkeySquads *)this)->m_squads[hotkeyNum])->bfmeClear();

	UnsignedByte numArgs = msg->getArgumentCount();
	for (UnsignedByte i = 0; i < numArgs; ++i)
	{
		ObjectID objectID = msg->getArgument(i)->objectID;
		Object *object = TheGameLogic->findObjectByID(objectID);
		if (object != NULL)
		{
			removeObjectFromHotkeySquad(object);
			((BFMEPlayerHotkeySquads *)this)->m_squads[hotkeyNum]->addObject(object);
		}
	}
}
