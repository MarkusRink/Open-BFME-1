// ??$__insertion_sort@PAHURva004539D0Cmp@@@_STL@@YAXPAH0URva004539D0Cmp@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport __insertion_sort over int with a stateful comparator
// (112 B gap at 0x004539D0 claimed by its shape: inline __linear_insert with
// copy_backward as memmove and the out-of-line __unguarded_linear_insert).
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct Rva004539D0Cmp
{
	void* m_state;
	bool operator()(int left, int right) const;
};
template void _STL::__insertion_sort<int*, Rva004539D0Cmp>(int*, int*, Rva004539D0Cmp);
