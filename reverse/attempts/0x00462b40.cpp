// ?bfmeFinish991@@YAXXZ
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <hash_map>

class AsciiString
{
private:
	void *m_data;
};

class GameWindow
{
public:
	bool winIsHidden();
	void winHide(bool hide);
	void winSetStatus(unsigned int status);
};

struct WindowRecord
{
	char m_pad00[16];
	GameWindow *m_window;
	char m_pad14[16];
	bool m_hidden;
};

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

struct Rva00461360Value
{
	AsciiString m_key;
	WindowRecord m_mapped;
};

struct Rva00461360ExtractKey
{
	const AsciiString &operator()(const Rva00461360Value &value) const
	{
		return value.m_key;
	}
};

typedef _STL::hashtable<Rva00461360Value, AsciiString, rts::hash<AsciiString>,
	Rva00461360ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461360Value> > WindowTable;

WindowTable *const g_windowTable = (WindowTable *)0x012F19A4;

// ?bfmeFinish991@@YAXXZ
void bfmeFinish991()
{
	WindowTable *table = g_windowTable;
	for (WindowTable::iterator it = table->begin(); it._M_cur != 0; it++)
	{
		if (!it->m_mapped.m_hidden)
		{
			GameWindow *window = it->m_mapped.m_window;
			if (window && !window->winIsHidden())
			{
				window->winHide(true);
				window->winSetStatus(0x10000000);
			}
		}
	}
}
