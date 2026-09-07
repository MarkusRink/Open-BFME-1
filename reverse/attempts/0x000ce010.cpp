// ?d_000ce010@@YAXXZ
// partial score=0.97 date=2026-09-08
class BfmeItemEAK
{
public:
	char bfmeTestEAK(void *a, void *b);
};

class BfmeNodeEAK
{
public:
	BfmeNodeEAK *m_bfmeNextEAK;
	int m_bfmePadEAK;
	BfmeItemEAK *m_bfmeItemEAK;
};

class BfmeHostEAK
{
public:
	char bfmeAnyEAK(void *a, void *b);

	unsigned char m_bfmeHeadEAK[0x288];
	BfmeNodeEAK *m_bfmeListEAK;
};

char BfmeHostEAK::bfmeAnyEAK(void *a, void *b)
{
	BfmeNodeEAK *node = m_bfmeListEAK->m_bfmeNextEAK;

	while (node != m_bfmeListEAK)
	{
		if (node->m_bfmeItemEAK->bfmeTestEAK(a, b))
			return 1;

		node = node->m_bfmeNextEAK;
	}

	return 0;
}
