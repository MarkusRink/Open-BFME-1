// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The BFME command button stores image names at +0x94 and resolved images at
// +0x138. ControlBar::init calls this method while it walks its button list.

#include <functional>
#include "PreRTS.h"
#include "Common/STLTypedefs.h"

class BFMERetailAsciiString
{
public:
	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}

	void releaseBuffer();

private:
	void *m_data;
};

struct AsciiStringVector
{
	BFMERetailAsciiString *m_begin;
	BFMERetailAsciiString *m_finish;
	BFMERetailAsciiString *m_capacity;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

class CommandButton
{
public:
	void cacheButtonImage();

private:
	unsigned char m_unmodelled_00[0x94];
	AsciiStringVector m_buttonImageNames;
	unsigned char m_unmodelled_0a0[0x98];
	std::vector<const Image *> m_buttonImages;
};

// ?cacheButtonImage@CommandButton@@QAEXXZ
void CommandButton::cacheButtonImage()
{
	if (TheMappedImageCollection == 0)
		return;

	for (BFMERetailAsciiString *name = m_buttonImageNames.m_begin;
			name != m_buttonImageNames.m_finish; ++name)
	{
		if (name->isNotEmpty())
		{
			m_buttonImages.push_back(TheMappedImageCollection->findImageByName(
				*(const AsciiString *)name));
			name->releaseBuffer();
		}
	}
}
