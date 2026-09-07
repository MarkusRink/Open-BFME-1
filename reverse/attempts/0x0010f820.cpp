// ?rva0010f820MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z
// partial score=0.78 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x0010F820 is called through ILT 0x00011B35 with ECX set to
// TheGameState.  Its hidden return slot and one AsciiString reference are
// therefore the GameState-style by-value-string ABI (ret 8).  The original
// public/member spelling is not recovered: this TU deliberately uses an
// address-derived neutral name.
//
// The six path globals are address-derived from the actual retail loads:
// BC/C0/C4 are Save\\, Maps\\, and UserData\\Maps\\, while C8/CC/D0 are
// the one-character route codes S/M/U and D4 is the fallback code X.

extern "C" unsigned int strlen(const char *text);

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

    Header *m_data;

public:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();
    bool startsWithNoCase(const T *text, int length) const;
    void set(const T *text, int length);
    void concat(const T *text, int length);
    void concat(const StringBase<T> &other);
    void toLower();
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other)
        : StringBase<char>(*(const StringBase<char> *)&other) {}
    ~AsciiString() {}

    AsciiString &operator=(const char *text);

    bool startsWithNoCase(const char *text, int length) const
    {
        return StringBase<char>::startsWithNoCase(text, length);
    }

    void set(const char *text, int length)
    {
        StringBase<char>::set(text, length);
    }

    void concat(const char *text, int length)
    {
        StringBase<char>::concat(text, length);
    }

    void concat(const AsciiString &other)
    {
        StringBase<char>::concat(*(const StringBase<char> *)&other);
    }

    void toLower()
    {
        StringBase<char>::toLower();
    }

    const char *str() const
    {
        return m_data ? (const char *)&m_data->data[0] : (const char *)0x0107388B;
    }

};

class GameState
{
public:
    // Original public name unrecovered; neutral address-derived declaration.
    AsciiString rva0010f820MapPathCode(const AsciiString &path) const;
};

static __forceinline const char *rva0010f820String(unsigned int address)
{
    return *(const char *const *)address;
}

AsciiString GameState::rva0010f820MapPathCode(const AsciiString &path) const
{
    AsciiString prefix;

    if (path.startsWithNoCase(
            rva0010f820String(0x012ABFBC),
            rva0010f820String(0x012ABFBC)
                ? (int)strlen(rva0010f820String(0x012ABFBC)) : 0))
    {
        const char *code = rva0010f820String(0x012ABFC8);
        prefix.set(code, code ? (int)strlen(code) : 0);

        const int tailOffset = (int)strlen(rva0010f820String(0x012ABFBC));
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        prefix.concat(tail, tailLength);
    }
    else if (path.startsWithNoCase(
                 rva0010f820String(0x012ABFC0),
                 rva0010f820String(0x012ABFC0)
                     ? (int)strlen(rva0010f820String(0x012ABFC0)) : 0))
    {
        const char *code = rva0010f820String(0x012ABFCC);
        prefix.set(code, code ? (int)strlen(code) : 0);

        const int tailOffset =
            (int)strlen(rva0010f820String(0x012ABFC0));
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        prefix.concat(tail, tailLength);
    }
    else if (path.startsWithNoCase(
                 rva0010f820String(0x012ABFC4),
                 rva0010f820String(0x012ABFC4)
                     ? (int)strlen(rva0010f820String(0x012ABFC4)) : 0))
    {
        prefix = rva0010f820String(0x012ABFD0);
        const int tailOffset =
            (int)strlen(rva0010f820String(0x012ABFC4));
        const char *tail = path.str() + tailOffset;
        const int tailLength = tail ? (int)strlen(tail) : 0;
        prefix.concat(tail, tailLength);
    }
    else
    {
        prefix = rva0010f820String(0x012ABFD4);
        prefix.concat(path);
    }

    prefix.toLower();
    return prefix;
}
