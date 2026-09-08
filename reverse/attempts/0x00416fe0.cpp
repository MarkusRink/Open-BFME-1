// ?d_00416fe0@@YAXXZ
// partial score=0.85 date=2026-09-08
class AudioEventRTS;
class AsciiStringTU;
class BfmeSubTU;
class BfmeParentTU;

extern AudioEventRTS BfmeTheEmptyAudioEvent;

class BfmeFinderTU
{
public:
	virtual void bfmeSlotB00TU();
	virtual const AudioEventRTS *bfmeFindTU(const AsciiStringTU &name);
};

class BfmeEntryTU
{
public:
	virtual void bfmeSlotA00TU();
	virtual void bfmeSlotA01TU();
	virtual void bfmeSlotA02TU();
	virtual void bfmeSlotA03TU();
	virtual void bfmeSlotA04TU();
	virtual void bfmeSlotA05TU();
	virtual void bfmeSlotA06TU();
	virtual void bfmeSlotA07TU();
	virtual void bfmeSlotA08TU();
	virtual void bfmeSlotA09TU();
	virtual void bfmeSlotA10TU();
	virtual BfmeFinderTU *bfmeGetFinderTU();
};

BfmeParentTU *__fastcall bfmeResolveTU(BfmeSubTU *sub);

class BfmeParentTU
{
public:
	const AudioEventRTS *bfmeLookupTU(const AsciiStringTU &name);

	int m_bfmeHeadTU;
	BfmeSubTU *m_bfmeSubTU;
};

__forceinline BfmeParentTU *bfmeBaseTU(BfmeParentTU *p)
{
	if (p->m_bfmeSubTU != 0)
		return bfmeResolveTU(p->m_bfmeSubTU);

	return p;
}

class BfmeTemplateTU
{
public:
	const AudioEventRTS *bfmeGetSoundTU(const AsciiStringTU &name) const;

	int m_bfmeHeadTU;
	BfmeParentTU *m_bfmeParentTU;
	unsigned char m_bfmePadTU[0x150];
	BfmeEntryTU **m_bfmeSoundsTU;
};

const AudioEventRTS *BfmeTemplateTU::bfmeGetSoundTU(const AsciiStringTU &name) const
{
	BfmeEntryTU **p = m_bfmeSoundsTU;

	if (p != 0)
	{
		while (*p != 0)
		{
			BfmeFinderTU *f = (*p)->bfmeGetFinderTU();

			if (f != 0)
			{
				const AudioEventRTS *r = f->bfmeFindTU(name);

				if (r != 0)
					return r;
			}

			p++;
		}
	}

	BfmeParentTU *parent = m_bfmeParentTU;
	BfmeParentTU *base = parent != 0 ? bfmeBaseTU(parent) : 0;

	const AudioEventRTS *r = base->bfmeLookupTU(name);

	if (r != 0)
		return r;

	return &BfmeTheEmptyAudioEvent;
}
