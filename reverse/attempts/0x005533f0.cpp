// ?_bfme_acceptLocale@BfmeAptScreenOnlineLogin@@QAEXPBD@Z
// partial score=0.84 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// AptOnline::Login::AcceptLocale callback.  The registration in the matched
// OnlineLogin constructor at 0x005538A0 stores this method under that exact
// action name and the 0x0001EC77 ILT reaches retail 0x005533F0.

#include "PreRTS.h"

#include "Common/GameSpyMiscPreferences.h"

class GameWindow;

void GadgetListBoxGetSelected( GameWindow *window, int *selected );
void *GadgetListBoxGetItemData( GameWindow *window, int row, int column );

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

// This is the existing 0x00049E1D ICF route used by the OnlineLogin
// singleton's tail action.  The retail global slot is also read as
// TheBfmeOnlineLogin by the matched OnlineLogin destructor/constructor family;
// only the callee's already-proven ABI is viewed here.
class BfmeObjELB
{
public:
	void bfmeTailELB( int argument );
};

extern WindowManager *g_theWindowManager;

struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[ 0x250 ];
	void *m_window;
};

class BfmeAptScreenOnlineLogin
{
public:
	// OnlineLogin's registered callbacks receive one const-char pointer
	// argument; this callback ignores it, as do the matched link callbacks.
	void _bfme_acceptLocale( const char *argument );

private:
	const void *m_vftable; // constructor 0x005538A0 installs 0x01107F58
	unsigned char m_unmodelled04[ 0x30 ];
	BfmeOnlineLoginContext *m_context; // retail [this+0x34]
	unsigned char m_unmodelled38[ 0x50 ];
	GameWindow *m_localeList; // retail [this+0x88]
	unsigned char m_unmodelled8C[ 0x13 ];
	unsigned char m_closeLocaleArgument; // retail [this+0x9F]
	unsigned char m_unmodelledA0[ 4 ];
	int m_locale; // retail [this+0xA4]
};

void BfmeAptScreenOnlineLogin::_bfme_acceptLocale( const char * )
{
	int selected = -1;
	GadgetListBoxGetSelected( m_localeList, &selected );
	if( selected >= 0 )
	{
		m_locale = (int)GadgetListBoxGetItemData( m_localeList, selected, 0 );
		GameSpyMiscPreferences preferences;
		preferences.setLocale( m_locale );
		preferences.write();
	}
	else
	{
		*(unsigned char *)0x012F4AB0 = 1;
	}

	g_theWindowManager->add( m_context->m_window,
		"CallChild", 1, (void *)"DoCloseLocale", 0, 0, 0, 0 );

	(*(BfmeObjELB **)0x012F4AAC)->bfmeTailELB( m_closeLocaleArgument );
}
