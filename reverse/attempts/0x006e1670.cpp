// ?bfmeTickAZ@BfmeThingAZ@@QAEXXZ
// partial score=0.85 date=2026-09-08
struct BfmeModeAZC
{
	void bfmeNotifyAZ(int a);

	unsigned char m_bfmeGapAZ[0xc];
	int m_bfmeStateAZ;
};

extern BfmeModeAZC *g_bfmeModeAZC;

class BfmeThingAZ
{
public:
	void bfmeTickAZ();

	unsigned char m_bfmeHeadAZ[0xc];
	int m_bfmeStateAZ;
	int m_bfmePhaseAZ;
	int m_bfmeTimerAZ;
};

void BfmeThingAZ::bfmeTickAZ()
{
	if (g_bfmeModeAZC->m_bfmeStateAZ == 4 && m_bfmeStateAZ != 4)
	{
		m_bfmePhaseAZ = 1;
		m_bfmeStateAZ = 4;
		m_bfmeTimerAZ = 0xff;
	}

	if (m_bfmePhaseAZ != 0)
	{
		if (m_bfmePhaseAZ == 1)
		{
			if (--m_bfmeTimerAZ <= 0)
			{
				m_bfmeTimerAZ = 0;
				m_bfmePhaseAZ = 0;

				if (g_bfmeModeAZC->m_bfmeStateAZ == 4)
					g_bfmeModeAZC->bfmeNotifyAZ(0);

				m_bfmeStateAZ = 0;
			}
		}
	}
}
