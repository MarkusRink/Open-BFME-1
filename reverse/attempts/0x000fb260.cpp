// ??0BfmeOwnCC@@QAE@PAX@Z (identity unknown)
// partial score=0.91 date=2026-09-06
// 83/91 at exact size. SEH constructor: pinned vftable, a 12-byte member at
// +4 zeroed by its own ctor (one unwind state), the parameter stored at +0x10,
// then a two-argument call on that member with its own first two fields.
// Naming the member in a `BfmeSubCC *sub = &m_bfmeSubCC;` local is what makes
// MSVC read the arguments late through ecx instead of hoisting one through
// esi (seven diffs down to three).
// Residue: retail emits `mov [esp+4], esi` -- the EH this-slot store -- AFTER
// the first two member stores; MSVC emits it before them. Same residue as
// 0x0034C5E0; SEH *destructors* do not show it (0x004762D0 was exact).
class BfmeSubCC
{
public:
	BfmeSubCC(void)
	{
		m_bfmeACC = 0;
		m_bfmeBCC = 0;
		m_bfmeCCC = 0;
	}
	~BfmeSubCC();

	void bfmeInitCC(int first, int second);

	int m_bfmeACC;
	int m_bfmeBCC;
	int m_bfmeCCC;
};

class BfmeOwnCC
{
public:
	BfmeOwnCC(void *value);
	virtual void bfmePureCC(void) = 0;

	BfmeSubCC m_bfmeSubCC;
	void *m_bfmeValueCC;
};

BfmeOwnCC::BfmeOwnCC(void *value)
{
	m_bfmeValueCC = value;

	BfmeSubCC *sub = &m_bfmeSubCC;

	sub->bfmeInitCC(sub->m_bfmeACC, sub->m_bfmeBCC);
}
