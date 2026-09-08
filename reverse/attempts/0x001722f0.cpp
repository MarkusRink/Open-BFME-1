// ?bfmeRunJP@BfmeSelfJP@@QAEHXZ
// partial score=0.8 date=2026-09-08
class BfmeArgJP
{
public:
	int m_bfmeFJP[10];
};

class BfmeResJP
{
public:
	unsigned char m_bfmeHeadJP[0xc8];
	int m_bfmeFlagsJP;
};

class BfmeSubJP
{
public:
	BfmeResJP *bfmeResolveJP();
};

class BfmeNodeJP
{
public:
	unsigned char m_bfmeHeadJP[4];
	BfmeSubJP *m_bfme04JP;
};

class BfmeHostJP
{
public:
	void bfmeSendJP(BfmeArgJP *x, BfmeArgJP *y);

	unsigned char m_bfmeHeadJP[4];
	BfmeNodeJP *m_bfme04JP;
};

class BfmeOwnJP
{
public:
	unsigned char m_bfmeHeadJP[0x10];
	BfmeHostJP *m_bfme10JP;
};

class ScriptEngine
{
public:
	void bfmePokeJP();
};

class BfmeAiHelpJP
{
public:
	void bfmeDoJP(BfmeHostJP *h);
};

class AI
{
public:
	unsigned char m_bfmeHeadJP[0xc];
	BfmeAiHelpJP *m_bfmeHelpJP;
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class BfmeSelfJP
{
public:
	int bfmeRunJP();

	unsigned char m_bfmeHeadJP[0x1c];
	BfmeOwnJP *m_bfme1cJP;
};

int BfmeSelfJP::bfmeRunJP()
{
	BfmeHostJP *h = m_bfme1cJP->m_bfme10JP;

	if (h != 0)
	{
		BfmeArgJP a;
		BfmeArgJP b;

		int za = 0;
		int zb = 0;

		a.m_bfmeFJP[0] = za;
		a.m_bfmeFJP[1] = za | 0x20000000;
		a.m_bfmeFJP[2] = za;
		a.m_bfmeFJP[3] = za;
		a.m_bfmeFJP[4] = za;
		a.m_bfmeFJP[5] = za;
		a.m_bfmeFJP[6] = za;
		a.m_bfmeFJP[7] = za;
		a.m_bfmeFJP[8] = za;
		b.m_bfmeFJP[0] = zb;
		b.m_bfmeFJP[1] = zb | 0x11ffff80;
		b.m_bfmeFJP[2] = zb;
		b.m_bfmeFJP[3] = zb | 0x700000;
		b.m_bfmeFJP[4] = zb | 0x80000;
		b.m_bfmeFJP[5] = zb;
		b.m_bfmeFJP[6] = zb;
		b.m_bfmeFJP[7] = zb;
		b.m_bfmeFJP[8] = zb;
		b.m_bfmeFJP[9] = zb;

		h->bfmeSendJP(&b, &a);

		TheScriptEngine->bfmePokeJP();

		BfmeNodeJP *p = h->m_bfme04JP;
		BfmeResJP *q;

		if (p != 0)
		{
			BfmeSubJP *sub = p->m_bfme04JP;

			if (sub != 0)
				q = sub->bfmeResolveJP();
			else
				q = (BfmeResJP *)p;
		}
		else
		{
			q = 0;
		}

		if (q->m_bfmeFlagsJP & 0x100)
			TheAI->m_bfmeHelpJP->bfmeDoJP(h);
	}

	return 0;
}
