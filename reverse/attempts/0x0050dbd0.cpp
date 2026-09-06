// ??1BfmeAptScreenCampaignReview@@UAE@XZ
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenCampaignReview destructor, retail 0x0050DBD0 (159 bytes).
// AptScreenFactories.cpp already names the class, its two vtables and the
// singleton g_obj12F495C from the constructor at 0x0003D09B; this body
// restores both vtables, closes the apt screen by name, hides the shell if
// present, clears the singleton, then chains to the base
// _bfme_AptGameWindow destructor (Gen_dtor_00465500).

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class Shell
{
public:
	void hide( bool shutdownImmediate );
};

void _bfme_closeAptScreen( const AsciiString &name );

extern const void *BfmeAptScreenCampaignReviewVftable[];
extern const void *BfmeAptScreenCampaignReviewSecondaryVftable[];
extern Shell *TheShell;
extern void *g_obj12F495C;

class __declspec(novtable) __multiple_inheritance BfmeAptScreenCampaignReview
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenCampaignReview();
};

// ??1BfmeAptScreenCampaignReview@@UAE@XZ
extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

BfmeAptScreenCampaignReview::~BfmeAptScreenCampaignReview()
{
	*(const void * volatile *)( (char *)this ) = BfmeAptScreenCampaignReviewVftable;
	_ReadWriteBarrier();
	*(const void * volatile *)( (char *)this + 0x218 ) =
		BfmeAptScreenCampaignReviewSecondaryVftable;

	_bfme_closeAptScreen( AsciiString( "CampaignReview.apt" ) );

	if( TheShell )
		TheShell->hide( false );

	g_obj12F495C = 0;
}
