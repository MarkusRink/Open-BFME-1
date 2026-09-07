// ?bfmeRemoveAQ@BfmeOwnerAQ@@QAEXPAVBfmeItemAQ@@@Z (identity unknown)
// partial score=0.92 date=2026-09-07
// 99/101. find the object in the vector at +0x17628/+0x1762c, delete it and
// memmove the tail down. Two residues, both compiler choices:
//   * retail leas the argument slot TWICE (lea eax,[esp+0x14] / push /
//     lea ecx,[esp+0x18]); MSVC CSEs the second into `mov ecx,eax` -- the 2
//     missing bytes. Tried differentiating the two argument TYPES (const T*const*
//     vs void*/const void*/const char*) and an offset cast; the CSE always fires.
//   * this lands in esi, not edi (and the esi/edi pushes swap with it).
// What IS recovered and worth reusing: `delete obj` on the PARAMETER reloads it
// from the home slot and re-null-checks it (4 extra bytes), because &obj was
// handed to an opaque callee. Copying the parameter into a local first and
// deleting the local removes both -- and `BfmeItemAQ *const obj` does NOT
// (the const parameter still reloads, and cost 4 bytes more).
extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

class BfmeItemAQ
{
public:
	virtual ~BfmeItemAQ();
};

extern "C" BfmeItemAQ **__cdecl bfmeFindAQ(BfmeItemAQ **first, BfmeItemAQ **last, BfmeItemAQ **value, BfmeItemAQ **hint);

class BfmeOwnerAQ
{
public:
	void bfmeRemoveAQ(BfmeItemAQ *obj);

	unsigned char m_bfmeHeadAQ[0x17628];
	BfmeItemAQ **m_bfmeBeginAQ;
	BfmeItemAQ **m_bfmeEndAQ;
};

void BfmeOwnerAQ::bfmeRemoveAQ(BfmeItemAQ *obj)
{
	BfmeItemAQ *o = obj;

	if (o == 0)
		return;

	BfmeItemAQ **last = m_bfmeEndAQ;
	BfmeItemAQ **it = bfmeFindAQ(m_bfmeBeginAQ, last, &obj, &obj);

	if (it == last)
		return;

	delete o;

	BfmeItemAQ **next = it + 1;

	if (m_bfmeEndAQ != next)
		BfmeMemMove(it, next, (char *)m_bfmeEndAQ - (char *)next);

	m_bfmeEndAQ--;
}
