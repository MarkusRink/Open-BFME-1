// ?d_005edfa0@@YAXXZ
// partial score=0.95 date=2026-09-08
extern "C" void *bfmeVft1EVL[];
extern "C" void *bfmeVft2EVL[];
extern "C" void *bfmeVft3EVL[];
extern "C" void *bfmeVft4EVL[];
extern "C" void *bfmeVft5EVL[];
extern "C" void *bfmeVft6EVL[];
extern "C" void *bfmeVft7EVL[];
extern "C" void *bfmeVft8EVL[];
extern "C" void *bfmeVft9EVL[];
extern "C" void *bfmeVft10EVL[];

class BfmeBaseEVL
{
public:
	void bfmeInitBaseEVL(BfmeBaseEVL *src);

	unsigned char m_bfmeBodyEVL[0xc];
};

class BfmeSubEVL
{
public:
	void bfmeInitSubEVL(BfmeSubEVL *src);

	void *m_bfmeVftDEVL;
	unsigned char m_bfmeBodySEVL[0xc];
};

class BfmeHostEVL
{
public:
	BfmeHostEVL(BfmeHostEVL *other);

	void *m_bfmeVftAEVL;
	BfmeBaseEVL m_bfmeBaseEVL;
	volatile int m_bfmeValueEVL;
	void *volatile m_bfmeVftBEVL;
	void *volatile m_bfmeVftCEVL;
	BfmeSubEVL m_bfmeSubEVL;
};

BfmeHostEVL::BfmeHostEVL(BfmeHostEVL *other)
{
	m_bfmeVftAEVL = bfmeVft1EVL;
	m_bfmeBaseEVL.bfmeInitBaseEVL(&other->m_bfmeBaseEVL);

	m_bfmeValueEVL = other->m_bfmeValueEVL;

	m_bfmeVftBEVL = bfmeVft2EVL;
	m_bfmeVftCEVL = bfmeVft3EVL;

	m_bfmeVftAEVL = bfmeVft4EVL;
	m_bfmeVftBEVL = bfmeVft5EVL;
	m_bfmeVftCEVL = bfmeVft6EVL;

	m_bfmeSubEVL.bfmeInitSubEVL(&other->m_bfmeSubEVL);

	m_bfmeVftAEVL = bfmeVft7EVL;
	m_bfmeVftBEVL = bfmeVft8EVL;
	m_bfmeVftCEVL = bfmeVft9EVL;

	m_bfmeSubEVL.m_bfmeVftDEVL = bfmeVft10EVL;
}
