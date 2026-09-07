// ?Rva009B62A0ExpandTable@@YAXPBIPAG@Z
// partial score=0.98 date=2026-09-06
// Retail VP6 Huffman lookup expansion at 0x009B62A0.

void Rva009B62A0ExpandTable(const unsigned *tree, unsigned short *output)
{
	unsigned value;
	int index = 0;
	int prefix;
	int bit;

	do {
		prefix = 0;
		value &= 0xffffff00;
		bit = 6;
		do {
			++prefix;
			--bit;
			int branch = index >> bit;
			value >>= 1;
			value &= 0x7f;
			if (branch & 1)
				value = tree[value * 3 + 1];
			else
				value = tree[value * 3];
		} while ((value & 1) == 0 && bit > 0);

		unsigned result = (value >> 1) & 0x7f;
		unsigned low = value & 1;
		result = (result | (prefix << 11)) << 1;
		result |= low;
		output[index] = (unsigned short)result;
		++index;
	} while (index < 64);
}
