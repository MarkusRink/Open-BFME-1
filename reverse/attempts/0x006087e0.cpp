// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS
// partial score=0.58 date=2026-09-08
// Open-BFME: SoundUpgrade record INI parser, retail 0x006087E0 (374 bytes).

#define _STLP_NO_EXCEPTIONS 1

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();
};

inline void *operator new(unsigned int, void *place)
{
	return place;
}

inline void operator delete(void *, void *)
{
}

struct SoundUpgradeFalseType
{
};

class SoundUpgradeVector
{
public:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_end;

	AsciiString *begin() { return m_start; }
	AsciiString *end() { return m_finish; }
	AsciiString *erase(AsciiString *, AsciiString *);
	void _M_insert_overflow(AsciiString *, const AsciiString &,
		const SoundUpgradeFalseType &, unsigned int, bool);

	void push_back(const AsciiString &value)
	{
		if (m_finish != m_end)
		{
			new (m_finish) AsciiString(value);
			++m_finish;
		}
		else
		{
			SoundUpgradeFalseType tag;
			_M_insert_overflow(m_finish, value, tag, 1, true);
		}
	}
};

#pragma comment(linker, "/alternatename:?erase@SoundUpgradeVector@@QAEPAVAsciiString@@PAV2@0@Z=?j_00024c17@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_insert_overflow@SoundUpgradeVector@@QAEXPAVAsciiString@@ABV2@ABVSoundUpgradeFalseType@@I_N@Z=?j_0003827b@@YAXXZ")

struct FieldParse;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		m_count = 0;
		for (int i = 0; i < 16; ++i)
		{
			m_offsets[i] = 0;
			m_fields[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fields[16];
	unsigned int m_offsets[16];
	unsigned int m_count;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators);
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

extern const FieldParse *getVoiceFieldParse();

class Rva00608FE0Element
{
public:
	void parse(INI *ini);
	void finish(void *, void *);

private:
	int m_values0[6];
	int m_values18[6];
	SoundUpgradeVector m_soundNames;
	SoundUpgradeVector m_otherNames;
	unsigned char m_member48[0x1B4];
	unsigned char m_member1FC[0x0C];
	int m_field208;
	unsigned char m_field20C;
	unsigned char m_padding20D[3];
};

#pragma comment(linker, "/alternatename:?finish@Rva00608FE0Element@@QAEXPAX0@Z=?j_0000f187@@YAXXZ")

void Rva00608FE0Element::parse(INI *ini)
{
	m_soundNames.erase(m_soundNames.begin(), m_soundNames.end());
	m_values0[0] = 0;
	m_values0[1] = 0;
	m_values0[2] = 0;
	m_values0[3] = 0;
	m_values0[4] = 0;
	m_values0[5] = 0;
	m_otherNames.erase(m_otherNames.begin(), m_otherNames.end());
	m_values18[0] = 0;
	m_values18[1] = 0;
	m_values18[2] = 0;
	m_values18[3] = 0;
	m_values18[4] = 0;
	m_values18[5] = 0;

	for (const char *token = ini->getNextTokenOrNull(0); token != 0;
		token = ini->getNextTokenOrNull(0))
	{
		AsciiString value(token);
		m_soundNames.push_back(value);
	}

	MultiIniFieldParse fields;
	fields.add(reinterpret_cast<const FieldParse *>(0x011159E8));
	fields.add(getVoiceFieldParse(), 0x48);
	ini->initFromINIMulti(this, fields);

	if (*(void **)0x00EEF188 != 0)
	{
		unsigned char localA[0x20];
		unsigned char localB[0x1C];
		finish(localA, localB);
	}
}
