// ?bfmeCalcHL@BfmeStateHL@@QAE?AVBfmeVec3HL@@H@Z
// partial score=0.85 date=2026-09-08
extern const float g_bfmeK1253;
extern float g_bfmeDefaultBU;

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadHL[0xab4];
	float m_bfmeRateHL;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class BfmeVec3HL
{
public:
	BfmeVec3HL(float x, float y, float z)
	{
		m_bfmeXHL = x;
		m_bfmeYHL = y;
		m_bfmeZHL = z;
	}

	float m_bfmeXHL;
	float m_bfmeYHL;
	float m_bfmeZHL;
};

class BfmeSlotHL
{
public:
	unsigned char m_bfmeGapHL[4];
};

class BfmeBHL
{
public:
	unsigned char m_bfmeHeadHL[0x18];
	BfmeSlotHL m_bfmeSlotHL;
};

BfmeVec3HL __stdcall bfmeComputeHL(int p, void *a, float f, BfmeSlotHL *s);

static __forceinline BfmeSlotHL *bfmeSlotHL(BfmeBHL *p)
{
	if (p != 0)
		return &p->m_bfmeSlotHL;

	return 0;
}

class BfmeStateHL
{
public:
	BfmeVec3HL bfmeCalcHL(int p);

	unsigned char m_bfmeHeadHL[0x134];
	int m_bfme134HL;
	unsigned char m_bfmeGap2HL[0x88];
	void *m_bfme1c0HL;
	BfmeBHL *m_bfme1c4HL;
};

BfmeVec3HL BfmeStateHL::bfmeCalcHL(int p)
{
	BfmeStateHL *self = this;

	if (self->m_bfme1c0HL != 0)
	{
		BfmeBHL *b = self->m_bfme1c4HL;

		if (b != 0)
		{
			float f = (TheWritableGlobalData->m_bfmeRateHL + g_bfmeDefaultBU) * g_bfmeK1253;

			return bfmeComputeHL(p, &self->m_bfme134HL, f, bfmeSlotHL(b));
		}
	}

	return BfmeVec3HL(0, 0, 0);
}
