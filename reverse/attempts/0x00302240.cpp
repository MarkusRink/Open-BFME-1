// ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.2 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Readable C++ conversion of ScriptActions::doTeamGarrisonNearestBuilding.
// Identity: executeAction template 108 -> arm -> ILT 0x00008A8F -> retail RVA
// 0x00302240 (536 bytes).
// stlport

#include "PreRTS.h"
#include "Common/GameEngine.h"
#include "Common/MapObject.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Team.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/View.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "GameLogic/ObjectTypes.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptConditions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/VictoryConditions.h"

void ScriptActions::doTeamGarrisonNearestBuilding(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theTeam) {
		return;
	}

	DLINK_ITERATOR<Object> diter = theTeam->iterate_TeamMemberList();
	Object *leader = diter.cur();
	if (!leader) {
		return;
	}

	PartitionFilter *filters[16];
	Int count = 0;

	PartitionFilterAcceptByKindOf f1(MAKE_KINDOF_MASK(KINDOF_FS_INTERNET_CENTER),
		KINDOFMASK_NONE);
	PartitionFilterGarrisonableByPlayer f2(theTeam->getControllingPlayer(), true,
		CMD_FROM_SCRIPT);

	if (leader->isKindOf(KINDOF_MONEY_HACKER)) {
		filters[count++] = &f1;
	} else {
		filters[count++] = &f2;
	}

	PartitionFilterSameMapStatus filterMapStatus(leader);
	filters[count++] = &filterMapStatus;
	filters[count++] = NULL;

	ObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(
		leader, 1000000.0f, FROM_CENTER_3D, filters,
		ITER_SORTED_NEAR_TO_FAR);
	MemoryPoolObjectHolder hold(iter);

	for (Object *theBuilding = iter->first(); theBuilding;
		theBuilding = iter->next()) {
		ContainModuleInterface *cmi = theBuilding->getContain();
		if (!cmi) {
			continue;
		}

		Int slotsAvailable = cmi->getContainMax() - cmi->getContainCount();
		for (int i = 0; i < slotsAvailable; ) {
			Object *obj = diter.cur();
			if (diter.done() || !obj) {
				return;
			}

			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai && obj->isKindOf(KINDOF_INFANTRY) &&
				!obj->isKindOf(KINDOF_NO_GARRISON)) {
				ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
				++i;
			}
			diter.advance();
		}
	}
}
