// cl: /O2 /Ob1 /EHs-c-
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <cstring>
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *dst, const void *src, unsigned int count);
#define memmove (*bfme_memmove_ptr)
#include <algorithm>
#include <vector>
#undef memmove

extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

struct BfmeVectorRawAK
{
	void **m_bfmeBeginAK;
	void **m_bfmeEndAK;
	void **m_bfmeCapAK;
};

class BfmeNodeAK
{
public:
	BfmeNodeAK(void *key);

	_STL::vector<void *> m_bfmeValuesAK;
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

BfmeNodeAK::BfmeNodeAK(void *key)
	: m_bfmeValuesAK()
{
	m_bfmeKeyAK = key;
	m_bfmeValuesAK.clear();
	m_bfmeNextAK = 0;
}

int BfmeListAK::bfmeDropAK(void *key, void *value)
{
	BfmeNodeAK *n = m_bfmeRootAK;

	m_bfmeHeadAK = n;

	while (n != 0)
	{
		if (n->m_bfmeKeyAK == key)
		{
			for (void **p = n->m_bfmeValuesAK.begin(); p != n->m_bfmeValuesAK.end(); p++)
			{
				if (*p == value)
				{
					void **next = p + 1;

					if (n->m_bfmeValuesAK.end() != next)
						BfmeMemMove(p, next, (char *)n->m_bfmeValuesAK.end() - (char *)next);

					((BfmeVectorRawAK *)&n->m_bfmeValuesAK)->m_bfmeEndAK--;
					return 1;
				}
			}
		}

		n = n->m_bfmeNextAK;
	}

	return 0;
}
