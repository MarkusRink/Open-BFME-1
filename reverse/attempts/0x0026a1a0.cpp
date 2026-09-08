// ?loadPostProcess@SpecialPowerModule@@MAEXXZ
// partial score=0.84 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Authentic ZH source body; BFME layout residue is documented in re_attempts.log.

#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Object.h"

void SpecialPowerModule::loadPostProcess( void )
{
	BehaviorModule::loadPostProcess();

	if( m_pausedCount == 0 &&
			getSpecialPowerTemplate()->isSharedNSync() == TRUE &&
			getSpecialPowerTemplate()->hasPublicTimer() == TRUE &&
			getObject()->getControllingPlayer() &&
			getObject()->isKindOf( KINDOF_STRUCTURE ) )
	{
		TheInGameUI->addSuperweapon( getObject()->getControllingPlayer()->getPlayerIndex(),
																 getPowerName(),
																 getObject()->getID(),
																 getSpecialPowerModuleData()->m_specialPowerTemplate );
	}
}
