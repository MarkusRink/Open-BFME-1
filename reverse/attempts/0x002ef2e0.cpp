// ?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z
// partial score=0.95 date=2026-09-08
// Retail is 30 bytes. This clean C++ produces the exact first 19 bytes through
// the bool-to-int conversion and vtable load, then spills/reloads the volatile
// local before the three pushes (38 bytes total). Without volatile, VC7.1
// schedules TheAudio first and produces 28/32-byte register-mirrored bodies.
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ScriptActions::doAmbientSoundsPause, retail 0x002EF2E0, 30 bytes.

typedef bool Bool;
typedef int Int;


class AudioManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void setAmbientEnabled(Int unused, Int immediate, Int enabled) = 0;
};

extern AudioManager *TheAudio;

class ScriptActions
{
protected:
	void doAmbientSoundsPause(Bool pausing);
};

// ?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z
void ScriptActions::doAmbientSoundsPause(Bool pausing)
{
	volatile Int enabled = !pausing;
	TheAudio->setAmbientEnabled(0, 1, enabled);
}
