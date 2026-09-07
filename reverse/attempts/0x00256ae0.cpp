// ?bfmeStepESN@BfmeHostESN@@QAEXPAVBfmeThingESN@@@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 111/108. Whole shape reproduces: the id lookup, the clear-or-attach split,
// the thing guard, the notify and the 12-byte command sent to m_08.
// The 3 bytes are how the command is filled. Retail keeps ZERO in a register
// and derives the flag word from it:
//     xor ecx,ecx / mov eax,ecx / mov [esp+8],ecx / mov [esp+0x10],ecx
//     or  eax,0x20000000 / mov [esp+0xc],eax          = 21 bytes
// MSVC constant-folds 0 | 0x20000000 and emits three immediate stores
//     mov [esp+0x10],0 / mov [esp+0x14],0 / mov [esp+0xc],0x20000000 = 24
// Ruled out: a zeroing constructor plus cmd.m_flags |= K (this file); no
// constructor with explicit stores and 0 | K written out (also 111); volatile
// members (does not compile -- the struct is passed by pointer to a
// non-volatile parameter).
// The lever wanted is whatever stops MSVC folding the OR against a known
// zero; see memory volatile-stops-zero-propagation and
// one-register-constant-rule, neither of which fired here.
// Pins are already in symbols.csv.
struct BfmeCmdESN
{
	BfmeCmdESN()
	{
		m_bfmeFlagsESN = 0;
		m_bfmeBESN = 0;
		m_bfmeCESN = 0;
	}

	int m_bfmeFlagsESN;
	int m_bfmeBESN;
	int m_bfmeCESN;
};

class BfmeSinkESN
{
public:
	void bfmeSendESN(BfmeCmdESN *cmd, int mode);
};

void __stdcall bfmeNotifyESN(BfmeSinkESN *sink);

class BfmeObjESN;

class BfmeLogicESN
{
public:
	BfmeObjESN *bfmeFindByIdESN(int id);
};

extern BfmeLogicESN *g_bfmeLogicESN;

class BfmeThingESN
{
public:
	unsigned char m_bfmeHeadESN[0x74];
	int m_bfme74ESN;
};

class BfmeHostESN
{
public:
	void bfmeStepESN(BfmeThingESN *thing);
	void bfmeAttachESN(BfmeObjESN *obj);

	unsigned char m_bfmeHeadESN[8];
	BfmeSinkESN *m_bfme08ESN;
	unsigned char m_bfmeMidESN[0x14];
	int m_bfme20ESN;
};

void BfmeHostESN::bfmeStepESN(BfmeThingESN *thing)
{
	int id = m_bfme20ESN;

	if (id != 0)
	{
		BfmeObjESN *obj = g_bfmeLogicESN->bfmeFindByIdESN(id);

		if (obj == 0)
			m_bfme20ESN = 0;
		else
			bfmeAttachESN(obj);
	}

	if (thing != 0)
	{
		m_bfme20ESN = thing->m_bfme74ESN;

		bfmeNotifyESN(m_bfme08ESN);

		BfmeCmdESN cmd;

		cmd.m_bfmeFlagsESN |= 0x20000000;

		m_bfme08ESN->bfmeSendESN(&cmd, 1);
	}
}
