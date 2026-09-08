// _bfmeReload1221
// partial score=0.8 date=2026-09-08
// _bfmeReload1221

extern int g_bfmeIndexFA;
extern unsigned int g_bfmeStateFA[];
extern unsigned int *g_bfmeNext1221;
extern void bfmeSeed(int seed);

extern "C" unsigned int bfmeReload1221(void)
{
	register int *lag;
	unsigned int *entry = &g_bfmeStateFA[0];
	unsigned int *next = &g_bfmeStateFA[2];

	if (g_bfmeIndexFA < -1)
		bfmeSeed(0x1105);

	int previous = g_bfmeStateFA[0];
	int value = g_bfmeStateFA[1];

	g_bfmeIndexFA = 0x26f;
	g_bfmeNext1221 = &g_bfmeStateFA[1];

	int count = 0xe3;
	do
	{
		unsigned int mixed = value ^ previous;
		mixed = (mixed & 0x7ffffffe) ^ previous;
		mixed >>= 1;
		mixed ^= ((value & 1) ? 0x9908b0df : 0);
		mixed ^= next[395];
		*entry = mixed;

		previous = value;
		value = *next;
		++entry;
		++next;
	}
	while (--count != 0);

	unsigned int secondMixed;
	lag = (int *)&g_bfmeStateFA[0];
	count = 0x18c;
	do
	{
		secondMixed = value ^ previous;
		secondMixed = (secondMixed & 0x7ffffffe) ^ previous;
		secondMixed >>= 1;
		secondMixed ^= ((value & 1) ? 0x9908b0df : 0);
		secondMixed ^= *lag;
		*entry = secondMixed;

		previous = value;
		value = *next;
		++entry;
		++lag;
		++next;
	}
	while (--count != 0);

	int first = g_bfmeStateFA[0];
	unsigned int mixed = first ^ previous;
	mixed = (mixed & 0x7ffffffe) ^ previous;
	mixed >>= 1;
	mixed ^= ((first & 1) ? 0x9908b0df : 0);
	mixed ^= *lag;
	*entry = mixed;

	unsigned int result = first;
	result ^= result >> 11;
	result ^= (result << 7) & 0xff3a58ad;
	result ^= (result << 15) & 0xffffdf8c;
	return result ^ (result >> 18);
}
