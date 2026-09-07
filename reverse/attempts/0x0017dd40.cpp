// ?bfmeStartVX@BfmeOwnerVX@@QAEHXZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 65/67 bytes. The guard is inverted from the obvious reading: retail's
// `cmp eax,[edx+3ch]; jae body` means the source is
// `if (m_index < count) return -1;` -- the LESS-than case returns.
// Everything else lines up: a 12-byte local args block passed by address with
// a trailing 0 argument, and the sink reached as this->m_1c->m_10.
// Residue (2 bytes): retail builds the 400000h field through the zero
// register -- `xor edx,edx; mov eax,edx; or eax,400000h` -- and writes the
// three fields in the order 1, 0, 2, while MSVC stores immediates directly.
// A constructor taking the flags and assigning in that 1,0,2 order does not
// recover it either (still 65, 14 differing lines).
// Zero-register-propagation residue.
struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadVX[0x3c];
	unsigned int m_bfmeCountVX;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

struct BfmeArgsVX
{
	int m_bfmeFlagsVX;
	int m_bfmeSecondVX;
	int m_bfmeThirdVX;
};

class BfmeSinkVX
{
public:
	void bfmeSendVX(BfmeArgsVX *args, int flag);
};

class BfmeThingVX
{
public:
	unsigned char m_bfmeHeadVX[0x10];
	BfmeSinkVX *m_bfmeSinkVX;
};

class BfmeOwnerVX
{
public:
	int bfmeStartVX(void);

	unsigned char m_bfmeHeadVX[0x1c];
	BfmeThingVX *m_bfmeThingVX;
	unsigned char m_bfmeGapVX[4];
	unsigned int m_bfmeIndexVX;
};

int BfmeOwnerVX::bfmeStartVX(void)
{
	if (m_bfmeIndexVX < TheBfmeGameLogic->m_bfmeCountVX)
		return -1;

	BfmeArgsVX args;

	args.m_bfmeFlagsVX = 0x400000;
	args.m_bfmeSecondVX = 0;
	args.m_bfmeThirdVX = 0;

	m_bfmeThingVX->m_bfmeSinkVX->bfmeSendVX(&args, 0);

	return 0;
}
