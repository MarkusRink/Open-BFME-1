// ?bfmeAnyZQ@BfmeOwnerZQ@@QAEDPAX0@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 74/74, exact size and instruction count. Circular-list walk fully recovered:
// the sentinel is the POINTER at this+0x288 (not the address of it), next sits
// at node+0 and the item at node+8, and the source spells the member each time
// -- MSVC caches it for the entry compare and re-reads it for the loop-end
// compare on its own, because the call could change it.
// Residue is four lines of pure [[argument-shuttle-register]] naming:
//   retail  ebx <- [esp+0x14] (a), ebp <- [esp+0x18] (b), push ebp / push ebx
//   MSVC    ebx <- [esp+0x18] (b), ebp <- [esp+0x14] (a), push ebx / push ebp
// Same push order, same size, only which callee-saved register holds which
// argument. Naming both in locals with the declaration order reversed does not
// move it (MSVC coalesces), and neither does reading both through
// *(void *volatile *)& to pin the load order.
class BfmeItemZQ
{
public:
	char bfmeTestZQ(void *a, void *b);
};

struct BfmeNodeZQ
{
	BfmeNodeZQ *m_bfmeNextZQ;
	unsigned char m_bfmePadZQ[4];
	BfmeItemZQ *m_bfmeItemZQ;
};

class BfmeOwnerZQ
{
public:
	char bfmeAnyZQ(void *a, void *b);

	unsigned char m_bfmeHeadZQ[0x288];
	BfmeNodeZQ *m_bfmeListZQ;
};

char BfmeOwnerZQ::bfmeAnyZQ(void *a, void *b)
{
	BfmeNodeZQ *node = m_bfmeListZQ->m_bfmeNextZQ;

	while (node != m_bfmeListZQ)
	{
		if (node->m_bfmeItemZQ->bfmeTestZQ(a, b) != 0)
			return 1;

		node = node->m_bfmeNextZQ;
	}

	return 0;
}
