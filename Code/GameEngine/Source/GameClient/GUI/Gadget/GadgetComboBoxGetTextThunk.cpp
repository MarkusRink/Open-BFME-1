// cl: /DNDEBUG /MD /EHsc /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// Return the combo box's edit-field text, or the empty string.
//
// The body is the one GadgetComboBox.cpp already carried; only the flavour of
// UnicodeString differs. GadgetComboBox.cpp resolves Common/UnicodeString.h to
// the Zero Hour header, whose copy constructor is out of line and mangles to
// ??0UnicodeString@@QAE@ABV0@@Z. Retail's `return UnicodeString::TheEmptyString`
// encodes 0x00888400 = ??0?$StringBase@G@@AAE@ABV0@@Z instead: BFME's string
// body lives on StringBase<WideChar> with UnicodeString as its friend, and the
// forwarding copy constructor is inlined at the call site. The languagefilter
// shim above is the header that spells that delegation, so this TU emits the
// base call retail made; the private /I keeps it out of GadgetComboBox.cpp.
#include "Common/UnicodeString.h"

typedef int Int;

enum { GWS_COMBO_BOX = 0x00008000 };	// GameClient/Gadget.h

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetComboBox.h
struct ComboBoxData
{
	unsigned char m_head[0x28];
	GameWindow *m_entry;
	GameWindow *m_listBox;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt winGetStyle(void);
	void *winGetUserData(void);
};

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

// ?GadgetComboBoxGetText@@YA?AVUnicodeString@@PAVGameWindow@@@Z
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox)
{

	// sanity
	if (comboBox == NULL)
		return UnicodeString::TheEmptyString;

	// verify that this is a combo box
	if (BitTest(comboBox->winGetStyle(), GWS_COMBO_BOX) == FALSE)
		return UnicodeString::TheEmptyString;

	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	return GadgetTextEntryGetText(
		comboBoxData && comboBoxData->m_entry ? comboBoxData->m_entry : NULL);
}
