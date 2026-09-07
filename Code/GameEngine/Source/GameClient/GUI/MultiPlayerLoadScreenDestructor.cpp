// cl: /DNDEBUG /MD /EHsc
// Open-BFME: MultiPlayerLoadScreen::~MultiPlayerLoadScreen at 0x00490890.
//
// The vtable at 0x010F9B28 is independently identified by the already
// matched MultiPlayerLoadScreen update/init/reset/processProgress slots.  This
// complete destructor clears the four corresponding per-slot tables, stops
// the music through the proven ClientSubsystem vslot +0x6c, and then chains to
// the existing window-owning base destructor through ILT 0x0004634E.

class Rva00490350Base;

class Rva00490350Base
{
public:
	virtual ~Rva00490350Base();
	virtual void slot1();

protected:
	Rva00490350Base *m_link;
	int m_unused;
	bool m_flag;
	char m_flagPadding[ 3 ];
};

class Rva00490470 : public Rva00490350Base
{
public:
	virtual ~Rva00490470();
	virtual void slot1();
};

class ClientSubsystem
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void slot6c( int a, int b, int c );
};

extern ClientSubsystem *TheAudioClientUpdate;

class MultiPlayerLoadScreen : public Rva00490470
{
public:
	virtual ~MultiPlayerLoadScreen();

private:
	void *m_progressBars[ 8 ];
	void *m_playerNames[ 8 ];
	void *m_playerSide[ 8 ];
	int m_playerLookup[ 8 ];
};

MultiPlayerLoadScreen::~MultiPlayerLoadScreen()
{
	for ( int i = 0; i < 8; ++i )
	{
		m_progressBars[ i ] = 0;
		m_playerNames[ i ] = 0;
		m_playerSide[ i ] = 0;
		m_playerLookup[ i ] = -1;
	}
	TheAudioClientUpdate->slot6c( 2, 1, 0 );
}
