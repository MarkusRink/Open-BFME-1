struct BfmeSubJX
{
	int m_bfmeGapJX[14];
	int m_bfme38JX;
};

struct CodecState
{
	unsigned char m_bfmeHeadJX[0x13c];
	BfmeSubJX *m_bfme13cJX;
	unsigned char m_bfmeGap0JX[0x64];
	int m_bfme1a4JX;
	int m_bfme1a8JX;
	unsigned char m_bfmeGap1JX[4];
	int m_bfme1b0JX;
	int m_bfme1b4JX;
	unsigned char m_bfmeGap2JX[0x7c];
	int m_bfme234JX;
	int m_bfme238JX;
	int m_bfme23cJX;
	int m_bfme240JX;
	unsigned char m_bfmeGap3JX[0x50];
	void *m_bfme294JX;
	void *m_bfme298JX;
};

extern int g_bfmeSharedJX;

class BfmeThingJT;

extern "C" void *__cdecl memcpy(void *d, const void *s, unsigned int n);
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

struct CodecState;

CodecState *bfmeAllocJX();

extern int g_bfmeTableJX;

int bfmeAllocJT(BfmeThingJT *q);
void bfmeFreeOneJT(void *q);

class Bucket
{
public:
	enum BucketMagicEnum { BFME_ZERO_JX = 0 };

	static void *operator new(unsigned int n, BucketMagicEnum m);
};
void *bfmeMakeBZB(void *q);
BfmeSubJX *bfmeMakeSubJX();
int bfmeCheckJX(CodecState *s);
class Rva009A8C30Owner;

void Rva009A8C30(Rva009A8C30Owner *s);
struct BfmeHolderBZB;

void Rva009A6EC0Release(void **q);
void bfmeGoBZB(BfmeHolderBZB *h);
void bfmeStepJW(void *q);
void Rva009A8880Release(void *q);
void releaseCodecState(CodecState **q);

int bfmeFreeCodecJW(CodecState **p)
{
	if (*p != 0)
	{
		Rva009A6EC0Release((void **)((char *)*p + 0x13c));
		bfmeGoBZB((BfmeHolderBZB *)((char *)*p + 0x298));
		bfmeStepJW(*p);
		Rva009A8880Release(*p);
		releaseCodecState(p);
	}

	return 1;
}

int bfmeInitCodecJX(CodecState **p, int a, int b)
{
	*p = bfmeAllocJX();

	(*p)->m_bfme234JX = a;
	(*p)->m_bfme238JX = b;
	(*p)->m_bfme23cJX = a;
	(*p)->m_bfme240JX = b;
	(*p)->m_bfme1b0JX = a;
	(*p)->m_bfme1b4JX = b;
	(*p)->m_bfme298JX = bfmeMakeBZB((char *)*p + 0x1b0);
	(*p)->m_bfme13cJX = bfmeMakeSubJX();
	(*p)->m_bfme1a4JX = g_bfmeSharedJX;

	if (bfmeCheckJX(*p) == 0)
	{
		releaseCodecState(p);

		return 0;
	}

	(*p)->m_bfme13cJX->m_bfme38JX = 0;

	Rva009A8C30((Rva009A8C30Owner *)*p);

	return 1;
}

CodecState *bfmeAllocJX()
{
	int cfg[14];

	cfg[0] = 0;
	cfg[1] = 0;
	cfg[2] = 0;
	cfg[3] = 0;
	cfg[4] = 8;
	cfg[5] = 8;
	cfg[6] = 0;
	cfg[7] = 0;
	cfg[8] = 0;
	cfg[9] = 0;
	cfg[10] = 0;
	cfg[11] = 0;
	cfg[12] = 0;
	cfg[13] = 0;

	CodecState *p = (CodecState *)Bucket::operator new(0x4954, Bucket::BFME_ZERO_JX);

	if (p == 0)
		return 0;

	memset(p, 0, 0x1255 * 4);
	memcpy((char *)p + 0x1b0, cfg, 14 * 4);

	if (bfmeAllocJT((BfmeThingJT *)p) == 0)
	{
		bfmeFreeOneJT(p);

		return 0;
	}

	p->m_bfme1a8JX = 0x46;
	p->m_bfme294JX = &g_bfmeTableJX;

	memset((char *)p + 0x3a0, 0, 0x16);
	memset((char *)p + 0x3b6, 0, 0x63 * 4);

	return p;
}
