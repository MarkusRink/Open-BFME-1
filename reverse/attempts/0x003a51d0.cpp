// ?bfmeUpdateAAU@BfmeHostAAU@@QAEXXZ
// partial score=0.91 date=2026-09-08
void __stdcall bfmeRefreshAAU(void);

class Glo012F1028Type
{
public:
	void bfmeNotifyAAU();
};

extern Glo012F1028Type *Glo012F1028;

class BfmeHostAAU
{
public:
	void bfmeUpdateAAU();
	void bfmeStepAAU();
	void bfmeSetAAU(bool on);

	unsigned char m_bfmeHeadAAU[0x1c];
	unsigned char m_bfme1CAAU;
	unsigned char m_bfmeGapAAU[2];
	unsigned char m_bfme1FAAU;
};

void BfmeHostAAU::bfmeUpdateAAU()
{
	if (m_bfme1CAAU == 0)
		bfmeRefreshAAU();

	unsigned char b = m_bfme1CAAU;
	int prev = b;

	if (b != 0)
		bfmeStepAAU();

	unsigned char cur = m_bfme1CAAU;

	if (prev != 0)
	{
		if (cur == 0 && m_bfme1FAAU != 0)
		{
			Glo012F1028->bfmeNotifyAAU();
			m_bfme1FAAU = 0;
		}

		bfmeSetAAU(true);
	}
	else if (cur != 0)
	{
		bfmeSetAAU(true);
	}
	else
	{
		bfmeSetAAU(false);
	}
}
