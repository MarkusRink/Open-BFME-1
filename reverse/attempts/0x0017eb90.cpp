// ?bfmeAbortCM@BfmeHostCM@@QAEXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 101/100. Everything matches except the flag block, which is the SAME one-byte
// residue as 0x002CDF00 -- see reverse/attempts/0x002cdf00.cpp:
//   retail  mov ecx,[esi+0x11c] / mov eax,0x10000000 / test eax,ecx / jne /
//           or ecx,eax / mov [esi+0x11c],ecx          (flags in ECX)
//   MSVC    mov eax,[esi+0x11c] / test eax,0x10000000 / jne /
//           or eax,0x10000000 / mov [esi+0x11c],eax   (flags in EAX)
// With the flags in eax the 5-byte `a9` immediate test always beats
// materialising the constant, so MSVC never shares it. Retail's compiler put
// the load in ecx (free after the preceding thiscall) and then the register
// form wins. Nothing source-level seen so far moves that choice; tried on the
// other body: naming the receiver first, and routing the bit through an inlined
// function parameter.
class BfmeStateCM
{
public:
	unsigned char m_bfmeHeadCM[0x333];
	unsigned char m_bfmeACM;
	unsigned char m_bfmeBCM;
};

class BfmeUnitCM
{
public:
	void bfmeNotifyCM(int what);
	void bfmeClearCM(int mask);
	void bfmeWakeCM();
	void bfmeIdleCM(int mode, int flag);

	unsigned char m_bfmeHeadCM[0x11c];
	int m_bfmeFlagsCM;
	unsigned char m_bfmeMidCM[0xe4];
	BfmeStateCM *m_bfmeStateCM;
};

class BfmeOwnerCM
{
public:
	unsigned char m_bfmeHeadCM[0x10];
	BfmeUnitCM *m_bfmeUnitCM;
};

class BfmeHostCM
{
public:
	void bfmeAbortCM(void *unused);

	unsigned char m_bfmeHeadCM[0x1c];
	BfmeOwnerCM *m_bfmeOwnerCM;
};

void BfmeHostCM::bfmeAbortCM(void *unused)
{
	BfmeUnitCM *u = m_bfmeOwnerCM->m_bfmeUnitCM;

	if (u == 0)
		return;

	BfmeStateCM *s = u->m_bfmeStateCM;

	if (s == 0)
		return;

	u->bfmeNotifyCM(0x38);
	u->bfmeClearCM(8);

	s->m_bfmeACM = 0;
	s->m_bfmeBCM = 0;

	int flags = u->m_bfmeFlagsCM;

	if ((flags & 0x10000000) == 0)
	{
		u->m_bfmeFlagsCM = flags | 0x10000000;
		u->bfmeWakeCM();
	}

	u->bfmeIdleCM(8, 0);
}
