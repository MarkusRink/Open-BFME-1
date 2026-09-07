// ?bfmeGetNH@BfmeOwnerNH@@QAEPAXPAX@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 51/51 bytes; 6 of 17 instructions differ, by register and argument-evaluation
// order only.
// Settled: the table guard, the -1 sentinel test written POSITIVELY
// (`if (index != -1) return m_table[index]; return 0;` so the shared xor lands
// last), the member re-read for the indexed load, and the set address written
// INLINE in the call -- hoisting it into a local turns retail's
// `lea edx,[ecx+2b0h]` into `add eax,2b0h` and loses a byte.
// Residue: retail evaluates the first argument (the set address) before
// loading the key, MSVC loads the key first (right-to-left), and the table
// register comes out edx instead of ecx. Naming the holder pointer is much
// worse (16 diffs).
struct BfmeSetNH
{
	unsigned char m_bfmeRawNH[4];
};

class BfmeHolderNH
{
public:
	unsigned char m_bfmeHeadNH[0x2b0];
	BfmeSetNH m_bfmeSetNH;
};

int __stdcall bfmeFindNH(BfmeSetNH *set, void *key);

class BfmeOwnerNH
{
public:
	void *bfmeGetNH(void *key);

	int m_bfmeSpareNH;
	BfmeHolderNH *m_bfmeHolderNH;
	unsigned char m_bfmeGapNH[0x30];
	void **m_bfmeTableNH;
};

void *BfmeOwnerNH::bfmeGetNH(void *key)
{
	if (m_bfmeTableNH == 0)
		return 0;

	int index = bfmeFindNH(&m_bfmeHolderNH->m_bfmeSetNH, key);

	if (index != -1)
		return m_bfmeTableNH[index];

	return 0;
}
