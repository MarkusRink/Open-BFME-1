// ?bfmeInsertJM@BfmeListJM@@QAEXPAVBfmeValJM@@@Z
// partial score=0.95 date=2026-09-08
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

class BfmeValJM
{
public:
	int m_bfmeAJM;
	int m_bfmeBJM;
};

class BfmeNodeJM
{
public:
	BfmeNodeJM *m_bfmePrevJM;
	BfmeNodeJM *m_bfmeNextJM;
	BfmeValJM m_bfmeValJM;
};

class BfmeListJM
{
public:
	void bfmeInsertJM(BfmeValJM *v);

	BfmeNodeJM *m_bfmeNodeJM;
};

void BfmeListJM::bfmeInsertJM(BfmeValJM *v)
{
	BfmeNodeJM *e = m_bfmeNodeJM->m_bfmePrevJM;
	BfmeNodeJM *n = (BfmeNodeJM *)_STL::__new_alloc::allocate(16);
	BfmeValJM *p = &n->m_bfmeValJM;

	if (p != 0)
	{
		p->m_bfmeAJM = v->m_bfmeAJM;
		p->m_bfmeBJM = v->m_bfmeBJM;
	}

	BfmeNodeJM *nx = e->m_bfmeNextJM;

	n->m_bfmePrevJM = e;
	n->m_bfmeNextJM = nx;
	nx->m_bfmePrevJM = n;
	e->m_bfmeNextJM = n;
}
