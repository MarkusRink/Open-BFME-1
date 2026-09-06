// ??0BfmeOwnCL@@QAE@XZ (identity unknown)
// partial score=0.91 date=2026-09-07
// Exact size (102) once the layout is right. The EH frame only appears when
// the FIRST member has a destructor: without it MSVC drops the frame entirely
// and the body is 58 bytes. So this class is
//   BfmeHeadCL (3 ints, ctor zeroes them, dtor declared)  at +0
//   BfmeListCL (allocates a 0x14 node and self-links it)  at +0xc
//   six plain ints                                        at +0x10..+0x24
// and the single unwind state 0 is set after the head member and before the
// allocating list constructor, which is the only thing that can throw.
// Residue: the EH this-slot store `mov [esp+8], esi` lands in the middle of
// the head member's three stores in retail and before them in MSVC -- the
// same constructor residue as 0x0034C5E0 and 0x000FB260.
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

}

class BfmeNodeCL
{
public:
	BfmeNodeCL *m_bfmeNextCL;
	BfmeNodeCL *m_bfmePrevCL;
	unsigned char m_bfmePadCL[0xc];
};

class BfmeListCL
{
public:
	BfmeListCL(void)
	{
		m_bfmeNodeCL = 0;

		BfmeNodeCL *node = (BfmeNodeCL *)_STL::__new_alloc::allocate(0x14);

		node->m_bfmeNextCL = node;
		node->m_bfmePrevCL = node;
		m_bfmeNodeCL = node;
	}
	~BfmeListCL();

	BfmeNodeCL *m_bfmeNodeCL;
};

class BfmeHeadCL
{
public:
	BfmeHeadCL(void)
	{
		m_bfmeACL = 0;
		m_bfmeBCL = 0;
		m_bfmeCCL = 0;
	}
	~BfmeHeadCL();

	int m_bfmeACL;
	int m_bfmeBCL;
	int m_bfmeCCL;
};

class BfmeOwnCL
{
public:
	BfmeOwnCL(void);

	BfmeHeadCL m_bfmeHeadCL;
	BfmeListCL m_bfmeListCL;
	int m_bfmeDCL;
	int m_bfmeECL;
	int m_bfmeFCL;
	int m_bfmeGCL;
	int m_bfmeHCL;
	int m_bfmeICL;
};

BfmeOwnCL::BfmeOwnCL(void)
{
	m_bfmeDCL = 0;
	m_bfmeECL = 0;
	m_bfmeFCL = 0;
	m_bfmeGCL = 0;
	m_bfmeHCL = 0;
	m_bfmeICL = 0;
}
