// ?bfmeCheckWD@@YGHHH@Z (identity unknown)
// partial score=0.75 date=2026-09-07
// 73/81 bytes. The call shape is worked out: a __stdcall taking SIX arguments,
// pushed so that left-to-right they are
//   (a1 by value, a2 by value, &localAtE-4, &a2's slot, &a1's slot, &localAtE-5)
// -- i.e. the two incoming parameter slots are handed to the callee as
// bool out-parameters and read back afterwards as BYTES:
//   [E+8] tested first, then [E+4], then the byte local at E-5.
// The byte local at E-4 is written by the callee and never read.
// What is not modelled: retail reserves EIGHT bytes (`sub esp,8`) and uses only
// E-5 and E-4 of them, leaving E-8..E-6 dead, while four `bool` locals make
// MSVC reserve four (`push ecx`) and spread them differently. Something in the
// original gives those two bytes a wider or aligned home.
void __stdcall bfmeQueryWD(int first, int second, bool *fourth, bool *secondOut, bool *firstOut, bool *third);

int __stdcall bfmeCheckWD(int first, int second)
{
	bool third;
	bool fourth;
	bool firstOut;
	bool secondOut;

	bfmeQueryWD(first, second, &fourth, &secondOut, &firstOut, &third);

	if (!secondOut)
		return 0;

	if (!firstOut)
		return 0;

	if (third)
		return 0;

	return 1;
}
