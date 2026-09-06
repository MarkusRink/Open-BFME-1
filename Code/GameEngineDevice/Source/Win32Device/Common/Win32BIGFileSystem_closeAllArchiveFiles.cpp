// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Win32BIGFileSystem::closeAllArchiveFiles, retail 0x009CD780, 261 bytes --
// vtable slot 4 of 0x01143B40.
//
// Its own translation unit because it needs exceptions: it opens with the
// fs:[0] prologue, where closeArchiveFile next door has no SEH frame at all.
// Two methods of one class cannot disagree about that inside a TU.
//
// Zero Hour's closeAllArchiveFiles is an empty body -- BFME wrote this one. The
// shape is readable straight off the disassembly: walk the archive map calling
// ArchiveFile slot 5 (getName, which returns by value, hence the return-slot
// push at 0x009CD7C5), collect the names into a vector, then walk the vector
// calling this->slot 3 with each -- and slot 3 is closeArchiveFile, matched next
// door. Collecting first is not incidental: closeArchiveFile erases from the map
// it would otherwise be iterating.

#include "Common/AsciiString.h"
#include <map>
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();							// slot 0
	virtual void A1() = 0;
	virtual void A2() = 0;
	virtual void A3() = 0;
	virtual void A4() = 0;
	// slot 5 = +0x14
	virtual AsciiString getName( void ) = 0;
};

typedef char Char;
typedef int Int;
typedef int Bool;

typedef std::map<AsciiString, ArchiveFile *> ArchiveFileMap;

class File;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename ) = 0;		// slot 2
	virtual void closeArchiveFile( const Char *filename ) = 0;				// slot 3
	virtual void closeAllArchiveFiles( void );								// slot 4

protected:
	ArchiveFileMap m_archiveFileMap;	// +0x04
};

// The vector<AsciiString> COMDAT this TU reaches is the copy at 0x00063700 --
// the one whose element copy calls StringBase<char>'s constructor out of line,
// which 38 retail sites encode -- not the inlined-copy twin at 0x00757C70. No
// pin can bridge the two (pin_consistency: divergent-bodies at +0x77), so spell
// the element with the name the ledger carries at 0x00063700.
class Open2Elem063700
{
public:
	Open2Elem063700( const Open2Elem063700 &source )
	{
		((AsciiString *)this)->AsciiString::AsciiString( *(const AsciiString *)&source );
	}

	~Open2Elem063700()
	{
		((AsciiString *)this)->AsciiString::~AsciiString();
	}

private:
	void *m_text;
};

// A reference cast, so the caller's temporary still dies at the end of its own
// full expression rather than at the end of the block.
static const Open2Elem063700 &asElement( const AsciiString &s )
{
	return *(const Open2Elem063700 *)&s;
}

// ?closeAllArchiveFiles@Win32BIGFileSystem@@UAEXXZ
void Win32BIGFileSystem::closeAllArchiveFiles( void )
{
	std::vector<Open2Elem063700> names;

	ArchiveFileMap::iterator it = m_archiveFileMap.begin();
	while (it != m_archiveFileMap.end()) {
		names.push_back( asElement( it->second->getName() ) );
		++it;
	}

	std::vector<Open2Elem063700>::iterator n = names.begin();
	while (n != names.end()) {
		closeArchiveFile( ((const AsciiString *)&*n)->str() );
		++n;
	}
}
