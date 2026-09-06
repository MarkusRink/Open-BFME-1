// ?d_008956c0@@YAXXZ
// partial score=0.90 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}
};

class BfmeCandidateValue
{
public:
	BfmeCandidateValue(BfmeDropObjectA *candidate)
		: m_candidate(candidate)
	{
		if (candidate)
			++*(int *)candidate;
	}

	BfmeCandidateValue(const BfmeCandidateValue &other)
		: m_candidate(other.m_candidate)
	{
	}

	~BfmeCandidateValue(void)
	{
		if (m_candidate && --*(int *)m_candidate == 0)
			delete m_candidate;
	}

	BfmeDropObjectA *m_candidate;
};

class Rva00895510
{
public:
	int match(BfmeCandidateValue candidate);
};

struct Gen_008956C0Holder
{
	void *m_unused;
	Rva00895510 *m_matcher;
};

struct Gen_008956C0Node
{
	Gen_008956C0Holder *m_holder;
	Gen_008956C0Node *m_next;
};

class Gen_008956C0
{
public:
	int contains(BfmeDropObjectA *candidate);

	Gen_008956C0Node *m_head;
};

int Gen_008956C0::contains(BfmeDropObjectA *candidate)
{
	Gen_008956C0Node *node = m_head;
	if (node)
	{
		BfmeCandidateValue hold(candidate);
		while (node)
		{
			if (node->m_holder->m_matcher->match(hold))
				return 1;
			node = node->m_next;
		}
	}
	return 0;
}
