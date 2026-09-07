// ?evaluate@Gen009D76F0@@QAEPAXPAX@Z
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /O2
// Address-derived definition of Gen009D76F0::evaluate, declared (but not
// defined) alongside this class in Code/GameEngine/Source/Common/Gen009D7D30.cpp.
// Computes a *5+c string hash over the C-string pointed to by *argument, maps
// it into the bucket array [m_bucketBegin, m_bucketEnd) by unsigned modulo,
// then walks the singly linked chain comparing node keys by pointer identity
// (interned strings) to *argument itself.
struct Gen009D76F0Node
{
	Gen009D76F0Node *m_next;
	char *m_key;
};

class Gen009D76F0
{
public:
	void *evaluate(void *argument);

	Gen009D76F0Node **m_bucketBegin;
	Gen009D76F0Node **m_bucketEnd;
};

void *Gen009D76F0::evaluate(void *argument)
{
	char *str = *(char **)argument;
	int hash = 0;
	char c = *str;
	if (c != 0)
	{
		const char *p = str;
		do
		{
			hash = hash * 5 + c;
			c = p[1];
			++p;
		} while (c != 0);
	}

	int numBuckets = (int)(m_bucketEnd - m_bucketBegin);
	unsigned idx = (unsigned)hash % (unsigned)numBuckets;
	Gen009D76F0Node *node = m_bucketBegin[idx];
	while (node != 0)
	{
		if (node->m_key == str)
			return node;
		node = node->m_next;
	}
	return 0;
}
