class BfmeSubAAY
{
public:
	void bfmeCloseAAY();
};

struct Rva00367E30Logic
{
	void bfmeResetAAY();
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Gen_00609320
{
public:
	virtual void bfmeSlot0AAY();
	virtual void bfmeSlot1AAY();
	virtual void bfmeSlot2AAY();
	virtual void bfmeFinishAAY();
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeHostAAY
{
public:
	void bfmeShutdownAAY();

	void bfmeStep1AAY();
	void bfmeStep2AAY();
	void bfmeStep3AAY();
	void bfmeStep4AAY();
	void bfmeStep5AAY();
	void bfmeStep6AAY();

	unsigned char m_bfmeHeadAAY[0x288];
	unsigned char m_bfme288AAY;
	unsigned char m_bfmePadAAY[3];
	BfmeSubAAY *m_bfme28CAAY;
};

void BfmeHostAAY::bfmeShutdownAAY()
{
	bfmeStep1AAY();
	bfmeStep2AAY();
	bfmeStep3AAY();
	bfmeStep4AAY();

	BfmeSubAAY *s = m_bfme28CAAY;

	if (s != 0)
		s->bfmeCloseAAY();

	bfmeStep5AAY();
	bfmeStep6AAY();

	if (TheBfmeGameLogic != 0)
		TheBfmeGameLogic->bfmeResetAAY();

	if (g_bfmeStateDF != 0)
		g_bfmeStateDF->bfmeFinishAAY();

	m_bfme288AAY = 0;
}
