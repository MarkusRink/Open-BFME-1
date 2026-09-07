// ?bfmeGetEQV@BfmeHostEQV@@QAEPAVBfmeItemEQV@@PAX@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 150/150 EXACT SIZE, every instruction matches, one 3-cycle register
// rotation on the three callee-saved values:
//   retail  ebx=key(param)  esi=&this+0x194  edi=zero/new item
//   MSVC    edi=key         ebx=&this+0x194  esi=zero/new item
// Retail also hoists the zero (xor edi,edi) to the first compare, giving
// cmp eax,edi where MSVC emits test eax,eax; that is the same allocation
// choice, not an extra instruction -- both bodies are 150 bytes.
// Ruled out: no locals at all; a local for the receiver; a local copy of the
// parameter; declaring the item first and comparing find() against it (MSVC
// folds it back to test eax,eax); /Ob1 /G7 /Ot /Gy (identical), /Oy- (147),
// /Os (109, drops a call).
// Pins used: ?bfmeFindEQV@BfmeMapEQV@@QAEPAVBfmeItemEQV@@PAX@Z -> 0x0002DB0A,
// ?bfmeAtEQV@BfmeMapEQV@@QAEPAPAVBfmeItemEQV@@PAX@Z -> 0x000059B6,
// ??0BfmeItemEQV@@QAE@PAX@Z -> 0x0002F289 (left in symbols.csv).
class BfmeItemEQV
{
public:
	BfmeItemEQV(void *key);

	unsigned char m_bfmeBodyEQV[0x34];
};

class BfmeMapEQV
{
public:
	BfmeItemEQV *bfmeFindEQV(void *key);
	BfmeItemEQV **bfmeAtEQV(void *key);
};

class BfmeHostEQV
{
public:
	BfmeItemEQV *bfmeGetEQV(void *key);

	unsigned char m_bfmeHeadEQV[0x194];
	BfmeMapEQV m_bfmeMapEQV;
};

BfmeItemEQV *BfmeHostEQV::bfmeGetEQV(void *key)
{
	BfmeMapEQV *map = &m_bfmeMapEQV;

	if (map->bfmeFindEQV(key) != 0)
		return *map->bfmeAtEQV(key);

	BfmeItemEQV *item = new BfmeItemEQV(key);

	*map->bfmeAtEQV(key) = item;

	return item;
}
