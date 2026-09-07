// cl: /DNDEBUG /MD /EHsc
// stlport

// Retail newHeaderTemplate is the named factory reached by
// INI::parseHeaderTemplateDefinition through ILT 0x000470E6.  The manager's
// STLport list is a circular sentinel at this+0; a node is { next, prev,
// HeaderTemplate* } and the node allocation is 0x0c bytes.  The compact BFME
// AsciiString is a one-pointer StringBase<char> value; keep its real header
// layout here so the by-value parameter and assignment use the shared engine
// bodies rather than an empty ABI surrogate.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase( void );
	StringBase( const StringBase<T> &other );
	void set( const StringBase<T> &other );
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
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString( void )
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	AsciiString &operator=( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::set(
			*(const StringBase<char> *)&other);
		return *this;
	}
};

typedef char BfmeAsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

class GameFont;

class HeaderTemplate
{
public:
	HeaderTemplate( void );

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
	HeaderTemplate *newHeaderTemplate( AsciiString name );

private:
	typedef std::list<HeaderTemplate *> HeaderTemplateList;
	HeaderTemplateList m_headerTemplateList;
};

HeaderTemplate *HeaderTemplateManager::newHeaderTemplate( AsciiString name )
{
	HeaderTemplate *newHTemplate = new HeaderTemplate;
	if( !newHTemplate )
		return 0;

	newHTemplate->m_name = name;
	m_headerTemplateList.push_front( newHTemplate );
	return newHTemplate;
}
