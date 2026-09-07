// ?bfmeUnlinkZN@@YGXPAXPAPAUBfmeNodeZN@@PAU1@00@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 55/56, one byte short. The whole shape is solved:
//   * the "pointer to the link that points at target" idiom -- `edx` starts as
//     the head-pointer ARGUMENT and becomes `(Node **)cur` inside the loop,
//     which works only because next sits at offset 0, so &cur->next == cur.
//   * `while (cur != target) { if (cur == 0) return; link = &cur->next;
//     cur = *link; }` then `bfmeDoZN(a, link, chosen ? chosen : fallback)`.
//   * __stdcall, five args, ret 0x14.
// The gap: retail keeps `target` in ESI (push esi / pop esi, 2 bytes) and needs
// only a 1-byte `nop` to 16-align the loop head; MSVC keeps it in ecx, needs no
// save, and pays a 2-byte `mov edi,edi` filler instead -- net one byte short.
// The loop has no calls and exactly three live values (link, cur, target), so
// nothing forces a callee-saved register. Tried: `*(T *volatile *)&target`
// ([[volatile-cast-pins-parameter]]) both before and after the `cur`
// declaration, and /G5 and /G6 -- all still 55 bytes with target in ecx.
// [[loop-align-nop-reproduces]] explains why the filler size follows the
// register choice rather than being independently fixable.
struct BfmeNodeZN
{
	BfmeNodeZN *m_bfmeNextZN;
};

void __stdcall bfmeDoZN(void *a, BfmeNodeZN **link, void *what);

void __stdcall bfmeUnlinkZN(void *a, BfmeNodeZN **link, BfmeNodeZN *target,
                            void *fallback, void *chosen)
{
	BfmeNodeZN *cur = *link;

	while (cur != target)
	{
		if (cur == 0)
			return;

		link = &cur->m_bfmeNextZN;
		cur = *link;
	}

	bfmeDoZN(a, link, chosen != 0 ? chosen : fallback);
}
