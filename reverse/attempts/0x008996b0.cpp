// ?bfmeAcquireFS@@YAPAURva008D2A30Node@@D@Z
// partial score=0.88 date=2026-09-08
extern "C" void *bfmeVftAFS[];
extern "C" void *bfmeVftBFS[];

struct Rva008D2A30Node
{
	void *m_bfmeVfFS;
	unsigned int m_bfmeFlagsFS;

	union
	{
		Rva008D2A30Node *m_bfmeNextFS;
		char m_bfmeKindFS;
	};
};

struct Rva00899560Pool
{
	int m_bfmeCapFS;
	int m_bfmeCountFS;
	Rva008D2A30Node **m_bfmeItemsFS;
};

extern Rva008D2A30Node *Rva008D2A30Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int n);

__forceinline void bfmeRegisterFS(Rva008D2A30Node *n)
{
	Rva00899560Pool *p = g_rva8CD130IdleHook;
	int count = p->m_bfmeCountFS;
	int cap = p->m_bfmeCapFS;

	if (count >= cap)
	{
		n->m_bfmeFlagsFS &= 0xbfffffff;
	}
	else
	{
		p->m_bfmeItemsFS[count] = n;
		p->m_bfmeCountFS = count + 1;
	}
}

Rva008D2A30Node *bfmeAcquireFS(char k)
{
	Rva008D2A30Node *n = Rva008D2A30Head;

	if (n != 0)
	{
		Rva008D2A30Head = n->m_bfmeNextFS;

		bfmeRegisterFS(n);

		n->m_bfmeKindFS = k;

		return n;
	}

	n = (Rva008D2A30Node *)Rva008C5D70Alloc(12);

	if (n == 0)
		return 0;

	n->m_bfmeVfFS = bfmeVftAFS;
	n->m_bfmeFlagsFS = (n->m_bfmeFlagsFS & 0xf0008005) | 0x40008005;

	bfmeRegisterFS(n);

	n->m_bfmeVfFS = bfmeVftBFS;
	n->m_bfmeKindFS = k;

	return n;
}
