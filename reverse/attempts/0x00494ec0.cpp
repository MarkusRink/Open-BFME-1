// ?bfmeResetLB@@YAXPAX@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 63/62 bytes -- one OVER. The whole structure matches: a static map object
// addressed by immediate (`mov ecx,offset g_bfmeMapLB`), a find returning a
// pointer-to-slot that is dereferenced, the `and byte ptr [eax+20h],0fch` and
// the zero store, and an erase taking the same &key.
// The two `mov [esp+0ch],esi` self-stores of the parameter into its own home
// slot need the volatile-self-store idiom (see volatile-home-slot-store), and
// both are present here -- but MSVC then RELOADS the parameter for each store
// (`mov eax,[esp+4]` / `mov edx,[esp+4]`) instead of caching it in esi across
// the body the way retail does, which costs the byte.
// Tried: one self-store only (56 bytes, both reload sites gone), and caching
// the value in a plain local first (72 bytes -- the local takes its own slot).
class BfmeEntryLB
{
public:
	unsigned char m_bfmeHeadLB[8];
	int m_bfmeCountLB;
	unsigned char m_bfmeGapLB[0x14];
	unsigned char m_bfmeFlagsLB;
};

class BfmeMapLB
{
public:
	BfmeEntryLB **bfmeFindLB(void **key);
	void bfmeEraseLB(void **key);
};

extern BfmeMapLB g_bfmeMapLB;

void __cdecl bfmeResetLB(void *key)
{
	*(void *volatile *)&key = key;

	BfmeEntryLB *entry = *g_bfmeMapLB.bfmeFindLB(&key);

	if (entry != 0)
	{
		entry->m_bfmeFlagsLB &= 0xfc;
		entry->m_bfmeCountLB = 0;

		*(void *volatile *)&key = key;

		g_bfmeMapLB.bfmeEraseLB(&key);
	}
}
