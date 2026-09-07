// ?bfmeRemoveAD@@YAHPAXPAPAX@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 99/96. Structure fully recovered and three levers were needed to get here,
// all worth reusing:
//   * the two arrays and the count are ONE global struct at RVA 0x00F563A0
//     (vals[20] at +0, keys[20] at +0x50, count at +0xa0). Retail walks the
//     shift with a single induction pointer and reaches the second array by
//     displacement (`[eax+0x50]` / `[eax+0x54]`), which the compiler can only do
//     if it knows they are adjacent.
//   * the shift loop must use that pointer, not indices: `p[0] = p[1];
//     p[20] = p[21]; p++;`. Written as `vals[j-1] = vals[j]` it emits four
//     separate `[eax*4 + base]` computations and the body is 112 bytes
//     ([[index-gives-compiler-iv-bias]], inverted -- here retail is the pointer).
//   * the count must be cached in a local, else it is re-read every iteration.
//   * the shift counter must REUSE the search index (`for (i = i + 1; ...)`),
//     not a fresh `j`, or MSVC emits `lea edx,[ecx+1]` for the new variable.
// The remaining 3 bytes: MSVC strength-reduces the shift loop to one induction
// pointer plus a down-counter (`mov edx,esi / sub edx,eax` ... `dec edx / jne`)
// where retail keeps TWO induction variables and compares them
// (`add eax,4 / inc ecx / cmp ecx,edx / jl`). One of the 3 bytes is separately
// [[eax-short-form-global]]: retail loads the count into eax (`a1 <abs>`, 5
// bytes) and MSVC into ecx (`8b 0d <abs>`, 6).
struct BfmeTableAD
{
	void *m_bfmeValsAD[20];
	void *m_bfmeKeysAD[20];
	int m_bfmeCountAD;
};

extern BfmeTableAD g_bfmeTableAD;

int __cdecl bfmeRemoveAD(void *key, void **out)
{
	int i;

	for (i = 0; i < g_bfmeTableAD.m_bfmeCountAD; i++)
	{
		if (g_bfmeTableAD.m_bfmeKeysAD[i] == key)
		{
			*out = g_bfmeTableAD.m_bfmeValsAD[i];

			void **p = &g_bfmeTableAD.m_bfmeValsAD[i];
			int count = g_bfmeTableAD.m_bfmeCountAD;

			for (i = i + 1; i < count; i++)
			{
				p[0] = p[1];
				p[20] = p[21];
				p++;
			}

			g_bfmeTableAD.m_bfmeCountAD = count - 1;

			return 0;
		}
	}

	return -1;
}
