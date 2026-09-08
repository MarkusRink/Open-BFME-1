// ?bfmeReadByteFL@@YAPAEPAE00@Z
// partial score=0.95 date=2026-09-08
unsigned char *bfmeReadByteFL(unsigned char *src, unsigned char *dst, unsigned char *limit)
{
	if (limit != 0)
	{
		if (src > limit)
			return src;

		if (src + 1 > limit)
			return src;
	}

	*dst = *src;

	return src + 1;
}
