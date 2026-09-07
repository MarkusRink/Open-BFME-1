// cl: /DNDEBUG /MD /EHsc

// The two ControlBar context updates that watch the selected drawable's object:
// the OCL build timer and the under-construction percentage.
//
// They were two files, and each described the same ControlBar from its own
// member outwards. One padded to +0x6C for m_displayedOCLTimerSeconds; the other
// padded to +0x68 for m_displayedConstructPercent. Neither was wrong and neither
// could show that the two fields are adjacent -- a Real at +0x68 followed by an
// UnsignedInt at +0x6C, both of them "what the user was last shown", updated by
// the same shape of test. Declared once, that is visible.
//
// Object was split the same way: one file knew findUpdateModule, the other knew
// the under-construction bit at +0x90 and the construction percent at +0x220.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { LOGICFRAMES_PER_SECOND = 5 };

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate
{
public:
	UnsignedInt getRemainingFrames(void);			// ILT 0x00032AA6
	Real getCountdownPercent(void);				// ILT 0x00047069
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	OCLUpdate *findUpdateModule(NameKeyType key);		// ILT 0x0002AE23

	Real getConstructionPercent(void) const
	{
		return *(const Real *)((const char *)this + 0x220);
	}

	bool testUnderConstruction(void) const
	{
		return (*(const unsigned char *)((const char *)this + 0x90) & 4) != 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject(void) { return m_object; }

private:
	char m_slice_pad[0xFC];					// retail this+0x00 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void updateConstructionTextDisplay(Object *obj);

// Access is load-bearing here: it is part of the mangled name the ledger pins.
// updateContextOCLTimer is ?...@ControlBar@@AAEXXZ -- private -- while
// updateContextUnderConstruction is IAE, protected. Putting both in one section
// renames one of them and the symbol stops existing in the object.
private:
	void updateContextOCLTimer(void);
	void updateOCLTimerTextDisplay(UnsignedInt secondsLeft, Real percentDone);	// ILT 0x00029839

protected:
	void updateContextUnderConstruction(void);
	void evaluateContextUI(void);

	char m_slice_pad[0x5C];					// retail this+0x00 .. +0x5B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x5C
	char m_slice_padB[0x68 - 0x60];				// this+0x60 .. +0x67, untouched
	Real m_displayedConstructPercent;			// this+0x68
	UnsignedInt m_displayedOCLTimerSeconds;			// this+0x6C
};

// Open-BFME: ControlBar::updateContextOCLTimer, retail 0x004AA980, 188 bytes.
//
// The reference's body with a guard around it: BFME checks that the selected
// drawable actually has an object before doing any of the work, which is what
// puts the function-local static's once-flag inside the test rather than at
// the top.
//
// The divisor is five, not the reference's thirty: the reciprocal multiply by
// 0xCCCCCCCD with a shift of two is a divide by five, and a shift of three
// would be the ten it looks like at a glance.
//
// The static key sits at 0x012F3624 behind the initialised-once bit at
// 0x012F3628.

// ?updateContextOCLTimer@ControlBar@@AAEXXZ
void ControlBar::updateContextOCLTimer( void )
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if( obj )
	{
		static const NameKeyType key_OCLUpdate = NAMEKEY( "OCLUpdate" );
		OCLUpdate *update = (OCLUpdate*)obj->findUpdateModule( key_OCLUpdate );

		UnsignedInt frames = update->getRemainingFrames();
		UnsignedInt seconds = frames / LOGICFRAMES_PER_SECOND;

		Real percent = update->getCountdownPercent();

		// if the time has changed since what was last shown to the user update the text
		if( m_displayedOCLTimerSeconds != seconds )
			updateOCLTimerTextDisplay( seconds, percent );
	}

}  // end updateContextOCLTimer

// ControlBar::updateContextUnderConstruction, retail 0x004AF660, 48 bytes.
// Twin: ControlBarUnderConstruction.cpp. BFME inlines the under-construction
// flag as a byte test at Object+0x90 bit 2, and the construction percent as
// the Real at Object+0x220.

// ?updateContextUnderConstruction@ControlBar@@IAEXXZ
void ControlBar::updateContextUnderConstruction(void)
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if (!obj->testUnderConstruction())
	{
		evaluateContextUI();
		return;
	}

	if (m_displayedConstructPercent != obj->getConstructionPercent())
		updateConstructionTextDisplay(obj);
}
