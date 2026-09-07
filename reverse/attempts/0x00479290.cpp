// ?bfmeRouteXX@BfmeOwnerXX@@QAEXHPAX0@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 67/67 exact size; every instruction present, only the ORDER of the argument
// loads relative to the receiver selection differs -- the [[argument-shuttle-register]]
// preload-depth shape. Retail reads a3 at offset 0 (before any push), pushes it,
// then interleaves the a2/a1 loads and pushes AROUND `mov ecx,[esi+4]` / `test`;
// MSVC does the whole `m_bfmeAXX ? : m_bfmeBXX` selection first and only then
// loads and pushes. Both the named-local form and the inline ternary
// `(m_bfmeAXX != 0 ? m_bfmeAXX : m_bfmeBXX)->bfmeHandleXX(...)` give the same
// MSVC order; /G7 does not move it either.
// Everything else is settled: receiver select on m4 falling back to m8, virtual
// slot 2 with (a1, a2, a3), then `if (a1 == 2 && m_bfmeBXX) { m_bfmeBXX->+0x1dc
// = m_bfmeAXX; m_bfmeBXX = 0; }`.
class BfmeTargetXX
{
public:
	virtual void bfmeV0XX();
	virtual void bfmeV1XX();
	virtual void bfmeHandleXX(int a1, void *a2, void *a3);

	unsigned char m_bfmeHeadXX[0x1d8];
	BfmeTargetXX *m_bfmeBackXX;
};

class BfmeOwnerXX
{
public:
	void bfmeRouteXX(int a1, void *a2, void *a3);

	unsigned char m_bfmeStartXX[4];
	BfmeTargetXX *m_bfmeAXX;
	BfmeTargetXX *m_bfmeBXX;
};

void BfmeOwnerXX::bfmeRouteXX(int a1, void *a2, void *a3)
{
	BfmeTargetXX *target = m_bfmeAXX;

	if (target == 0)
		target = m_bfmeBXX;

	target->bfmeHandleXX(a1, a2, a3);

	if (a1 == 2 && m_bfmeBXX != 0)
	{
		m_bfmeBXX->m_bfmeBackXX = m_bfmeAXX;
		m_bfmeBXX = 0;
	}
}
