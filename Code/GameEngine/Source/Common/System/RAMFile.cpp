// cl: /DNDEBUG /MD /EHsc
// BFME RAMFile methods recovered against the Zero Hour declaration order.
// File has BFME's lock/unlock additions before RAMFile's own overloads.

typedef int Int;
typedef bool Bool;
typedef char Char;
typedef float Real;

#define FALSE false
#define TRUE true
#define NULL 0

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;

    StringBase() : m_data(0) {}
    void releaseBuffer();

public:
    void concat(const T *text, Int length);
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    ~AsciiString() { releaseBuffer(); }

    void concat(const char *text, Int length)
    {
        StringBase<char>::concat(text, length);
    }

    const char *str() const
    {
        return m_data ? m_data->data : "";
    }
};

class File
{
public:
    virtual ~File();
    virtual Bool open(const Char *filename, Int access);
    virtual void close(void);
    virtual Int read(void *buffer, Int bytes) = 0;
    virtual Int write(const void *buffer, Int bytes) = 0;
    virtual Int seek(Int bytes, Int mode) = 0;
    virtual void nextLine(Char *buf, Int bufSize) = 0;
    virtual Bool scanInt(Int &newInt) = 0;
    virtual Bool scanReal(Real &newReal) = 0;
    virtual Bool scanString(AsciiString &newString) = 0;
    virtual Bool print(const Char *format, ...);
    virtual Int size(void);
    virtual Int position(void);
    virtual char *readEntireAndClose(void) = 0;
    virtual File *convertToRAMFile(void) = 0;
    virtual void lock(void);
    virtual void unlock(void);

protected:
    unsigned char m_fileState[0x10];
};

class RAMFile : public File
{
public:
    virtual Bool open(const Char *filename, Int access);
    virtual void close(void);
    virtual Int read(void *buffer, Int bytes);
    virtual Int write(const void *buffer, Int bytes);
    virtual Int seek(Int bytes, Int mode);
    virtual void nextLine(Char *buf, Int bufSize);
    virtual Bool scanInt(Int &newInt);
    virtual Bool scanReal(Real &newReal);
    virtual Bool scanString(AsciiString &newString);
    virtual Bool open(File *file);
    virtual Bool openFromArchive(File *archiveFile, const AsciiString &filename,
                                 Int offset, Int size);
    virtual Bool copyDataToFile(File *localFile);
    virtual char *readEntireAndClose(void);
    virtual File *convertToRAMFile(void);

protected:
    Char *m_data;
    Int m_pos;
    Int m_size;
};

extern "C" __declspec(dllimport) double __cdecl atof(const char *text);

// ?scanReal@RAMFile@@UAE_NAAM@Z
Bool RAMFile::scanReal(Real &newReal)
{
    newReal = 0.0;
    AsciiString tempstr;
    Bool sawDec = FALSE;

    while ((m_pos < m_size) &&
           ((m_data[m_pos] < '0') || (m_data[m_pos] > '9')) &&
           (m_data[m_pos] != '-') && (m_data[m_pos] != '.'))
    {
        ++m_pos;
    }

    if (m_pos >= m_size)
    {
        m_pos = m_size;
        return FALSE;
    }

    do
    {
        Char value[2];
        value[0] = m_data[m_pos];
        tempstr.concat(value, 1);
        if (m_data[m_pos] == '.')
        {
            sawDec = TRUE;
        }
        ++m_pos;
    }
    while ((m_pos < m_size) &&
           (((m_data[m_pos] >= '0') && (m_data[m_pos] <= '9')) ||
            ((m_data[m_pos] == '.') && !sawDec)));

    newReal = (Real)atof(tempstr.str());
    return TRUE;
}
