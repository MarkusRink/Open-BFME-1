// ?bfmeEraseAAF@BfmeHostAAF@@QAE_NPAX_N@Z
// partial score=0.85 date=2026-09-08
struct BfmeStrAAF
{
	~BfmeStrAAF();

	void *m_bfmeDataAAF;
};

struct BfmeNodeAAF
{
	BfmeNodeAAF *m_bfmeNextAAF;
	BfmeNodeAAF *m_bfmePrevAAF;
	BfmeStrAAF m_bfmeStrAAF;
};

struct BfmeIterAAF
{
	BfmeIterAAF(BfmeNodeAAF *n) { m_bfmeNodeAAF = n; }
	BfmeIterAAF(const BfmeIterAAF &o) throw() { m_bfmeNodeAAF = o.m_bfmeNodeAAF; }

	BfmeNodeAAF *m_bfmeNodeAAF;
};

BfmeIterAAF bfmeFindAAF(BfmeIterAAF first, BfmeIterAAF last, void *value, void *tag);

namespace _STL
{

class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

}

class BfmeHostAAF
{
public:
	bool bfmeEraseAAF(void *key, bool doErase);

	unsigned char m_bfmeHeadAAF[0x17260];
	BfmeNodeAAF *m_bfme17260AAF;
};

bool BfmeHostAAF::bfmeEraseAAF(void *key, bool doErase)
{
	BfmeNodeAAF *head = m_bfme17260AAF;
	BfmeNodeAAF *n = bfmeFindAAF(BfmeIterAAF(head->m_bfmeNextAAF), BfmeIterAAF(head), key, &doErase).m_bfmeNodeAAF;

	if (n == m_bfme17260AAF)
		return false;

	if (!doErase)
		return true;

	BfmeNodeAAF *pv = n->m_bfmePrevAAF;
	BfmeNodeAAF *nx = n->m_bfmeNextAAF;

	pv->m_bfmeNextAAF = nx;
	nx->m_bfmePrevAAF = pv;

	n->m_bfmeStrAAF.~BfmeStrAAF();
	_STL::__node_alloc::_M_deallocate(n, 12);

	return true;
}
