// ?bfmeInternAttributeEntry@@YAIPAVGen00043699@@@Z
// partial score=0.75 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

class Gen00043699
{
public:
	bool operator==(const Gen00043699 &other) const;

	unsigned char m_data[0x84];
	int m_useCount;
};

class BfmeFalseType
{
};

class BfmeAttributePool
{
public:
	void insertOverflow(Gen00043699 *position,
		const Gen00043699 &value, const BfmeFalseType &tag,
		UnsignedInt count, bool last);

	Gen00043699 *m_start;
	Gen00043699 *m_finish;
	Gen00043699 *m_end;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern void bfmeConstructAttributeEntry(Gen00043699 *destination,
	const Gen00043699 &source);

UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry)
{
	BfmeFalseType tag;
	register unsigned char *cursor =
		(unsigned char *)TheBfmeAttributePool.m_start;
	int count = TheBfmeAttributePool.m_finish
		- (Gen00043699 *)cursor;
	for (register int index = 0; index < count; ++index)
	{
		if (*(Gen00043699 *)cursor == *entry)
		{
			++*(UnsignedInt *)((char *)TheBfmeAttributePool.m_start
				+ index * 0x88 + 0x84);
			return index;
		}
		cursor += 0x88;
	}

	entry->m_useCount = 1;
	if (TheBfmeAttributePool.m_finish != TheBfmeAttributePool.m_end)
	{
		bfmeConstructAttributeEntry(TheBfmeAttributePool.m_finish, *entry);
		TheBfmeAttributePool.m_finish += 1;
	}
	else
	{
		TheBfmeAttributePool.insertOverflow(TheBfmeAttributePool.m_finish,
			*entry, tag, 1, true);
	}

	return (TheBfmeAttributePool.m_finish - TheBfmeAttributePool.m_start) - 1;
}
