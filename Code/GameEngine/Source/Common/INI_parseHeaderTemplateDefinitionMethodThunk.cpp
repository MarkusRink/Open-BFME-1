// cl: /DNDEBUG /MD /EHsc

// Retail's named parser is the caller that selects the HeaderTemplate
// manager methods at 0x0048C8C0 and 0x0048CAD0.  Its local AsciiString is
// the BFME four-byte StringBase value (not the ZH string surrogate); keeping
// the data-bearing private base here gives the by-value calls and cleanup
// their actual ABI.

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic(strlen)

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase( void ) : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	void set( const T *text, int length );
	void releaseBuffer( void );

protected:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( void ) : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString( void )
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}

	void set( const char *text, int length )
	{
		((StringBase<char> *)this)->StringBase<char>::set( text, length );
	}

};

typedef char BfmeAsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

class GameFont;

class HeaderTemplate
{
public:
	GameFont *m_font;
	AsciiString m_name;
	AsciiString m_fontName;
	int m_point;
	unsigned char m_bold;
};

typedef char HeaderTemplateSizeCheck[(sizeof(HeaderTemplate) == 20) ? 1 : -1];

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );
	HeaderTemplate *newHeaderTemplate( AsciiString name );

	// The retail call pushes the HeaderTemplate FieldParse table directly.
	// Its entries are Font/Point/Bold at VA 0x010F9830, defined by the owning
	// HeaderTemplate TU and reached through the manager's field-parse view.
	const void *getFieldParse( void ) const
	{
		return (const void *)0x010F9830;
	}
};

extern HeaderTemplateManager *TheHeaderTemplateManager;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const void *fieldParse );
	static void parseHeaderTemplateDefinition( INI *ini );
};

// ?parseHeaderTemplateDefinition@INI@@SAXPAV1@@Z
void INI::parseHeaderTemplateDefinition( INI *ini )
{
	AsciiString name;
	HeaderTemplate *hTemplate = 0;
	const char *c = ini->getNextToken();
	name.set( c, c ? (int)strlen( c ) : 0 );
	hTemplate = TheHeaderTemplateManager->findHeaderTemplate( name );
	if( hTemplate == 0 )
		hTemplate = TheHeaderTemplateManager->newHeaderTemplate( name );
	ini->initFromINI( hTemplate, TheHeaderTemplateManager->getFieldParse() );
}
