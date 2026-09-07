// ?d_009d86e0@@YAXXZ
// partial score=0.55 date=2026-09-07
// scratch only: neutral Xfer-family helper reconstruction for retail 0x009D86E0.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <string>

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
};

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D86E0String;
typedef _STL::pair<const Rva009D86E0String, int> Rva009D86E0Pair;
typedef _STL::hash_map<Rva009D86E0String, int,
	_STL::hash<Rva009D86E0String>, _STL::equal_to<Rva009D86E0String>,
	_STL::allocator<Rva009D86E0Pair> > Rva009D86E0NameMap;
struct Rva009D86E0AuxMap
{
	unsigned char storage[0x14];
	int size(void) const
	{
		return *reinterpret_cast<const int *>(storage + 0x10);
	}
};

class Rva009D86E0Owner
{
public:
	virtual void slot0();
	void emitName(const char *name);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	unsigned char m_vector[0x0c];
	Rva009D86E0NameMap m_names;
	Rva009D86E0AuxMap m_aux;
};

void Rva009D86E0Owner::emitName(const char *name)
{
	if (name == 0 || *name == 0)
		return;

	Rva009D86E0NameMap::const_iterator found;
	{
		Rva009D86E0String key(name);
		found = m_names.find(key);
	}
	if (found != m_names.end())
	{
		unsigned char marker = 0xff;
		if (m_stream->write(&marker, 1) != 1)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		if (m_stream->write(&found->second, 4) != 4)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		return;
	}

	const char *cursor = name + 1;
	while (*cursor != 0)
		++cursor;
	unsigned int length = static_cast<unsigned int>(cursor - (name + 1));
	if (length > 0xfe)
		length = 0xfe;

	if (m_stream->write(&length, 1) != 1)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}
	if (m_stream->write(name, static_cast<int>(length)) !=
		static_cast<int>(length))
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	m_names[Rva009D86E0String(name)] =
		static_cast<int>(m_aux.size() + m_names.size());
}
