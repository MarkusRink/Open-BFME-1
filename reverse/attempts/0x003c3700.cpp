// ?bfmeDoXY@@YGXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 28/28 bytes; TWO instructions differ and only by register name: retail holds
// the target in edx (mov edx,[esp+8] / push edx), MSVC in ecx.
// The shape is settled: a 2-byte struct built in a push-ecx local with two
// byte stores, read back as a dword and pushed by value, then a __stdcall with
// (target, pair). Naming the target in a local first changes nothing.
// Lone ecx/edx scratch flip -- see the ecx-edx-flip note; toolchain, not source.
struct BfmePairXY
{
	char m_bfmeFirstXY;
	char m_bfmeSecondXY;
};

void __stdcall bfmeSendXY(void *target, BfmePairXY pair);

void __stdcall bfmeDoXY(void *target)
{
	BfmePairXY pair;

	pair.m_bfmeFirstXY = 1;
	pair.m_bfmeSecondXY = 0;

	bfmeSendXY(target, pair);
}
