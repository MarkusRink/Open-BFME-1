// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define __ARCHIVEFILESYSTEM_H_
#include "Common/SubsystemInterface.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

// Retail inlines AsciiString's forwarding constructor and calls its StringBase body.
template <typename T>
class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &src);
    void *m_data;
};

__forceinline AsciiString::AsciiString(const AsciiString &src)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(
        *(const StringBase<char> *)&src);
}

class DetailedArchivedDirectoryInfo;
class ArchivedFileInfo
{
public:
    AsciiString m_filename;
    AsciiString m_archiveFilename;
    UnsignedInt m_offset;
    UnsignedInt m_size;
};

typedef std::map<AsciiString, DetailedArchivedDirectoryInfo> DetailedArchivedDirectoryInfoMap;
typedef std::map<AsciiString, ArchivedFileInfo> ArchivedFileInfoMap;

// The matched copy body at 0x009D0DB0 copies the name and maps at +0, +4 and +0x10.
// Keep its declaration local so shared directory-map inlining is unaffected.
class DetailedArchivedDirectoryInfo
{
public:
    DetailedArchivedDirectoryInfo(const DetailedArchivedDirectoryInfo &);
    AsciiString m_directoryName;
    DetailedArchivedDirectoryInfoMap m_directories;
    ArchivedFileInfoMap m_files;
};

// Retail 0x009D0EC0 constructs the key, then calls the Detailed copy body at this+4.
template std::pair<const AsciiString, DetailedArchivedDirectoryInfo>::pair(
    const AsciiString &, const DetailedArchivedDirectoryInfo &);
