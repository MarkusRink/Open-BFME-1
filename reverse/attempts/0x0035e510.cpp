// ?d_0035e510@@YAXXZ
// partial score=0.95 date=2026-09-08
class BfmeHeadEAT
{
public:
	int m_bfmeHeadEAT;
};

class BfmeBaseEAT
{
public:
	int m_bfmeAEAT;
	int m_bfmeBEAT;
};

class BfmeSubAEAT
{
public:
	void bfmeSwapAEAT(BfmeSubAEAT *other);

	unsigned char m_bfmeBodyAEAT[0x20];
};

class BfmeSubBEAT
{
public:
	void bfmeSwapBEAT(BfmeSubBEAT *other);

	unsigned char m_bfmeBodyBEAT[4];
};

class BfmeNodeEAT;

void __stdcall bfmeLinkEAT(BfmeNodeEAT *node, int *a, int *b);

class BfmeNodeEAT : public BfmeHeadEAT, public BfmeBaseEAT
{
public:
	void bfmeSwapEAT(BfmeNodeEAT *other);
	void bfmeFixEAT();
	void bfmeRelinkEAT(BfmeNodeEAT *node, int *a, int *b);

	BfmeSubAEAT m_bfmeSubAEAT;
	BfmeSubBEAT m_bfmeSubBEAT;
};

void BfmeNodeEAT::bfmeSwapEAT(BfmeNodeEAT *other)
{
	BfmeBaseEAT *b = other;
	int *link = &m_bfmeAEAT;

	int t = link[0];
	link[0] = b->m_bfmeAEAT;
	b->m_bfmeAEAT = t;

	t = link[1];
	link[1] = b->m_bfmeBEAT;
	b->m_bfmeBEAT = t;

	m_bfmeSubAEAT.bfmeSwapAEAT(&other->m_bfmeSubAEAT);

	m_bfmeSubBEAT.bfmeSwapBEAT(&other->m_bfmeSubBEAT);

	bfmeFixEAT();

	bfmeLinkEAT(other, &other->m_bfmeAEAT, link);

	bfmeRelinkEAT(other, &other->m_bfmeBEAT, &m_bfmeBEAT);
}
