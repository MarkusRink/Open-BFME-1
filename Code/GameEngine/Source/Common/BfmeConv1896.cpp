extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

class BfmeNodeAK
{
public:
	void **m_bfmeBeginAK;
	void **m_bfmeEndAK;
	void **m_bfmeCapAK;
	void *m_bfmeKeyAK;
	BfmeNodeAK *m_bfmeNextAK;
};

class BfmeListAK
{
public:
	int bfmeDropAK(void *key, void *value);

	BfmeNodeAK *m_bfmeHeadAK;
	BfmeNodeAK *m_bfmeRootAK;
};

int BfmeListAK::bfmeDropAK(void *key, void *value)
{
	BfmeNodeAK *n = m_bfmeRootAK;

	m_bfmeHeadAK = n;

	while (n != 0)
	{
		if (n->m_bfmeKeyAK == key)
		{
			for (void **p = n->m_bfmeBeginAK; p != n->m_bfmeEndAK; p++)
			{
				if (*p == value)
				{
					void **next = p + 1;

					if (n->m_bfmeEndAK != next)
						BfmeMemMove(p, next, (char *)n->m_bfmeEndAK - (char *)next);

					n->m_bfmeEndAK--;
					return 1;
				}
			}
		}

		n = n->m_bfmeNextAK;
	}

	return 0;
}
