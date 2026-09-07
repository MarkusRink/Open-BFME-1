void * __cdecl bfmeCall1VY(void *end, void *x, void *sixth, void *seventh);
void __cdecl bfmeCall2VY(void *out, void *made, void *end, void *second, void *third, void *fourth, void *x, void *fifth);

void * __stdcall bfmeMakeVY(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh)
{
	char buffer[0x40];
	void *x = ((void **)fourth)[1];
	void *made = bfmeCall1VY(buffer + 0x40, x, sixth, seventh);

	bfmeCall2VY(out, made, buffer + 0x40, second, third, fourth, x, fifth);

	return out;
}
