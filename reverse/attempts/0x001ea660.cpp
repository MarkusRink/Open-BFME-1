// ?bfmeFwdGF@@YGXPAX0PAVBfmeThingGF@@0@Z
// partial score=0.8 date=2026-09-08
class BfmeThingGF
{
public:
	unsigned char m_bfmeHeadGF[0x74];
	void *m_bfmeValueGF;
};

void __stdcall bfmeCallGF(void *a, void *b, BfmeThingGF *c, void *v, int e, int f, int g, void *d, int i);

void __stdcall bfmeFwdGF(void *a, void *b, BfmeThingGF *c, void *d)
{
	bfmeCallGF(a, b, c, c->m_bfmeValueGF, 0, 1, 0, d, 0);
}
