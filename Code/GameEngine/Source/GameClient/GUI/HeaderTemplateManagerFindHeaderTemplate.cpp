// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ?findHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
//
// Retail walks the std::list sentinel stored at manager+0.  A node links at
// +0x00 and stores its HeaderTemplate at +0x08.  HeaderTemplate's name is the
// inline AsciiString at +0x04.  The lookup compares the by-value query's
// ushort length/data with that name, then releases the automatic query on
// both the match and no-match exits.

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T data[1];
};

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
};

extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const AsciiString &other )
		: m_data( other.m_data )
	{}
	~AsciiString()
	{
		releaseBuffer();
	}
	int compare( const AsciiString &other ) const
	{
		int otherLength = other.m_data ? *(const unsigned short *)(other.m_data + 4) : 0;
		const char *otherText = other.m_data ? other.m_data + 8 : (const char *)0x0107388B;
		int thisLength = m_data ? *(const unsigned short *)(m_data + 4) : 0;
		const char *thisText = m_data ? m_data + 8 : (const char *)0x0107388B;
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp( thisText, otherText, length );
		if( result != 0 )
			return result;
		return thisLength - otherLength;
	}

	protected:
	void releaseBuffer( void );

	private:
	char *m_data;
};

class GameFont;

class HeaderTemplate
{
public:
	GameFont *m_font;
	AsciiString m_name;
};

struct HeaderTemplateListNode
{
	HeaderTemplateListNode *m_next;
	unsigned int m_unused;
	HeaderTemplate *m_value;
};

class HeaderTemplateList
{
public:
	HeaderTemplateListNode *m_node;
};

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );

private:
	HeaderTemplateList m_headerTemplateList;
};

HeaderTemplate *HeaderTemplateManager::findHeaderTemplate( AsciiString name )
{
	HeaderTemplateListNode *head = m_headerTemplateList.m_node;
	for( HeaderTemplateListNode *it = head->m_next; it != head; it = it->m_next )
	{
		HeaderTemplate *header = it->m_value;
		if( header->m_name.compare( name ) == 0 )
			return header;
	}
	return 0;
}
