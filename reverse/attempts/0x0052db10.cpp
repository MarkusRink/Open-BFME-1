// ?bfmeGetDM@@YADPAXHPAVStringBaseG@@@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 135/136. The whole shape matches: a count call, the two-sided bound check,
// an sret StringBase<G> returned by value into the dead argument slot and fed
// straight to `set` (retail reuses the sret return in eax, so the
// [[bind-temporary-to-const-ref]] lever is NOT wanted here), then the temp's
// destructor and the char return.
// The single byte is [[zero-materialisation-is-unstable]]: retail keeps 0 in
// EBX (push ebx / xor ebx,ebx) and uses it for both `cmp ecx,ebx` and the
// return-0 (`mov al,bl`); MSVC never allocates the register and uses immediates,
// saving the push/pop but costing the match.
class StringBaseG
{
public:
	void set(const StringBaseG &other);

	~StringBaseG() { releaseBuffer(); }

	void *m_bfmeBufDM;

private:
	void releaseBuffer();
};

extern "C" int __cdecl bfmeCountDM(void *ctx);
extern "C" StringBaseG __cdecl bfmeFetchDM(void *ctx, int index, int mode);

char __cdecl bfmeGetDM(void *ctx, int index, StringBaseG *out)
{
	int count = bfmeCountDM(ctx);

	if (index < 0 || index >= count)
		return 0;

	out->set(bfmeFetchDM(ctx, index, 2));

	return 1;
}
