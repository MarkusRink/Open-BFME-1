class BfmeThingAIA;
struct BfmeSlotAIA;

int bfmeTryAIA(BfmeThingAIA *who, BfmeSlotAIA *slot);

class BfmeFoundXF
{
public:
	void *m_bfmePadXF[0x1d];
	void *m_bfmeTagXF;
};

struct BfmeSlotXF
{
	void *m_bfmeWantXF;
	BfmeFoundXF *m_bfmeHaveXF;
};

class BfmeLogicXF
{
public:
	void bfmeNoteXF(void *tag);
};

extern BfmeLogicXF *TheBfmeLogicXF;

class BfmeOwnerXF
{
public:
	void bfmeFindXF();
	void bfmeStepXF(void *routine, void *state);

	unsigned char m_bfmeHeadXF[0x63c];
	void *volatile m_bfmeTagXF;
};

void BfmeOwnerXF::bfmeFindXF()
{
	if (m_bfmeTagXF == 0)
	{
		BfmeSlotXF slot;

		slot.m_bfmeWantXF = this;
		slot.m_bfmeHaveXF = 0;
		bfmeStepXF((void *)bfmeTryAIA, &slot);

		if (slot.m_bfmeHaveXF != 0)
			m_bfmeTagXF = slot.m_bfmeHaveXF->m_bfmeTagXF;
	}

	TheBfmeLogicXF->bfmeNoteXF(m_bfmeTagXF);
}
