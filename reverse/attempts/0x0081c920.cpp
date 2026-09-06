// ?rva0081c920@@YAPAUBfmeElemVIA@@PAU1@00@Z
// partial score=0.55 date=2026-09-06
// ?rva0081c920@@YAPAUBfmeElemVIA@@PAU1@00@Z

struct BfmeElemVIA;

extern BfmeElemVIA *__cdecl bfmeCopyVIA(BfmeElemVIA *first, BfmeElemVIA *last, BfmeElemVIA *dest);

BfmeElemVIA *__cdecl rva0081c920(BfmeElemVIA *first, BfmeElemVIA *last, BfmeElemVIA *dest)
{
	volatile char temp[12];
	temp[7] = 0;
	return bfmeCopyVIA(first, last, dest);
}
