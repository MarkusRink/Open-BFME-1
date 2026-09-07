// ?getFontFromTemplate@HeaderTemplateManager@@QAEPAVGameFont@@VAsciiString@@@Z
// partial score=0.99 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc

// The parseWindow caller at 0x00487F80 invokes this method for the END/CHILD
// header-template path through TheHeaderTemplateManager at 0x012F333C.  The
// 0x0048C8C0 lookup walks HeaderTemplateManager's list at +0x00, compares the
// HeaderTemplate name at +0x04, and returns HeaderTemplate; getFont then
// returns its GameFont pointer at +0x00.  This TU-local ABI view preserves the
// BFME StringBase<char> copy/release calls used by the retail by-value argument.

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
};

class AsciiString
{
public:
	AsciiString( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}

private:
	char *m_data;
};

class GameFont;

class HeaderTemplate
{
public:
	GameFont *m_font;

private:
	AsciiString m_name;
};

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );
	GameFont *getFontFromTemplate( AsciiString name );
};

// The retail caller reaches the list-search body through ILT 0x0004881A.
// This TU calls the already-pinned body symbol directly; the linker still
// emits the same 0x0048C8C0 REL32 used by the retail method.
#pragma comment(linker, "/alternatename:?findHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z=?b_0048c8c0@@YAXXZ")

// ?getFontFromTemplate@HeaderTemplateManager@@QAEPAVGameFont@@VAsciiString@@@Z
GameFont *HeaderTemplateManager::getFontFromTemplate( AsciiString name )
{
	HeaderTemplate *header = findHeaderTemplate( name );
	if (!header)
		return 0;
	return header->m_font;
}
