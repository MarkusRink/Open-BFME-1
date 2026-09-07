// ?bfmeBindCP@BfmeHostCP@@QAEXPAX0@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 115/103. Structure, both registry calls, the 12-byte zeroed box passed by
// address, and the tail slot-20 call all match.
// The 12 bytes are ONE decision: retail materialises the zero once and reuses
// it five times -- `xor ecx,ecx` then two `push ecx` for the literal arguments
// and three `mov [esp+N],ecx` for the box -- 16 bytes. MSVC uses immediates
// everywhere: two `push 0` plus three 8-byte `mov dword ptr [esp+N],0` = 28.
// Tried: a named `int zero = 0;` feeding both the box fields and the two
// literal arguments. Identical output; MSVC folds it straight back.
// See [[zero-materialisation-is-unstable]] -- the same decision went the OTHER
// way on 0x0058D930, so it is not a fixed direction to compensate for.
class BfmeEntryCP;

struct BfmeBoxCP
{
	int m_bfmeACP;
	int m_bfmeBCP;
	int m_bfmeCCP;
};

class BfmeItemCP
{
public:
	virtual void bfmeSlot00CP();
	virtual void bfmeSlot01CP();
	virtual void bfmeSlot02CP();
	virtual void bfmeSlot03CP();
	virtual void bfmeSlot04CP();
	virtual void bfmeSlot05CP();
	virtual void bfmeSlot06CP();
	virtual void bfmeSlot07CP();
	virtual void bfmeSlot08CP();
	virtual void bfmeSlot09CP();
	virtual void bfmeSlot10CP();
	virtual void bfmeSlot11CP();
	virtual void bfmeSlot12CP();
	virtual void bfmeSlot13CP();
	virtual void bfmeSlot14CP();
	virtual void bfmeSlot15CP();
	virtual void bfmeSlot16CP();
	virtual void bfmeSlot17CP();
	virtual void bfmeSlot18CP();
	virtual void bfmeSlot19CP();
	virtual void bfmeApplyCP(int value);

	void bfmeAimCP(void *at);
};

struct Rva0020AA00Registry
{
	BfmeEntryCP *bfmeFindCP(void *key);
	BfmeItemCP *bfmeMakeCP(BfmeEntryCP *entry, int mode, BfmeBoxCP *box, int flag);
};

extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

class BfmeUnitCP
{
public:
	unsigned char m_bfmeHeadCP[0x23c];
	int m_bfmeValCP;
};

class BfmeHostCP
{
public:
	void bfmeBindCP(void *first, void *second);

	unsigned char m_bfmeHeadCP[8];
	BfmeUnitCP *m_bfmeUnitCP;
};

void BfmeHostCP::bfmeBindCP(void *first, void *second)
{
	BfmeEntryCP *e = Rva0020AA00TheRegistry->bfmeFindCP(second);

	if (e == 0)
		return;

	BfmeBoxCP box;

	box.m_bfmeACP = 0;
	box.m_bfmeBCP = 0;
	box.m_bfmeCCP = 0;

	BfmeItemCP *it = Rva0020AA00TheRegistry->bfmeMakeCP(e, 0, &box, 0);

	if (it == 0)
		return;

	it->bfmeAimCP(first);
	it->bfmeApplyCP(m_bfmeUnitCP->m_bfmeValCP);
}
