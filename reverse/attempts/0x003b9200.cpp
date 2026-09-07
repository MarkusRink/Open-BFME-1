// ?rva003B9200Contains@Rva003B9200Owner@@QAE_NPAVRva003B9200Predicate@@@Z
// partial score=0.4 date=2026-09-06
// ?rva003B9200Contains@Rva003B9200Owner@@QBE_NPAVRva003B9200Predicate@@@Z
// Address-derived: linear scan over a pointer array [m_begin, m_end) (4-byte
// elements), calling the already-named thunk 0x000202BB as pred->matches(*it)
// for each element; returns true on the first match, false if the array is
// exhausted. The element count is recomputed from m_begin/m_end every
// iteration rather than cached, matching retail's re-read.
class Rva003B9200Predicate
{
public:
	bool matches(void *element);
};

class Rva003B9200Owner
{
public:
	unsigned char m_pad0[0xc];
	void **m_begin;
	char *m_end;

	bool rva003B9200Contains(Rva003B9200Predicate *pred);
};

bool Rva003B9200Owner::rva003B9200Contains(Rva003B9200Predicate *pred)
{
	void **it = m_begin;
	int count = (int)(m_end - (char *)m_begin) >> 2;
	if (count <= 0)
		return false;

	int i = 0;
	do
	{
		if (pred->matches(*it))
			return true;
		count = (int)(m_end - (char *)m_begin) >> 2;
		++i;
		++it;
	} while (i < count);

	return false;
}
