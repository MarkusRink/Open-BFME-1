// ?bfmeFindPV@BfmeMapPV@@QAEPAXPAX@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 57/57 bytes; every instruction matches. The only difference is where the
// shared `xor eax,eax; pop ecx; ret 4` block sits: retail puts it immediately
// after the null guard (`test eax,eax; jne body`) so the guard falls THROUGH
// into it and the not-found case jumps BACKWARD to it; MSVC lays the body out
// first and puts the block at the end.
// Settled: the table is an embedded member at this+27ch (lea, not a pointer),
// the lookup takes &found and &key -- &key being the parameter's own home slot
// -- and the result is compared against the table's first member.
// 0x006128A0 is the 57-byte twin of this body and will need the same fix.
class BfmeNodePV
{
public:
	unsigned char m_bfmeHeadPV[0x14];
	void *m_bfmeValuePV;
};

class BfmeTablePV
{
public:
	void bfmeLookupPV(BfmeNodePV **found, void **key);

	BfmeNodePV *m_bfmeEndPV;
};

class BfmeMapPV
{
public:
	void *bfmeFindPV(void *key);

	unsigned char m_bfmeHeadPV[0x27c];
	BfmeTablePV m_bfmeTablePV;
};

void *BfmeMapPV::bfmeFindPV(void *key)
{
	if (!key)
		return 0;

	BfmeNodePV *found;

	m_bfmeTablePV.bfmeLookupPV(&found, &key);

	if (found == m_bfmeTablePV.m_bfmeEndPV)
		return 0;

	return found->m_bfmeValuePV;
}
