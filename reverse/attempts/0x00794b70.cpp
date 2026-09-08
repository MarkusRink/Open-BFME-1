// ?W3DGadgetPushButtonNumberDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@PAUPushButtonData@@@Z
// partial score=0.99 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Color;
typedef unsigned short WCHAR;
typedef float Real;

template <typename T> class StringBase
{
friend class UnicodeString;

private:
	StringBase( void );
	StringBase( const StringBase<T> &that );
	StringBase( const T *text );
	void releaseBuffer( void );

public:
};

class UnicodeString
{
public:
	UnicodeString( void ) { m_data = 0; }
	UnicodeString( const WCHAR *text )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase( text );
	}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase(
			*(const StringBase<WCHAR> *)&that );
	}
	~UnicodeString( void )
	{
		((StringBase<WCHAR> *)this)->releaseBuffer();
	}

	void format( UnicodeString fmt, ... );

private:
	void *m_data;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct DrawLocals
{
	Int width;
	Int height;
	Color textColor;
	Color dropColor;
	Int originX;
	Int originY;
	Int sizeX;
	Int sizeY;
};

class GameFont;

class DisplayString
{
public:
	virtual void unused00();
	virtual void setText( UnicodeString text );
	virtual void unused01();
	virtual void unused02();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont( GameFont *font );
	virtual GameFont *getFont();
	virtual void unused08();
	virtual void unused09();
	virtual void setTextColor( Color color, Color drop );
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw( Int x, Int y, Int color, Int drop );
	virtual void getSize( Int *width, Int *height );
};

class WinInstanceData
{
public:
	unsigned char pad00[8];
	UnsignedInt state;
};

class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	GameFont *winGetFont();
};

struct PushButtonData
{
	unsigned char pad00[0x2C];
	UnsignedInt value;
	DisplayString *displayString;
};

extern const Real g_bfmeK1253;
extern void getButtonTextColors( GameWindow *window, WinInstanceData *instData,
	Color *textColor, Color *dropColor );

void W3DGadgetPushButtonNumberDraw( GameWindow *window,
	WinInstanceData *instData, PushButtonData *data )
{
	if( data == 0 || data->value < 1 )
		return;

	DrawLocals local;
	window->winGetSize( &local.sizeX, &local.sizeY );
	window->winGetScreenPosition( &local.originX, &local.originY );

	DisplayString *text = data->displayString;
	if( text == 0 )
		return;

	UnicodeString displayNumber;
	displayNumber.format( L"%d", data->value );
	text->setText( displayNumber );

	getButtonTextColors( window, instData, &local.textColor, &local.dropColor );

	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );

	text->getSize( &local.width, &local.height );

	register Int textX = local.sizeX * g_bfmeK1253 - local.width * g_bfmeK1253 + local.originX;
	register Int textY = local.originY + local.sizeY - local.height;
	text->setTextColor( local.textColor, local.dropColor );
	text->draw( textX, textY, 1, 1 );
}
