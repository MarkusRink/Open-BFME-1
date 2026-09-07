// cl: /DNDEBUG /MD /EHsc

#include <stdio.h>

class AsciiString;
template <typename T>
class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &);
    ~StringBase();
    void concat(const T *, int);
    void *m_data;
};

// The retail call sites inline these wrappers around the private char base.
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void concat(const char *text, int length) { StringBase<char>::concat(text, length); }
    const char *str() const { return m_data ? static_cast<const char *>(m_data) + 8 : ""; }
};

class GlobalData
{
public:
    AsciiString getPath_UserData() const;
};
extern GlobalData *TheGlobalData;

class Mapping;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents()
        : m_list(0), m_listLength(0), m_nextID(1), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
private:
    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class OutputStream;
class OutputChunk;
// The retail stores agree with the reference writer layout through m_chunkStack (+0x18).
class DataChunkOutput
{
public:
    DataChunkOutput(OutputStream *output);
private:
    OutputStream *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};

// The reference temporary-file constructor agrees with retail getter 0x000106EA
// and its narrow-string concat/release calls; no named direct caller is recovered.
// ??0DataChunkOutput@@QAE@PAVOutputStream@@@Z
DataChunkOutput::DataChunkOutput(OutputStream *output) : m_pOut(output)
{
    AsciiString temporaryFileName = TheGlobalData->getPath_UserData();
    temporaryFileName.concat("_tmpChunk.dat", 13);
    m_tmp_file = fopen(temporaryFileName.str(), "wb");
    m_chunkStack = 0;
}
