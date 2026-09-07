// ?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z
// partial score=0.72 date=2026-09-07
// Scratch reconstruction for GameState::getSaveGameInfoFromFile at 0x00111980.
// This is deliberately outside Code while the BFME-only ABI is measured.
// The local views follow the matched GameState ctor, Gen009D8CA0 reader, and
// the retail Xfer vtable; no retail bytes are embedded here.
// cl: /DNDEBUG /MD /EHsc /O2 /Ireference/shims/sweep

typedef bool Bool;
typedef unsigned short UnsignedShort;

template <typename T> class StringBase
{
    template <typename U> friend class StringBase;
    friend class AsciiString;
    friend class UnicodeString;

    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };

    Header *m_data;

public:
    StringBase() : m_data(0) {}
    StringBase(const StringBase &other);
    ~StringBase();
    void set(const StringBase &other);
    int compareNoCase(const T *text) const;
    void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    bool isEmpty() const
    {
        return m_data == 0 || m_data->length == 0;
    }

    const char *str() const
    {
        return m_data ? m_data->text : "";
    }

    int compareNoCase(const char *text) const
    {
        return StringBase<char>::compareNoCase(text);
    }

    AsciiString &operator=(const AsciiString &other)
    {
        StringBase<char>::set(other);
        return *this;
    }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}

    UnicodeString &operator=(const UnicodeString &other)
    {
        StringBase<unsigned short>::set(other);
        return *this;
    }
};

struct SaveDate
{
    UnsignedShort year;
    UnsignedShort month;
    UnsignedShort day;
    UnsignedShort dayOfWeek;
    UnsignedShort hour;
    UnsignedShort minute;
    UnsignedShort second;
    UnsignedShort milliseconds;
};

class SaveGameInfo
{
public:
    SaveGameInfo();
    ~SaveGameInfo();
    SaveGameInfo &operator=(const SaveGameInfo &other);

    AsciiString saveGameMapName;
    AsciiString pristineMapName;
    AsciiString mapLabel;
    SaveDate date;
    AsciiString campaignSide;
    int missionNumber;
    UnicodeString description;
    int saveFileType;
    AsciiString missionMapName;
};

class File
{
public:
    virtual ~File();
    virtual Bool open(const char *, int);
    virtual void close();
    virtual int read(void *, int);
    virtual int write(const void *, int);
    virtual int seek(int, int);
    virtual void nextLine(char *, int);
    virtual Bool scanInt(int &);
    virtual Bool scanReal(float &);
    virtual Bool scanString(void *);
    virtual Bool print(const char *, ...);
    virtual int size();
    virtual int position();
    virtual char *readEntireAndClose();
    virtual File *convertToRAMFile();
    virtual void lock();
    virtual void unlock();
};

class FileSystem
{
public:
    File *openFile(const char *filename, int access);
};

extern FileSystem *TheFileSystem;

class Snapshot;

class Gen009D8CA0
{
public:
    Gen009D8CA0(int first, int second, int third);
    ~Gen009D8CA0();
    Bool readAt009D89E0(File *file, void *output);

    virtual void slot00();
    virtual Bool slot01();
    virtual Bool slot02();
    virtual Bool slot03();
    virtual Bool slot04();
    virtual int beginBlock(const char *name);
    virtual void endBlock();
    virtual void skipBlock(const char *name);
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void xferSnapshot(Snapshot *snapshot);
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void xferAsciiString(AsciiString *value);

private:
    unsigned char m_data[0x1c];
};

class Rva009D8AA0
{
public:
    void apply();

private:
    unsigned char m_pad[0x14];
    void *m_stream;
};

class Snapshot
{
public:
    virtual ~Snapshot();
    virtual void crc(void *xfer);
    virtual void xfer(void *xfer);
    virtual void loadPostProcess();
};

enum SnapshotType
{
    SNAPSHOT_SAVELOAD,
    SNAPSHOT_DEEPCRC_LOGICONLY,
    SNAPSHOT_DEEPCRC,
    SNAPSHOT_MAX
};

struct SnapshotBlock
{
    Snapshot *snapshot;
    AsciiString blockName;
};

class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
    virtual void init();
    virtual void reset();
    virtual void update();

private:
    void *m_name;
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
    GameState();
    virtual ~GameState();
    void getSaveGameInfoFromFile(AsciiString filename, SaveGameInfo *saveGameInfo);
    SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);
    SaveGameInfo *getSaveGameInfo() { return &m_gameInfo; }

private:
    unsigned char m_snapshotLists[0x0c];
    SaveGameInfo m_gameInfo;
    unsigned char m_tail[0x10];
};

struct BfmeFormattedText
{
    char *text;
    int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
    BfmeFormattedText *result, int tag, const char *format, ...);
extern "C" int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern "C" int __cdecl _stricmp(const char *, const char *);

static const char *SAVE_FILE_EOF = "SG_EOF";

// ?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z
void GameState::getSaveGameInfoFromFile(AsciiString filename, SaveGameInfo *saveGameInfo)
{
    Bool done = false;
    BfmeFormattedText error;

    if (filename.isEmpty() || saveGameInfo == 0)
        return;

    File *file = TheFileSystem->openFile(filename.str(), 0x41);
    if (file == 0)
        return;

    Gen009D8CA0 xfer(0, 0, 0);
    int version;
    if (!xfer.readAt009D89E0(file, &version))
    {
        file->close();
        return;
    }

    if (version > 1)
    {
        file->close();
        return;
    }

    while (!done)
    {
        AsciiString token;
        xfer.xferAsciiString(&token);
        if (token.compareNoCase(SAVE_FILE_EOF) == 0)
        {
            done = true;
        }
        else
        {
            try
            {
                if (findBlockInfoByToken(token, SNAPSHOT_SAVELOAD) == 0)
                {
                    bfmeFormatText(&error, 0, 0);
                    _CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
                }

                if (_stricmp(token.str(), "CHUNK_GameState") == 0)
                {
                    GameState tempGameState;
                    xfer.beginBlock("?");
                    xfer.xferSnapshot(&tempGameState);
                    xfer.endBlock();
                    *saveGameInfo = *tempGameState.getSaveGameInfo();
                    done = true;
                }
                else
                {
                    xfer.skipBlock("?");
                }
            }
            catch (...)
            {
                throw;
            }
        }
    }

    reinterpret_cast<Rva009D8AA0 *>(&xfer)->apply();
    file->close();
}
