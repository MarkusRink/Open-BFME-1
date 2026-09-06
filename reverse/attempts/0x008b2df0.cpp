// ??1BfmeOwnCV@@QAE@XZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 97 bytes exact, structure recovered. Modelling notes worth reusing:
//  - the two vftable stores are NOT compiler-generated: model the class as
//    non-polymorphic with an explicit `int *m_vf` member, the derived value
//    written in the body and the base value written by the base's inline
//    destructor. A real virtual hierarchy puts the vfptr store first, where
//    retail has it after two member stores.
//  - the member stores must be volatile or MSVC sinks them past the notify
//    call (eight diffs instead of fourteen).
// Residue: the EH this-slot store `mov [esp+8],esi` lands before `xor ebx,ebx`
// in MSVC and after it in retail, and one push is ordered differently as a
// consequence. Same this-slot residue as the SEH constructors.
// notify is ?notify@Q4Base00D35D68@@QAEXHH@Z, so the base class name is
// forced; its vftable is 0x01135D68 and the derived one 0x01136058.
extern "C" int _bfmeVftCVa[];
extern "C" int _bfmeVftCVb[];

class Q4Base00D35D68
{
public:
	~Q4Base00D35D68(void)
	{
		m_bfmeVfCV = _bfmeVftCVb;
	}

	void notify(int first, int second);

	int *volatile m_bfmeVfCV;
	unsigned char m_bfmeHeadCV[4];
};

class BfmeMemCV
{
public:
	~BfmeMemCV();

	unsigned char m_bfmeHeadCV[0x10];
};

class BfmeOwnCV : public Q4Base00D35D68
{
public:
	~BfmeOwnCV(void);

	BfmeMemCV m_bfmeMemCV;
	volatile int m_bfmeCCV;
	unsigned char m_bfmePadCV[4];
	volatile int m_bfmeACV;
	volatile int m_bfmeBCV;
};

BfmeOwnCV::~BfmeOwnCV(void)
{
	m_bfmeACV = 0;
	m_bfmeBCV = 0;

	m_bfmeVfCV = _bfmeVftCVa;

	notify(0, 0);

	m_bfmeCCV = 0;
}
