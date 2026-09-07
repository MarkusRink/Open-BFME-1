// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/stringbaseunicode /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// BFME delegates this assignment to StringBase<wchar_t>::set at 0x00888530.
// The legacy languagefilter adapter emitted UnicodeString::operator= instead.
#include <stddef.h>
#include "Common/UnicodeString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	void setName(UnicodeString name);
private:
	unsigned char m_pad[0x3a0];
	UnicodeString m_gameName;
};

// ?setName@LANGameInfo@@QAEXVUnicodeString@@@Z
void LANGameInfo::setName(UnicodeString name)
{
	m_gameName = name;
}
