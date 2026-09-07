// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Glo00EF3330::h00489410, retail 0x00489410, 90 bytes.
//
// The receiver is TheTransitionHandler at 0x012F3330.  The matched guarded
// caller Rva00382980 names this object and calls h00489410 through the same
// Glo00EF3330 view used by the landed h004893E0 increment sibling.  That
// sibling independently proves the counter at +0x30 and the critical section
// at +0x34.  Retail decrements the counter while holding the section and, on
// the final reference, calls the existing ILT 0x00043C57 to body 0x005A0130.
//
// The local guard is intentional: retail has a real compiler EH region.  Its
// unwind state is zeroed only after EnterCriticalSection, and the handler
// leaves the section if the final-reference helper throws.  An inline guard
// gives that lifetime to the compiler without register forcing or emitted
// assembly.

struct BfmeCriticalSection
{
	unsigned char m_unmodelled_000[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCriticalSection *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCriticalSection *cs);

extern void j_00043c57(void);

typedef int Int;

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(BfmeCriticalSection *section) : m_section(section)
	{
		EnterCriticalSection(m_section);
	}

	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_section);
	}

private:
	BfmeCriticalSection *m_section;
};

class Glo00EF3330
{
public:
	void h00489410(void);

private:
	unsigned char m_unmodelled_000[0x30];
	Int m_count;
	BfmeCriticalSection m_section;
};

void Glo00EF3330::h00489410(void)
{
	CriticalSectionLock lockGuard(&m_section);
	if (--m_count <= 0)
		j_00043c57();
}
