// cl: /DNDEBUG /MD /EHsc
// Open-BFME: MultiPlayerLoadScreen::MultiPlayerLoadScreen at 0x00490790.
//
// The BFME LoadScreen base is the address-derived window-owning object
// Rva00490470 in Rva00490350LinkedCtorAndWindowDtor.cpp, on top of its linked
// Rva00490350Base.  Its link head, +0x08 scalar, and +0x0c flag are observable
// in this constructor before the MultiPlayerLoadScreen vtable is installed;
// its destructor tail-jump is the already matched 0x00490470 body.  The
// derived fields use the reference LoadScreen.h order, with the BFME
// five-table offsets proven by the already matched MultiPlayer
// update/processProgress/init methods.

class Rva00490350Base;
extern Rva00490350Base *Rva00490350Head;

class Rva00490350Base
{
public:
	Rva00490350Base( bool flag )
		: m_link( Rva00490350Head )
	{
		Rva00490350Head = this;
		m_unused = 0;
		m_flag = flag;
	}
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
	Rva00490470()
		: Rva00490350Base( true )
	{
	}
	virtual ~Rva00490470();
	virtual void slot1();
};

class MultiPlayerLoadScreen : public Rva00490470
{
public:
	MultiPlayerLoadScreen();
	virtual ~MultiPlayerLoadScreen();
	virtual void slot1();

private:
	void *m_progressBars[ 8 ];
	void *m_playerNames[ 8 ];
	void *m_playerSide[ 8 ];
	int m_playerLookup[ 8 ];
	void *m_mapPreview;
	void *m_buttonMapStartPosition[ 8 ];
};

MultiPlayerLoadScreen::MultiPlayerLoadScreen()
	: Rva00490470()
{
	m_mapPreview = 0;
	for ( int i = 0; i < 8; ++i )
	{
		m_buttonMapStartPosition[ i ] = 0;
		m_progressBars[ i ] = 0;
		m_playerNames[ i ] = 0;
		m_playerSide[ i ] = 0;
		m_playerLookup[ i ] = -1;
	}
}
