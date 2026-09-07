// ?_bfme_login@BfmeAptScreenOnlineLogin@@QAEXPBD@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail constructor 0x005538A0 registers this callback as
// AptOnline::Login::Login through ILT 0x0000649C, whose body route lands at
// 0x00553520.  The bool tail and receiver layout are independently shared
// with the other OnlineLogin state writer and AcceptLocale.

#include "PreRTS.h"

#include "Common/GameSpyMiscPreferences.h"

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

class Rva00548D30WindowGroup
{
public:
	void winEnable( bool enabled );
};

struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[ 0x250 ];
	void *m_window;
};

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_login( const char *argument );
	void rva00552C40( bool argument );

private:
	const void *m_vftable;
	unsigned char m_unmodelled04[ 0x30 ];
	BfmeOnlineLoginContext *m_context; // retail [this+0x34]
	unsigned char m_unmodelled38[ 0x67 ];
	bool m_closeLocaleArgument; // retail [this+0x9F]
	unsigned char m_unmodelledA0[ 4 ];
	int m_locale; // retail [this+0xA4]
};

extern WindowManager *g_theWindowManager;
extern BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;

void BfmeAptScreenOnlineLogin::_bfme_login( const char * )
{
	if( TheBfmeOnlineLogin != 0 )
	{
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonDeleteNickname", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonCreate", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonLogin", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonServiceTerms", 0, 0, 0, 0 );
		}

		GameSpyMiscPreferences preferences;
		if( preferences.getLocale() >= 1 && preferences.getLocale() <= 0x25 )
		{
			m_locale = preferences.getLocale();
			TheBfmeOnlineLogin->rva00552C40( false );
			return;
		}

		m_closeLocaleArgument = false;
		void *window = m_context->m_window;
		g_theWindowManager->add( window,
			"CallChild", 1, (void *)"DoOpenLocale", 0, 0, 0, 0 );
		reinterpret_cast<Rva00548D30WindowGroup *>( this )->winEnable( false );
	}
}
