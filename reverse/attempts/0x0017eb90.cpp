// ?d_0017eb90@@YAXXZ
// partial score=0.9 date=2026-09-08
class BfmeStateEAM
{
public:
	unsigned char m_bfmeHeadEAM[0x333];
	char m_bfmeAEAM;
	char m_bfmeBEAM;
};

class BfmeObjEAM
{
public:
	void bfmeClearEAM(int mode);
	void bfmeStopEAM(int mode);
	void bfmeNotifyEAM();
	void bfmeFinishEAM(int mode, int flag);

	unsigned char m_bfmeHeadEAM[0x11c];
	int m_bfmeFlagsEAM;
	unsigned char m_bfmePadEAM[0xe4];
	BfmeStateEAM *m_bfmeStateEAM;
};

class BfmeOwnerEAM
{
public:
	unsigned char m_bfmeHeadEAM[0x10];
	BfmeObjEAM *m_bfmeObjEAM;
};

class BfmeHostEAM
{
public:
	void bfmeResetEAM(int unused);

	unsigned char m_bfmeHeadEAM[0x1c];
	BfmeOwnerEAM *m_bfmeOwnerEAM;
};

void BfmeHostEAM::bfmeResetEAM(int unused)
{
	BfmeObjEAM *obj = m_bfmeOwnerEAM->m_bfmeObjEAM;

	if (obj == 0)
		return;

	BfmeStateEAM *state = obj->m_bfmeStateEAM;

	if (state == 0)
		return;

	obj->bfmeClearEAM(0x38);
	obj->bfmeStopEAM(8);

	state->m_bfmeAEAM = 0;
	state->m_bfmeBEAM = 0;

	int flags = obj->m_bfmeFlagsEAM;

	if ((flags & 0x10000000) == 0)
	{
		obj->m_bfmeFlagsEAM = flags | 0x10000000;

		obj->bfmeNotifyEAM();
	}

	obj->bfmeFinishEAM(8, 0);
}
