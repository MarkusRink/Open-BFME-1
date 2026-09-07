// ?d_00621170@@YAXXZ
// partial score=0.82 date=2026-09-07
// Best scratch reconstruction for RVA 0x00621170; not an official source body.
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

typedef bool Bool;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

	int getLength() const { return m_data ? m_data->length : 0; }
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }
	bool nextToken(StringBase<T> *out, const T *delimiters);
	const T *find(T c) const
	{
		const T *start = m_data ? &m_data->data[0] : (const T *)"";
		const T *end = start + (m_data ? m_data->length : 0);
		for (const T *p = start; p != end; ++p)
		{
			if (*p == c)
				return p;
		}
		return 0;
	}
	void concat(const StringBase<T> &source);
	void concat(T source);
	void set(const StringBase<T> &source);

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
	int getLength() const { return StringBase<char>::getLength(); }
	const char *str() const { return StringBase<char>::str(); }
	bool nextToken(AsciiString *out, const char *delimiters)
	{
		return StringBase<char>::nextToken(out, delimiters);
	}
	const char *find(char c) const
	{
		const StringBase<char>::Header *data = ((const StringBase<char> *)this)->m_data;
		const char *start = data ? &data->data[0] : "";
		const char *end = start + (data ? data->length : 0);
		for (const char *p = start; p != end; ++p)
		{
			if (*p == c)
				return p;
		}
		return 0;
	}
	void concat(char c) { StringBase<char>::concat(c); }
	void concat(const AsciiString &source) { StringBase<char>::concat(source); }
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
	AsciiString _Rva0010F820MapPathTransform(const AsciiString &in) const;
};

extern GameState *TheGameState;

AsciiString _Rva00621170MapPathHelperBest(const AsciiString &input, Bool option)
{
	AsciiString mapName = TheGameState->realMapPathToPortableMapPath(input);
	if (option)
		mapName = TheGameState->_Rva0010F820MapPathTransform(mapName);

	AsciiString newMapName;
	if (mapName.getLength() > 0)
	{
		AsciiString token;
		mapName.nextToken(&token, "\\/");
		while (mapName.find('\\') != 0)
		{
			if (newMapName.getLength() > 0)
				newMapName.concat('/');
			newMapName.concat(token);
			mapName.nextToken(&token, "\\/");
		}
	}
	return newMapName;
}
