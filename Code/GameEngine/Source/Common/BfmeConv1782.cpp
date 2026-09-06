class ClientRoot4120
{
public:
	void bfmeCloseHV(void);
	void bfmeOpenHV(void);
};

extern ClientRoot4120 *TheGameClient;

struct Rva005A63D0Mouse
{
	void bfmeSetHV(int flag);
};

extern Rva005A63D0Mouse *TheMouse;

class BfmeOwnerHV
{
public:
	void bfmeEndHV(int reason);

	unsigned char m_bfmeHeadHV[0x25e];
	unsigned char m_bfmeFlagHV;
	unsigned char m_bfmeGapHV[5];
	int m_bfmeStateHV;
};

void BfmeOwnerHV::bfmeEndHV(int reason)
{
	if (m_bfmeStateHV == 8 && reason == 3)
	{
		if (m_bfmeFlagHV)
			TheGameClient->bfmeCloseHV();
		else
			TheGameClient->bfmeOpenHV();

		TheMouse->bfmeSetHV(0);
		m_bfmeStateHV = 0;
	}
}
