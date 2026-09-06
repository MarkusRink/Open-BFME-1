// ?bfmeRva00558A30@BfmeQuickMatchPopulateMaxPingBody@@QAE_NXZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// FILE: WOLQuickMatchMenu_populateMaxPing.cpp ///////////////////////////////////////////
// gap port rva=0x00558A30 size=332, zh_source=WOLQuickMatchMenu.cpp anchor="GUI:TimeInMilliseconds"
// The retail body is an outlined fragment of the quickmatch ping-combo populate logic
// (Zero Hour keeps this inline in WOLQuickMatchMenuInit(); BFME's compiler split it into
// its own thiscall helper operating on a caller-owned blob: a QuickMatchPreferences at
// +0x40 and the max-ping GameWindow* at +0x68 -- consistent with sizeof(QuickMatchPreferences)
// landing the window pointer right after the embedded preferences object). No ZH mangled
// name exists for this fragment (it is compiler-outlined), so it is landed here under an
// address-derived name in the class's home directory per IDENTITY POLICY.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

static Int s_bfmeMaxPingEntries = 0;

// BFME's QuickMatchPreferences (UserPreferences : std::map<AsciiString,AsciiString> plus
// extra fields) compiles larger than the Zero Hour header describes; the retail body only
// needs getMaxPing() through this object and puts the next field (m_maxPing) at +0x28 from
// here, so pad to that true size instead of pulling in the real (smaller, ZH-shaped) class.
class QuickMatchPreferences
{
public:
	Int getMaxPing(void);
private:
	unsigned char _bfme_pad28[0x28];
};

struct BfmeQuickMatchPopulateMaxPingBody
{
	unsigned char _bfme_pad40[0x40];
	QuickMatchPreferences m_pref;
	GameWindow *m_maxPing;

	Bool bfmeRva00558A30(void);
};

Bool BfmeQuickMatchPopulateMaxPingBody::bfmeRva00558A30(void)
{
	if (!m_maxPing)
		return FALSE;

	Color c = GameSpyColor[GSCOLOR_DEFAULT];
	UnicodeString s;
	GadgetComboBoxReset(m_maxPing);

	s_bfmeMaxPingEntries = (TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
	s_bfmeMaxPingEntries++;
	for (Int i = 1; i < s_bfmeMaxPingEntries; ++i)
	{
		s.format(TheGameText->fetch("GUI:TimeInMilliseconds"), i * 100);
		GadgetComboBoxAddEntry(m_maxPing, s, c);
	}
	GadgetComboBoxAddEntry(m_maxPing, TheGameText->fetch("GUI:ANY"), c);

	Int i = m_pref.getMaxPing();
	if (i < 0)
		i = 0;
	if (i >= s_bfmeMaxPingEntries)
		i = s_bfmeMaxPingEntries - 1;
	GadgetComboBoxSetSelectedPos(m_maxPing, i);

	return TRUE;
}
