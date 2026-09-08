// ?bfmeDoSixRC@@YAXPAX0000H@Z
// partial score=0.99 date=2026-09-08
// stlport

typedef void *(__cdecl *BfmeLookupRC)(void *, void *);
extern BfmeLookupRC g_lookup;

struct BfmeAsciiRC
{
	void *m_data;

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}
};

struct BfmeStringLookUpRC
{
	BfmeAsciiRC *m_label;
	void *m_info;
};

struct BfmeStringCompareRC
{
	void *m_state;
};

extern BfmeStringLookUpRC *__cdecl GameTextLowerBound004371E0(
	BfmeStringLookUpRC *, BfmeStringLookUpRC *, const char *const &,
	BfmeStringCompareRC, int *);
extern BfmeStringLookUpRC *__cdecl GameTextUpperBound00437260(
	BfmeStringLookUpRC *, BfmeStringLookUpRC *, const char *const &,
	BfmeStringCompareRC, int *);

static __forceinline void bfmeStoreRangeRC(
	BfmeStringLookUpRC *left, BfmeStringLookUpRC *right, void *out)
{
				BfmeStringLookUpRC **destination =
					(BfmeStringLookUpRC **)out;
				destination[0] = left;
				destination[1] = right;
}

void bfmeDoSixRC(void *out, void *firstArg, void *lastArg,
	void *valueArg, void *compareArg, int)
{
	BfmeStringLookUpRC *first = (BfmeStringLookUpRC *)firstArg;
	BfmeStringLookUpRC *last = (BfmeStringLookUpRC *)lastArg;
	const char *const &value = *(const char *const *)valueArg;
	int length = last - first;
	if (length > 0)
	{
		for (;;)
		{
			const char *key = value;
			int half = length >> 1;
			BfmeStringLookUpRC *middle = first + half;
			if ((int)g_lookup((void *)middle->m_label->str(),
				(void *)key) < 0)
			{
				first = middle + 1;
				length = length - half - 1;
			}
			else
			{
				const char *secondKey = value;
				if ((int)g_lookup((void *)secondKey,
				(void *)middle->m_label->str()) < 0)
				{
					length = half;
				}
				else
				{
				BfmeStringLookUpRC *left = GameTextLowerBound004371E0(
					first, middle, value,
					*(BfmeStringCompareRC *)&compareArg, 0);
				BfmeStringLookUpRC *right = GameTextUpperBound00437260(
					middle + 1, first + length, value,
					*(BfmeStringCompareRC *)&compareArg, 0);
				bfmeStoreRangeRC(left, right, out);
				return;
				}
			}
			if (length <= 0)
				break;
		}
	}
	((BfmeStringLookUpRC **)out)[0] = first;
	((BfmeStringLookUpRC **)out)[1] = first;
}
