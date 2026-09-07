// ?bfmeEqualUW@@YAHPBVBfmeKeyUW@@0@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 50/50 bytes; the SHAPE is exact -- the remaining 8 lines differ only by a
// whole-body ecx/edx swap (retail ecx where we use edx and vice versa).
// Settled: the return type is int (both exits are 32-bit, mov eax,1 and
// xor eax,eax), the kind test must be NESTED with one trailing `return 0` (an
// early `return 0` inlines that block and lets MSVC fold the tail to
// `setne al`, 46 bytes), and the first two arguments must be hoisted into
// locals (`item`, then `data`) so retail's `mov edx,[eax+8]` happens before the
// pushes instead of destroying eax between them.
// Lone ecx/edx scratch flip -- toolchain, not source.
class BfmeItemUW
{
public:
	unsigned char m_bfmeHeadUW[8];
	void *m_bfmeDataUW;
};

class BfmeKeyUW
{
public:
	BfmeItemUW *m_bfmeItemUW;
	int m_bfmeKindUW;
};

char __cdecl bfmeSameUW(void *first, BfmeItemUW *second, void *third);

int __cdecl bfmeEqualUW(const BfmeKeyUW *first, const BfmeKeyUW *second)
{
	if (first->m_bfmeKindUW == second->m_bfmeKindUW)
	{
		BfmeItemUW *item = first->m_bfmeItemUW;
		void *data = item->m_bfmeDataUW;

		if (bfmeSameUW(data, item, second->m_bfmeItemUW->m_bfmeDataUW))
			return 1;
	}

	return 0;
}
