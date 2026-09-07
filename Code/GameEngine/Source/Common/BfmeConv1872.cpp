class BfmeWinZE
{
public:
	virtual void bfmeW0ZE();
	virtual void bfmeW1ZE();
	virtual void bfmeW2ZE();
	virtual void bfmeW3ZE();
	virtual void bfmeW4ZE();
	virtual void bfmeDoneZE();
};

class BfmeManagerZE
{
public:
	virtual void bfmeM00ZE();
	virtual void bfmeM01ZE();
	virtual void bfmeM02ZE();
	virtual void bfmeM03ZE();
	virtual void bfmeM04ZE();
	virtual void bfmeM05ZE();
	virtual void bfmeM06ZE();
	virtual void bfmeM07ZE();
	virtual void bfmeM08ZE();
	virtual void bfmeM09ZE();
	virtual void bfmeM10ZE();
	virtual void bfmeM11ZE();
	virtual void bfmeM12ZE();
	virtual void bfmeM13ZE();
	virtual void bfmeM14ZE();
	virtual void bfmeM15ZE();
	virtual void bfmeM16ZE();
	virtual void bfmeM17ZE();
	virtual void bfmeM18ZE();
	virtual void bfmeM19ZE();
	virtual void bfmeM20ZE();
	virtual void bfmeM21ZE();
	virtual void bfmeM22ZE();
	virtual void bfmeM23ZE();
	virtual void bfmeM24ZE();
	virtual void bfmeM25ZE();
	virtual void bfmeM26ZE();
	virtual void bfmeM27ZE();
	virtual void bfmeM28ZE();
	virtual void bfmeM29ZE();
	virtual void bfmeM30ZE();
	virtual void bfmeM31ZE();
	virtual void bfmeM32ZE();
	virtual void bfmeM33ZE();
	virtual void bfmeM34ZE();
	virtual void bfmeM35ZE();
	virtual void bfmeM36ZE();
	virtual void bfmeM37ZE();
	virtual void bfmeM38ZE();
	virtual void bfmeM39ZE();
	virtual void bfmeM40ZE();
	virtual void bfmeM41ZE();
	virtual void bfmeM42ZE();
	virtual int bfmeBusyZE();
	virtual void bfmeHideZE(BfmeWinZE *win);
};

extern BfmeManagerZE *TheBfmeManagerZE;

char bfmeCheckZE();

class BfmeOwnerZE
{
public:
	void bfmeCloseZE(void *unused);

	unsigned char m_bfmeHeadZE[0x24];
	BfmeWinZE *m_bfmeWinZE;
	char m_bfmeFlagZE;
};

void BfmeOwnerZE::bfmeCloseZE(void *unused)
{
	if (m_bfmeWinZE == 0)
		return;

	if (m_bfmeFlagZE != 0 && TheBfmeManagerZE->bfmeBusyZE() == 0 && bfmeCheckZE() == 0)
		TheBfmeManagerZE->bfmeHideZE(m_bfmeWinZE);

	m_bfmeWinZE->bfmeDoneZE();
}
