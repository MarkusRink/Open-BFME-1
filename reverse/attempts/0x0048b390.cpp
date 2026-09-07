// ?bfmeCopyRK@BfmeSourceRK@@QAEXPAUBfmeListRK@@@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 79/79 bytes; every instruction of the body matches. The only difference is
// the ORDER of the callee-saved pushes:
//   retail  push ecx / push ebx / push ebp / push esi / (test) / push edi
//   ours    push ecx / push esi / (test) / push ebx / push ebp / push edi
// so retail saves three registers before the empty-list test and we shrink-wrap
// two of them past it.
// Settled: _STL::__new_alloc::allocate(12) declared as a static member so the
// mangled name matches, placement new through
// `inline void *__cdecl operator new(unsigned int, void *)` (that is what emits
// `lea ecx,[eax+8]; test ecx,ecx; je`), the value read into a local BEFORE the
// allocate, and head->m_prev hoisted into a local so it is read once.
// Tried: naming the destination in a local before the loop, and the while form
// instead of for. Both leave the same 12 differing lines.
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

}

inline void * __cdecl operator new(unsigned int size, void *place) { return place; }

struct BfmeValueRK
{
	BfmeValueRK(void *raw) { m_bfmeRawRK = raw; }

	void *m_bfmeRawRK;
};

struct BfmeNodeRK
{
	BfmeNodeRK *m_bfmeNextRK;
	BfmeNodeRK *m_bfmePrevRK;
	BfmeValueRK m_bfmeValueRK;
};

struct BfmeListRK
{
	BfmeNodeRK *m_bfmeHeadRK;
};

class BfmeSourceRK
{
public:
	void bfmeCopyRK(BfmeListRK *dest);

	int m_bfmeSpareRK;
	BfmeNodeRK *m_bfmeSentinelRK;
};

void BfmeSourceRK::bfmeCopyRK(BfmeListRK *dest)
{
	BfmeNodeRK *item;

	for (item = m_bfmeSentinelRK->m_bfmeNextRK; item != m_bfmeSentinelRK; item = item->m_bfmeNextRK)
	{
		void *value = item->m_bfmeValueRK.m_bfmeRawRK;
		BfmeNodeRK *head = dest->m_bfmeHeadRK;
		BfmeNodeRK *node = (BfmeNodeRK *)_STL::__new_alloc::allocate(12);

		new (&node->m_bfmeValueRK) BfmeValueRK(value);

		BfmeNodeRK *prev = head->m_bfmePrevRK;

		node->m_bfmeNextRK = head;
		node->m_bfmePrevRK = prev;
		prev->m_bfmeNextRK = node;
		head->m_bfmePrevRK = node;
	}
}
