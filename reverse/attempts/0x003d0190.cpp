// ?bfmeEnsureRQ@BfmeOwnerRQ@@QAEXPAX@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 70/70 bytes; 9 of 27 instructions differ, by register naming and by where
// `lea edi,[ecx+30h]` lands (retail after the by-value byte is read, ours
// right after the first member load).
// Settled: the search callee is __cdecl with FIVE arguments -- (begin, end,
// &key, a one-byte by-value comparator, 0) -- and that comparator is a 1-byte
// struct built in the `push ecx` slot with `mov byte ptr [esp+0ch],0` and then
// pushed as a whole dword; begin and end must be hoisted into locals so the
// end is still live for `cmp eax,esi` after the call; and the insert is a
// method on the EMBEDDED vector at this+30h taking (found, &key).
// Tried: swapping the begin/end declaration order (same 9).
struct BfmeCmpRQ
{
	char m_bfmeRawRQ;
};

void ** __cdecl bfmeLowerRQ(void **begin, void **end, void **key, BfmeCmpRQ compare, int spare);

class BfmeVecRQ
{
public:
	void bfmeInsertRQ(void **where, void **key);

	void **m_bfmeBeginRQ;
	void **m_bfmeEndRQ;
};

class BfmeOwnerRQ
{
public:
	void bfmeEnsureRQ(void *key);

	unsigned char m_bfmeHeadRQ[0x30];
	BfmeVecRQ m_bfmeVecRQ;
};

void BfmeOwnerRQ::bfmeEnsureRQ(void *key)
{
	void **begin = m_bfmeVecRQ.m_bfmeBeginRQ;
	void **end = m_bfmeVecRQ.m_bfmeEndRQ;
	BfmeCmpRQ compare;

	compare.m_bfmeRawRQ = 0;

	void **found = bfmeLowerRQ(begin, end, &key, compare, 0);

	if (found == end || *found != key)
		m_bfmeVecRQ.bfmeInsertRQ(found, &key);
}
