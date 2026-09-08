// ?bfmeOnEventGA@@YGXHPAXPBH@Z
// partial score=0.97 date=2026-09-08
struct BfmeMsgGA
{
	int m_bfmeTypeGA;
	int m_bfmePad0GA;
	int m_bfmeAGA;
	int m_bfmePad1GA;
	int m_bfmeBGA;
	unsigned char m_bfmePad2GA[0x80];
	int m_bfmeCGA;
	unsigned char m_bfmePad3GA[0x864 - 0x98];
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void bfmeSlot0GA();
	virtual void bfmeSlot1GA();
	virtual void bfmeSlot2GA();
	virtual void bfmeSlot3GA();
	virtual void bfmeSlot4GA();
	virtual void bfmeSlot5GA();
	virtual void bfmeSlot6GA();
	virtual void bfmeSlot7GA();
	virtual void bfmeAddGA(BfmeMsgGA *m);
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern unsigned char g_bfmeFlagAGA;
extern unsigned char g_bfmeFlagBGA;

void __stdcall bfmeOnEventGA(int code, void *p2, const int *p3)
{
	if (code != 0)
	{
		if (code == 4)
			g_bfmeFlagAGA = 1;

		return;
	}

	if (p3 != 0 && *p3 == -204)
	{
		BfmeMsgGA m;

		m.m_bfmeTypeGA = 6;
		m.m_bfmeCGA = 1;
		g_bfmeFlagBGA = 1;
		m.m_bfmeAGA = 4;
		m.m_bfmeBGA = 6;
		g_bfmeFlagAGA = 0;

		TheGameSpyBuddyMessageQueue->bfmeAddGA(&m);
	}
}
