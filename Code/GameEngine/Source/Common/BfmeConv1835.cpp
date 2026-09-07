void * __cdecl bfmeCall1WA(void *end, void *x, void *sixth);
void __cdecl bfmeCall2WA(void *out, void *sixth, void *end, void *second, void *third, void *fourth, void *x, void *fifth);

void * __stdcall bfmeMakeWA(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth)
{
	char buffer[0x40];
	void *x = ((void **)fourth)[1];

	void *made = bfmeCall1WA(buffer + 0x40, x, sixth);

	bfmeCall2WA(out, made, buffer + 0x40, second, third, fourth, x, fifth);

	return out;
}
