// ?d_0061bd90@@YAXXZ
// partial score=0.93 date=2026-09-08
extern "C" void *bfmeVft1VUQ[];
extern "C" void *bfmeVft2VUQ[];

class BfmeObjVUQ
{
public:
	virtual void bfmeCloseVUQ(int mode);

	unsigned char m_bfmeSubVUQ[0x80];
	int m_bfmeFlagVUQ;
};

extern int (__stdcall *g_bfmeCheckVUQ)(void *sub);

class BfmeRefVUQ
{
public:
	__forceinline ~BfmeRefVUQ()
	{
		BfmeObjVUQ *p = m_bfmePtrVUQ;

		if (p != 0 && g_bfmeCheckVUQ(p->m_bfmeSubVUQ) <= 0 && p != 0)
			p->bfmeCloseVUQ(1);
	}

	BfmeObjVUQ *m_bfmePtrVUQ;
};

class BfmeStrVUQ
{
public:
	~BfmeStrVUQ();

	void *m_bfmeDataVUQ;
};

class Rva005A00B0AudioClient
{
public:
	virtual void bfmeSlot00VUQ();
	virtual void bfmeSlot01VUQ();
	virtual void bfmeSlot02VUQ();
	virtual void bfmeSlot03VUQ();
	virtual void bfmeSlot04VUQ();
	virtual void bfmeSlot05VUQ();
	virtual void bfmeSlot06VUQ();
	virtual void bfmeSlot07VUQ();
	virtual void bfmeSlot08VUQ();
	virtual void bfmeSlot09VUQ();
	virtual void bfmeSlot10VUQ();
	virtual void bfmeSlot11VUQ();
	virtual void bfmeSlot12VUQ();
	virtual void bfmeSlot13VUQ();
	virtual void bfmeSlot14VUQ();
	virtual void bfmeSlot15VUQ();
	virtual void bfmeSlot16VUQ();
	virtual void bfmeSlot17VUQ();
	virtual void bfmeSlot18VUQ();
	virtual void bfmeStopVUQ(unsigned int mode);
	virtual void bfmeSlot20VUQ();
	virtual void bfmeSlot21VUQ();
	virtual void bfmeSlot22VUQ();
	virtual void bfmeSlot23VUQ();
	virtual void bfmeSlot24VUQ();
	virtual void bfmeSlot25VUQ();
	virtual void bfmeSlot26VUQ();
	virtual void bfmeQuietVUQ(int a, int b, int c);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class BfmeBaseVUQ
{
public:
	__forceinline ~BfmeBaseVUQ() { m_bfmeVftVUQ = bfmeVft2VUQ; }

	void *volatile m_bfmeVftVUQ;
};

class BfmeHostVUQ : public BfmeBaseVUQ
{
public:
	~BfmeHostVUQ();

	BfmeStrVUQ m_bfmeNameVUQ;
	unsigned char m_bfmePadAVUQ[0xc];
	BfmeRefVUQ m_bfmeRefVUQ;
	unsigned char m_bfmePadBVUQ[0x14];
	unsigned int m_bfmeModeVUQ;
};

BfmeHostVUQ::~BfmeHostVUQ()
{
	m_bfmeVftVUQ = bfmeVft1VUQ;

	if (TheAudioClientUpdate != 0 && m_bfmeModeVUQ >= 5)
	{
		BfmeObjVUQ *obj = m_bfmeRefVUQ.m_bfmePtrVUQ;

		if (obj != 0 && obj->m_bfmeFlagVUQ == 0)
			TheAudioClientUpdate->bfmeQuietVUQ(1, 1, 0);
		else
			TheAudioClientUpdate->bfmeStopVUQ(m_bfmeModeVUQ);

		m_bfmeModeVUQ = 1;
	}
}
