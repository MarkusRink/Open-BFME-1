// ?copyWords@@YAXPAG00@Z
// partial score=0.8 date=2026-09-06
void copyWords(unsigned short* first, unsigned short* last, unsigned short* dst)
{
	for (int n = last - first; n > 0; --n)
		*dst++ = *first++;
}
