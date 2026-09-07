// ?d_0035ac30@@YAXXZ
// partial score=0.97 date=2026-09-08
class BfmeNodeEAQ
{
public:
	~BfmeNodeEAQ();

	BfmeNodeEAQ *m_bfmeNextEAQ;
};

class BfmeElemEAQ
{
public:
	~BfmeElemEAQ();

	unsigned char m_bfmeHeadEAQ[0x10];
	BfmeNodeEAQ *m_bfmeListEAQ;
};

class BfmeVecEAQ
{
public:
	BfmeElemEAQ *m_bfmeBeginEAQ;
	BfmeElemEAQ *m_bfmeEndEAQ;
};

void bfmeClearEAQ(BfmeVecEAQ *v)
{
	while (v->m_bfmeBeginEAQ != v->m_bfmeEndEAQ)
	{
		BfmeElemEAQ *e = v->m_bfmeEndEAQ - 1;

		while (e->m_bfmeListEAQ != 0)
		{
			BfmeNodeEAQ *n = e->m_bfmeListEAQ;

			if (n != 0)
			{
				e->m_bfmeListEAQ = n->m_bfmeNextEAQ;

				delete n;
			}
		}

		v->m_bfmeEndEAQ = v->m_bfmeEndEAQ - 1;

		v->m_bfmeEndEAQ->~BfmeElemEAQ();
	}
}
