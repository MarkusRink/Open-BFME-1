// ?bfmeCall942D@BfmeSub942D@@QAEPAXPAX@Z
// partial score=0.9 date=2026-09-07
class BfmeMgrF1D
{
public:
	void *registerObj(void *field);
};

extern BfmeMgrF1D *g_mgr12EF1D8;

class BfmeSub942D
{
public:
	void *bfmeCall942D(void *a);

private:
	struct BfmeElem942D
	{
		char m_bfmePad942D[0x60];
	};

	char m_bfmePad942D[4];
	BfmeElem942D *volatile m_bfmeBegin942D;
	BfmeElem942D *volatile m_bfmeEnd942D;
};

void *BfmeSub942D::bfmeCall942D(void *a)
{
	int index = (int)a;
	if ((unsigned int)index >= (unsigned int)(m_bfmeEnd942D - m_bfmeBegin942D))
		return 0;
	return g_mgr12EF1D8->registerObj(m_bfmeBegin942D + index);
}
