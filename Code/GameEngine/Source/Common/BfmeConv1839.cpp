void __cdecl bfmeReleaseXC(void *item);

class BfmeStateXC
{
public:
	void bfmeStopXC(void *unused);

	void bfmeNotifyXC(int kind);
	void bfmeApplyXC(void *item, int kind);
	void bfmeFlushXC();
	void bfmeDoneXC();

	unsigned char m_bfmeHeadXC[0x40];
	void *m_bfmeFirstXC;
	void *m_bfmeSecondXC;
	unsigned char m_bfmeMidXC[0x5c];
	int m_bfmeModeXC;
};

void BfmeStateXC::bfmeStopXC(void *unused)
{
	switch (m_bfmeModeXC)
	{
	case 1:
		bfmeApplyXC(m_bfmeFirstXC, 0);
		break;
	case 2:
		bfmeNotifyXC(0);
		break;
	case 3:
		bfmeNotifyXC(1);
		break;
	}

	bfmeFlushXC();
	bfmeReleaseXC(m_bfmeSecondXC);
	bfmeDoneXC();
}
