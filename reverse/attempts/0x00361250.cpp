// ?bfmeSelectBV@BfmeHostBV@@QAEXPAVBfmeTargetBV@@H@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 113/113 at exact size. Every instruction and operand matches; the only
// difference is that retail puts the index in esi and the begin pointer in edi
// (pushing esi second, edi third) while MSVC picks the opposite pair.
// Two things WERE settled here and are worth reusing:
//   * the magic-multiply divisor tells you sizeof(element) exactly. Retail's
//     `mov eax,0x2e8ba2e9 / imul edx / sar edx,4` is /0x58; my first struct was
//     0x5c and produced a completely different magic plus an extra add. If the
//     magic constant does not match, fix the STRUCT SIZE before anything else.
//   * `ja` after a preceding `test/jl` on the same value means the source wrote
//     an UNSIGNED compare -- `(unsigned)index > (unsigned)(end - begin)`.
//     Spelling it signed gives `jg` and two extra bytes.
// Tried for the register swap: naming end/begin as locals in retail's load
// order, and copying the index parameter into a local. Both identical.
class BfmeResBV
{
public:
	void bfmeApplyBV(int value);
};

class BfmeTargetBV
{
public:
	virtual void bfmeSlot00BV();
	virtual void bfmeSlot01BV();
	virtual void bfmeSlot02BV();
	virtual void bfmeSlot03BV();
	virtual void bfmeSlot04BV();
	virtual void bfmeSlot05BV();
	virtual void bfmeSlot06BV();
	virtual void bfmeSlot07BV();
	virtual void bfmeSlot08BV();
	virtual void bfmeSlot09BV();
	virtual BfmeResBV *bfmeGetBV();

	void bfmeMarkBV(int index);
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadBV[0x218];
	int m_bfmeModeBV;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class BfmeEntryBV
{
public:
	unsigned char m_bfmeHeadBV[0x18];
	int m_bfmeMainBV;
	int m_bfmeAltBV;
	unsigned char m_bfmeTailBV[0x38];
};

class BfmeHostBV
{
public:
	void bfmeSelectBV(BfmeTargetBV *t, int index);

	unsigned char m_bfmeHeadBV[0x18];
	BfmeEntryBV *m_bfmeBeginBV;
	BfmeEntryBV *m_bfmeEndBV;
};

void BfmeHostBV::bfmeSelectBV(BfmeTargetBV *t, int index)
{
	if (t == 0)
		return;

	if (index < 0)
		return;

	BfmeEntryBV *end = m_bfmeEndBV;
	BfmeEntryBV *begin = m_bfmeBeginBV;

	if ((unsigned int)index > (unsigned int)(end - begin))
		return;

	BfmeEntryBV *e = &begin[index];
	int value;

	if (TheWritableGlobalData->m_bfmeModeBV == 4)
		value = e->m_bfmeAltBV;
	else
		value = e->m_bfmeMainBV;

	BfmeResBV *r = t->bfmeGetBV();

	if (r == 0)
		return;

	r->bfmeApplyBV(value);
	t->bfmeMarkBV(index);
}
