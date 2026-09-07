void * __cdecl bfmeCall1VX(void *end, void *x, void *sixth);
void __cdecl bfmeCall2VX(void *out, void *sixth, void *end, void *second, void *third, void *fourth, void *x, void *fifth);

void * __stdcall bfmeMakeVX(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth)
{
	char buffer[0x40];
	void *x = ((void **)fourth)[1];

	void *made = bfmeCall1VX(buffer + 0x40, x, sixth);

	bfmeCall2VX(out, made, buffer + 0x40, second, third, fourth, x, fifth);

	return out;
}
