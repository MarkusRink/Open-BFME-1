struct CodecState;
struct BfmeHolderBZB;

void Rva009A6EC0Release(void **q);
void bfmeGoBZB(BfmeHolderBZB *h);
void bfmeStepJW(void *q);
void Rva009A8880Release(void *q);
void releaseCodecState(CodecState **q);

int bfmeFreeCodecJW(CodecState **p)
{
	if (*p != 0)
	{
		Rva009A6EC0Release((void **)((char *)*p + 0x13c));
		bfmeGoBZB((BfmeHolderBZB *)((char *)*p + 0x298));
		bfmeStepJW(*p);
		Rva009A8880Release(*p);
		releaseCodecState(p);
	}

	return 1;
}
