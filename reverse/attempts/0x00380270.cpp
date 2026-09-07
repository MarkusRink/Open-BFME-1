// ?bfmeInsertERQ@BfmeHostERQ@@QAEXPAVBfmeItemERQ@@@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 100/104. Hash-bucket walk keyed by nameToKey on the item name, then a
// cdecl call taking (node+8, item). Every instruction matches; the only
// difference is how the parameter is kept alive across the body:
//   retail  reloads it twice from its home slot -- mov eax,[esp+4] at the
//           top for the name, mov ecx,[esp+4] at the bottom for the call
//   MSVC    caches it in ebx: push ebx / mov ebx,[esp+8] / ... / push ebx
// That is 4 bytes short. ebx is free in both builds (retail uses only esi
// for this and edi for the bucket count), so this is an allocator choice.
// Ruled out: declaring the parameter volatile -- MSVC 13.10 does NOT drop a
// top-level volatile from the parameter mangling, so the symbol no longer
// matches PAVBfmeItemERQ@@ and explain_mismatch fails with "symbol not found
// in object". Any fix must leave the mangled name alone.
// Supersedes the earlier identity-only block.
// Pins are already in symbols.csv.
extern char g_bfmeEmptyERQ[];

struct BfmeStrDataERQ
{
	int m_bfmeRefERQ;
	int m_bfmeLenERQ;
	char m_bfmeTextERQ[1];
};

class BfmeItemERQ
{
public:
	const char *bfmeNameERQ() const
	{
		return m_bfmeNameDataERQ ? m_bfmeNameDataERQ->m_bfmeTextERQ : g_bfmeEmptyERQ;
	}

	unsigned char m_bfmeHeadERQ[0xc];
	BfmeStrDataERQ *m_bfmeNameDataERQ;
};

class BfmeKeyGenERQ
{
public:
	unsigned int bfmeNameToKeyERQ(const char *name);
};

extern BfmeKeyGenERQ *g_bfmeKeyGenERQ;

class BfmeNodeERQ
{
public:
	BfmeNodeERQ *m_bfmeNextERQ;
	unsigned int m_bfmeKeyERQ;
	unsigned char m_bfmeBodyERQ[4];
};

void bfmeAddERQ(void *slot, BfmeItemERQ *item);

class BfmeHostERQ
{
public:
	void bfmeInsertERQ(BfmeItemERQ *item);

	unsigned char m_bfmeHeadERQ[0xc];
	BfmeNodeERQ **m_bfmeFirstERQ;
	BfmeNodeERQ **m_bfmeLastERQ;
};

void BfmeHostERQ::bfmeInsertERQ(BfmeItemERQ *item)
{
	unsigned int key = g_bfmeKeyGenERQ->bfmeNameToKeyERQ(item->bfmeNameERQ());
	unsigned int count = (unsigned int)(m_bfmeLastERQ - m_bfmeFirstERQ);

	BfmeNodeERQ *node = m_bfmeFirstERQ[key % count];

	while (node != 0)
	{
		if (node->m_bfmeKeyERQ == key)
			break;

		node = node->m_bfmeNextERQ;
	}

	if (node == 0)
		return;

	bfmeAddERQ(node->m_bfmeBodyERQ, item);
}
