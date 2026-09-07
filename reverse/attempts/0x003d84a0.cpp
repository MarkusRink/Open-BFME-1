// ?bfmeSetETD@BfmeGridETD@@QAEXPAVBfmeOwnerETD@@@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 113/113 EXACT SIZE. Whole shape reproduces: position-to-cell conversion
// through the out-parameter pair, two bounds pairs, the 2D index with a
// 16-byte element, the owner test and the two calls.
// Residue is callee-saved allocation:
//   retail  ebx=x  esi=this  edi=y  ebp=owner
//   MSVC    ebp=x  esi=this  edi=owner  ebx=y
// and MSVC loads x into ecx first then copies to ebp, where retail loads it
// straight into ebx. MSVC also pushes edi in the prologue; retail shrink-wraps
// that push to just before the y load.
// Ruled out: dropping the x and y locals and spelling cell.m_x / cell.m_y at
// every use (117 bytes, allocation drifts further).
//
// SIBLING: 0x003D8530 (112 bytes) is the same body with two changes only --
//   cmp [ecx+4],ebp / jne  instead of  mov eax,[ecx+4] / test eax,eax / jne
//   push 0 instead of push ebp, and push 0 instead of push 1
// i.e. it tests cell->m_owner == owner and then clears it, where this one
// tests == 0 and sets it. One fix lands both, 225 bytes.
// Pins are already in symbols.csv.
class BfmeOwnerETD;
class BfmePosETD;

struct BfmePairETD
{
	int m_bfmeXETD;
	int m_bfmeYETD;
};

struct BfmeCellETD
{
	void bfmeSetOwnerETD(BfmeOwnerETD *owner);

	unsigned char m_bfmeHeadETD[4];
	BfmeOwnerETD *m_bfmeOwnerETD;
	unsigned char m_bfmeTailETD[8];
};

class BfmeSinkETD
{
public:
	void bfmeNotifyETD(int x, int y, int mode, BfmeOwnerETD *owner);
};

class BfmeOwnerETD
{
public:
	unsigned char m_bfmeHeadETD[0xc];
	BfmePosETD *m_bfmePosETD;
};

class BfmeGridETD
{
public:
	void bfmeSetETD(BfmeOwnerETD *owner);
	void bfmeToCellETD(BfmePosETD *pos, BfmePairETD *out);

	unsigned char m_bfmeHeadETD[0x10];
	BfmeCellETD **m_bfme10ETD;
	int m_bfme14ETD;
	int m_bfme18ETD;
	int m_bfme1cETD;
	int m_bfme20ETD;
	unsigned char m_bfmeMidETD[0xc78];
	BfmeSinkETD m_bfmeSinkETD;
};

void BfmeGridETD::bfmeSetETD(BfmeOwnerETD *owner)
{
	BfmePairETD cell;

	bfmeToCellETD((BfmePosETD *)&owner->m_bfmePosETD, &cell);

	int x = cell.m_bfmeXETD;

	if (x < m_bfme14ETD || x > m_bfme1cETD)
		return;

	int y = cell.m_bfmeYETD;

	if (y < m_bfme18ETD || y > m_bfme20ETD)
		return;

	BfmeCellETD *entry = m_bfme10ETD[x] + y;

	if (entry == 0)
		return;

	if (entry->m_bfmeOwnerETD != 0)
		return;

	entry->bfmeSetOwnerETD(owner);

	m_bfmeSinkETD.bfmeNotifyETD(x, y, 1, owner);
}
