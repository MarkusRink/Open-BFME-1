// ?bfmeLeaveBQ@BfmeHostBQ@@QAEXPAX@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 88/88 at exact size. Every instruction, operand and displacement matches.
// The ONLY difference is the known marker/receiver swap: retail writes
//   mov dword ptr [esp+8],esp   then   mov ecx,esp
// and MSVC emits the two the other way round. See [[marker-precedes-receiver]];
// this is the FOURTH body blocked on it.
// Newly ruled out here on top of that note's list: /EHa (adds a full SEH frame,
// 130 bytes), /EHsc- and /GX (both unchanged at 88).
// Everything else fell out of the standard recipe: a real const char* ctor, an
// INLINE copy ctor, and a destructor declared but not defined, which builds the
// by-value AsciiString straight in the outgoing argument area.
// The literal at 0x0110633C is "MainMenuToBattleSchool".
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &other) { m_bfmeBufBQ = other.m_bfmeBufBQ; }
	~BFMERetailAsciiString();

	char *m_bfmeBufBQ;
};

class Shell40D9
{
public:
	void bfmeCloseBQ();

	unsigned char m_bfmeHeadBQ[0x59];
	unsigned char m_bfmeFlagBQ;
};

extern Shell40D9 *TheShell;

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00BQ();
	virtual void bfmeSlot01BQ();
	virtual void bfmeSlot02BQ();
	virtual void bfmeSlot03BQ();
	virtual void bfmeSlot04BQ();
	virtual void bfmeSlot05BQ();
	virtual void bfmeSlot06BQ();
	virtual void bfmeSlot07BQ();
	virtual void bfmeSlot08BQ();
	virtual void bfmeSlot09BQ();
	virtual void bfmeStopBQ(int mode);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

struct Rva005A00B0Transition
{
	void bfmeStartBQ(BFMERetailAsciiString name);
};

extern Rva005A00B0Transition *TheTransitionHandler;

class BfmeHostBQ
{
public:
	void bfmeLeaveBQ(void *unused);

	unsigned char m_bfmeHeadBQ[0x264];
	int m_bfmeStateBQ;
};

void BfmeHostBQ::bfmeLeaveBQ(void *unused)
{
	if (TheShell != 0)
		TheShell->m_bfmeFlagBQ = 0;

	TheAudioClientUpdate->bfmeStopBQ(8);

	TheTransitionHandler->bfmeStartBQ(BFMERetailAsciiString("MainMenuToBattleSchool"));

	if (TheShell != 0)
		TheShell->bfmeCloseBQ();

	m_bfmeStateBQ = 0;
}
