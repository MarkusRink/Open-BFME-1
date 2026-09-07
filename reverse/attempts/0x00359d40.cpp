// ?bfmeFindERY@BfmeHostERY@@QAEPAHPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 101/101 EXACT SIZE, ONE swapped instruction pair:
//   retail  push ebp / lea ecx,[eax+esi+8] / call
//   MSVC    lea ecx,[eax+esi+8] / push ebp / call
//
// The two remaining levers CONFLICT and only one can be had at a time:
//  * naming the receiver (BfmeSubERY *sub = &map->m_entries[id].m_sub) is what
//    fixes the esi/edi assignment -- without it map lands in esi and the
//    scaled index in edi, six diffs instead of one;
//  * but naming it also makes MSVC compute the receiver BEFORE pushing the
//    argument, where retail pushes first.
// Measured alternatives: receiver as a reference (same one diff); naming the
// argument as well (same); naming the bucket instead of the sub-object (102);
// naming the entries base (92, loses the this spill); map as a reference
// instead of a pointer (nine diffs).
//
// The this-pointer spill is load-bearing: `map` must be a named local so the
// final expression can be spelled through m_bfmeMapERY (i.e. through this),
// which forces retail's push ecx / mov [esp+0x10],ecx / reload. Spelling
// everything through this gives 92 bytes.
//
// SIBLING: 0x00359DC0 is the same body with the map at this+0x2c instead of
// this+0xc, the final base at +0x38 instead of +0x18, and lookup thunk
// 0x000072F7 instead of 0x000329FC. One fix lands both, 202 bytes.
// Pins are already in symbols.csv.
class BfmeItemERY
{
public:
	unsigned char m_bfmeHeadERY[4];
	int m_bfmeValueERY;
};

class BfmeSubERY
{
public:
	int bfmeCheckERY(void *key);
};

struct BfmeBucketERY
{
	unsigned char m_bfmeHeadERY[8];
	BfmeSubERY m_bfmeSubERY;
	unsigned char m_bfmePadERY[7];
	BfmeItemERY *m_bfmeItemERY;
};

class BfmeMapERY
{
public:
	unsigned int bfmeLookupERY(void *key);

	int *m_bfmeFirstERY;
	int *m_bfmeLastERY;
	unsigned char m_bfmeMidERY[4];
	BfmeBucketERY *m_bfmeEntriesERY;
};

class BfmeHostERY
{
public:
	int *bfmeFindERY(void *key);

	unsigned char m_bfmeHeadERY[0xc];
	BfmeMapERY m_bfmeMapERY;
};

int *BfmeHostERY::bfmeFindERY(void *key)
{
	BfmeMapERY *map = &m_bfmeMapERY;

	unsigned int i = map->bfmeLookupERY(key);

	if (i < (unsigned int)(map->m_bfmeLastERY - map->m_bfmeFirstERY))
	{
		int id = map->m_bfmeFirstERY[i];

		BfmeSubERY *sub = &map->m_bfmeEntriesERY[id].m_bfmeSubERY;

		if (sub->bfmeCheckERY(key) == 0 && id != -1)
			return &m_bfmeMapERY.m_bfmeEntriesERY[id].m_bfmeItemERY->m_bfmeValueERY;
	}

	return 0;
}
