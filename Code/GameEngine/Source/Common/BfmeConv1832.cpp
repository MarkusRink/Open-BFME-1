void * __cdecl bfmeCall1VW(void *end, void *x, void *sixth, void *seventh);
void __cdecl bfmeCall2VW(void *out, void *made, void *end, void *second, void *third, void *fourth, void *x, void *fifth);

void * __stdcall bfmeMakeVW(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh)
{
	char buffer[0x40];
	void *x = ((void **)fourth)[1];
	void *made = bfmeCall1VW(buffer + 0x40, x, sixth, seventh);

	bfmeCall2VW(out, made, buffer + 0x40, second, third, fourth, x, fifth);

	return out;
}
