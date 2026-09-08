// ?bfmeSetABE@BfmeHostABE@@QAEHPAUBfmeArgABE@@0HH@Z
// partial score=0.88 date=2026-09-09
extern const float g_bfmeK1253;
extern const float g_bfmeDirectionWeight1285;

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0ABE();
	virtual void bfmeSlot1ABE();
	virtual void bfmeSlot2ABE();
	virtual void bfmeSlot3ABE();
	virtual void bfmeSlot4ABE();
	virtual void bfmeSlot5ABE();
	virtual void bfmeSlot6ABE();
	virtual float bfmeHeightABE(float x, float y, int layer, int a, int b);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

struct BfmeArgABE
{
	unsigned char m_bfmeHeadABE[0xc];
	unsigned int m_bfme0CABE;
};

class BfmeSubABE
{
public:
	int bfmeQueryABE(int a, int b, int c, int d, int e, int f);
};

class BfmeHostABE
{
public:
	int bfmeSetABE(BfmeArgABE *a0, BfmeArgABE *a1, int a2, int a3);

	BfmeSubABE *m_bfme00ABE;
	int m_bfme04ABE;
	float m_bfme08ABE;
	float m_bfme0CABE;
	float m_bfme10ABE;
};

int BfmeHostABE::bfmeSetABE(BfmeArgABE *a0, BfmeArgABE *a1, int a2, int a3)
{
	if (a0 != 0)
	{
		int f1 = (a1->m_bfme0CABE >> 6) & 0x3f;

		if (f1 >= 2 && f1 <= 0xf)
		{
			if (((a0->m_bfme0CABE >> 6) & 0x3f) == (unsigned int)f1)
				return 0;
		}
	}

	int f = (a1->m_bfme0CABE >> 6) & 0x3f;

	if (m_bfme00ABE->bfmeQueryABE(0, a2, a3, f, m_bfme04ABE, 1) != m_bfme04ABE)
		return 1;

	float x = ((float)a2 + g_bfmeK1253) * g_bfmeDirectionWeight1285;

	m_bfme08ABE = x;

	float y = ((float)a3 + g_bfmeK1253) * g_bfmeDirectionWeight1285;

	m_bfme0CABE = y;
	m_bfme10ABE = TheTerrainLogic->bfmeHeightABE(x, y, f, 0, 1);

	return 0;
}
