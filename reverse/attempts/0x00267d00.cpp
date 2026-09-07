// ?bfmeStopCO@BfmeHostCO@@QAEXD@Z (identity unknown)
// partial score=0.93 date=2026-09-07
// 99/102. The whole chain matches -- `test ah,8` for the 0x800 bit, the four
// guards, the secondary member walk and the four-argument tail call.
// The 3 bytes: retail COPIES the flags before masking
//   mov eax,[esi+0x130] / test ah,8 / mov ecx,eax / and ecx,0xfffff7ff /
//   mov [esi+0x130],ecx
// where MSVC masks in place (`and eax,0xfffff7ff`). eax is dead either way, so
// retail is simply preserving it -- possibly because `test ah,8` reads only a
// sub-register and its optimizer kept eax live.
// Tried: a separate named local for the cleared value. Identical output.
class BfmeAgentCO
{
public:
	char bfmeBusyCO();
	void bfmeSendCO(void *at, int a, int b, int c);
};

class BfmeUnitCO
{
public:
	void bfmeWakeCO();

	unsigned char m_bfmeHeadCO[0x38];
	unsigned char m_bfmeAtCO[4];
	unsigned char m_bfmeMidCO[0xf4];
	int m_bfmeFlagsCO;
};

class BfmeOtherCO
{
public:
	unsigned char m_bfmeHeadCO[0x264];
	BfmeAgentCO *m_bfmeAgentCO;
};

class BfmeHostCO
{
public:
	void bfmeStopCO(char quiet);
	void bfmeHaltCO(int mode);

	unsigned char m_bfmeHeadCO[4];
	BfmeOtherCO *m_bfmeOtherCO;
	BfmeUnitCO *m_bfmeUnitCO;
};

void BfmeHostCO::bfmeStopCO(char quiet)
{
	BfmeUnitCO *u = m_bfmeUnitCO;
	int flags = u->m_bfmeFlagsCO;

	if ((flags & 0x800) == 0)
		return;

	u->m_bfmeFlagsCO = flags & ~0x800;
	u->bfmeWakeCO();

	if (quiet != 0)
		return;

	bfmeHaltCO(1);

	BfmeAgentCO *a = m_bfmeOtherCO->m_bfmeAgentCO;

	if (a == 0)
		return;

	if (a->bfmeBusyCO() != 0)
		return;

	a->bfmeSendCO(u->m_bfmeAtCO, 0, 0, 0);
}
