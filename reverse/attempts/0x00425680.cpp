// ?d_00425680@@YAXXZ
// partial score=0.99 date=2026-09-08
namespace _STL
{
	struct __new_alloc
	{
		static void *allocate(unsigned int n);
	};
}

struct BfmeNodeEAL
{
	char m_bfmeCharEAL;
	unsigned char m_bfmePadEAL[3];
	int m_bfmeSizeEAL;
	BfmeNodeEAL *m_bfmeNextEAL;
	BfmeNodeEAL *m_bfmePrevEAL;
	int m_bfmeTailEAL;
	int m_bfmeTail2EAL;
};

class BfmeHostEAL
{
public:
	BfmeHostEAL();

	volatile int m_bfmeAEAL;
	volatile int m_bfmeBEAL;
	volatile int m_bfmeCEAL;
	volatile int m_bfmeDEAL;
	BfmeNodeEAL *m_bfmeNodeEAL;
	volatile int m_bfmeEEAL;
};

BfmeHostEAL::BfmeHostEAL()
{
	m_bfmeAEAL = 0x4e20;
	m_bfmeBEAL = 0x5dc;
	m_bfmeCEAL = 0;
	m_bfmeDEAL = 5;
	m_bfmeNodeEAL = 0;

	m_bfmeNodeEAL = (BfmeNodeEAL *)_STL::__new_alloc::allocate(0x18);

	m_bfmeEEAL = 0;

	m_bfmeNodeEAL->m_bfmeCharEAL = 0;
	m_bfmeNodeEAL->m_bfmeSizeEAL = 0;
	m_bfmeNodeEAL->m_bfmeNextEAL = m_bfmeNodeEAL;
	m_bfmeNodeEAL->m_bfmePrevEAL = m_bfmeNodeEAL;
}
