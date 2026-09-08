// ?bfmeParseXU@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.96 date=2026-09-08
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

__declspec(dllimport) int __cdecl bfmeAtoiVHG(const char *s);

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);

	unsigned char m_bfmeHeadXU[0x414];
	const char *m_bfme414XU;
};

struct BfmeNodeXU
{
	BfmeNodeXU *m_bfmeNextXU;
	BfmeNodeXU *m_bfmePrevXU;
	int m_bfmeValXU;
};

void bfmeParseXU(INI *ini, void *instance, void *store, const void *userData)
{
	const char *tok = ini->getNextTokenOrNull(ini->m_bfme414XU);

	if (tok == 0)
		return;

	do
	{
		int v = bfmeAtoiVHG(tok);
		BfmeNodeXU *head = *(BfmeNodeXU **)store;
		BfmeNodeXU *n = (BfmeNodeXU *)_STL::__new_alloc::allocate(12);
		int *q = &n->m_bfmeValXU;

		if (q != 0)
			*q = v;

		BfmeNodeXU *prev = head->m_bfmePrevXU;

		n->m_bfmePrevXU = prev;
		n->m_bfmeNextXU = head;
		prev->m_bfmeNextXU = n;
		head->m_bfmePrevXU = n;

		tok = ini->getNextTokenOrNull(ini->m_bfme414XU);
	}
	while (tok);
}
