// ??0BfmeListGU@@QAE@XZ
// partial score=0.93 date=2026-09-08
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

class BfmeCellGU
{
public:
	char m_bfmeFlagGU;
	unsigned char m_bfmePadGU[3];
	int m_bfmeValueGU;
	BfmeCellGU *m_bfmeNextGU;
	BfmeCellGU *m_bfmePrevGU;
	int m_bfmeTailGU;
};

class BfmeListGU
{
public:
	BfmeListGU();

	char m_bfmeAGU;
	char m_bfmeBGU;
	char m_bfmeCGU;
	unsigned char m_bfmePadGU[1];
	int m_bfmeDGU;
	BfmeCellGU *m_bfmeNodeGU;
	int m_bfmeCountGU;
};

BfmeListGU::BfmeListGU()
{
	m_bfmeAGU = 1;
	m_bfmeBGU = 1;
	m_bfmeCGU = 1;
	m_bfmeDGU = -1;
	m_bfmeNodeGU = 0;
	m_bfmeNodeGU = (BfmeCellGU *)_STL::__new_alloc::allocate(0x14);
	m_bfmeCountGU = 0;
	m_bfmeNodeGU->m_bfmeFlagGU = 0;
	m_bfmeNodeGU->m_bfmeValueGU = 0;
	m_bfmeNodeGU->m_bfmeNextGU = m_bfmeNodeGU;
	m_bfmeNodeGU->m_bfmePrevGU = m_bfmeNodeGU;
}
