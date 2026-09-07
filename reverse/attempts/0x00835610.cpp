// ?bfmeMakeVW@@YAPAXPAX000000@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 77/79 bytes. THE MODEL FOR A WHOLE FAMILY -- 0x008357B0, 0x00835AA0,
// 0x00835F60, 0x00836000 and 0x00837380 all have this shape.
// It is NOT an sret function: arg1 is an explicit out-pointer that the body
// hands to the second callee and returns unchanged (`mov eax,esi`), which is
// why `ret 1ch` covers seven stack arguments. Modelling it as a struct return
// makes MSVC add a 16-byte temporary (+37 bytes).
// The `lea edx,[esp+50h]` computes ONE PAST the end of a 40h-byte local buffer
// (buffer + 0x40), not a local's address -- the arithmetic lands on the return
// address slot, which is what makes it look wrong.
// Both callees are __cdecl and the caller cleans both at once (`add esp,30h`
// after the second call covers 4 + 8 pushed dwords).
// Residue: retail pre-loads BOTH of the last two arguments into eax and ecx
// before `sub esp,40h`; MSVC loads one there and puts the other in ebx, which
// costs the two bytes and shifts the displacements.
void __cdecl bfmeCall1VW(void *end, void *x, void *sixth, void *seventh);
void * __cdecl bfmeCall2VW(void *out, void *seventh, void *end, void *second, void *third, void *fourth, void *x, void *fifth);

void * __cdecl bfmeMakeVW(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh)
{
	char buffer[0x40];
	void *x = ((void **)fourth)[1];

	bfmeCall1VW(buffer + 0x40, x, sixth, seventh);

	return bfmeCall2VW(out, seventh, buffer + 0x40, second, third, fourth, x, fifth);
}
