// ?bfmeInsertZO@BfmeIterZO@@QAEXPBUBfmeValZO@@@Z
// partial score=0.96 date=2026-09-08
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

inline void *operator new(unsigned int, void *p)
{
	return p;
}

struct BfmeValZO
{
	BfmeValZO(const BfmeValZO &o) : m_bfmeAZO(o.m_bfmeAZO), m_bfmeBZO(o.m_bfmeBZO) {}

	void *m_bfmeAZO;
	void *m_bfmeBZO;
};

struct BfmeNodeZO
{
	BfmeNodeZO *m_bfmePrevZO;
	BfmeNodeZO *m_bfmeNextZO;
	BfmeValZO m_bfmeValZO;
};

class BfmeIterZO
{
public:
	void bfmeInsertZO(const BfmeValZO *v);

	BfmeNodeZO **m_bfme00ZO;
};

void BfmeIterZO::bfmeInsertZO(const BfmeValZO *v)
{
	BfmeNodeZO *at = *m_bfme00ZO;
	BfmeNodeZO *n = (BfmeNodeZO *)_STL::__new_alloc::allocate(16);

	new (&n->m_bfmeValZO) BfmeValZO(*v);

	BfmeNodeZO *nx = at->m_bfmeNextZO;

	n->m_bfmePrevZO = at;
	n->m_bfmeNextZO = nx;
	nx->m_bfmePrevZO = n;
	at->m_bfmeNextZO = n;
}
