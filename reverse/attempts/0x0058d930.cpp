// ?bfmeResetBC@BfmeHostBC@@QAEXXZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 66/72. Build a 0x18-byte parameter block on the stack (one member copy, three
// -1s via `or reg,-1`, and three zeros), clear two byte members, and hand the
// block plus two sub-object addresses to a cdecl helper. The frame, the 0x18
// block, the -1 run and the combined `add esp,0x24` all match.
// Residue: retail writes all five zero stores as IMMEDIATES
//   c6 01 00 / c6 00 00 / c7 44 24 10 0.. / c6 44 24 20 00 / c6 44 24 21 00
// because it schedules the three argument pushes FIRST, leaving no free
// register. MSVC materialises `xor edx,edx` and stores dl everywhere, which is
// 6 bytes shorter. Tried: field order, sinking the zeros after the member
// stores, `volatile` on the block, and /G7 /G6 /G5 /Op /QIfist -- every one
// gives the identical 66-byte register-shared form.
struct BfmeParamBC
{
	int m_bfmeABC;
	int m_bfmeBBC;
	int m_bfmeCBC;
	int m_bfmeDBC;
	int m_bfmeEBC;
	unsigned char m_bfmeFBC;
	unsigned char m_bfmeGBC;
	unsigned char m_bfmePadBC[2];
};

extern "C" void __cdecl bfmeApplyBC(void *sub, unsigned char *other, BfmeParamBC *param);

class BfmeHostBC
{
public:
	void bfmeResetBC();

	unsigned char m_bfmeFlagBC;
	unsigned char m_bfmePadOneBC[3];
	int m_bfmeValueBC;
	unsigned char m_bfmeSubBC[0x198];
	unsigned char m_bfmeOtherBC;
};

void BfmeHostBC::bfmeResetBC()
{
	BfmeParamBC param;

	param.m_bfmeABC = m_bfmeValueBC;
	param.m_bfmeCBC = -1;
	param.m_bfmeDBC = -1;
	param.m_bfmeEBC = -1;

	m_bfmeFlagBC = 0;
	m_bfmeOtherBC = 0;

	param.m_bfmeBBC = 0;
	param.m_bfmeFBC = 0;
	param.m_bfmeGBC = 0;

	bfmeApplyBC(m_bfmeSubBC, &m_bfmeOtherBC, &param);
}
