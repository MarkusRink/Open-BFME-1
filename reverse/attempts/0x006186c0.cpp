// ?bfmeGetAG@BfmeOwnerAG@@QAE?AUBfmeVec3AG@@XZ (identity unknown)
// partial score=0.85 date=2026-09-07
// 89/97, eight bytes short. Solved and worth reusing:
//   * this is an SRET body -- `ret 4`, and the hidden buffer pointer loaded with
//     `mov eax,[esp+0x20]` at the end IS the return value.
//   * the result must be built with `return BfmeVec3AG(x, y, z);` and the struct
//     given a constructor. A local `r` filled field by field and returned costs
//     19 bytes for the copy into the sret buffer (116 vs 97) --
//     [[construct-in-the-return]], no NRV in 13.10.
//   * x and z default to literal `0.0f` (immediate `mov dword ptr,0`) but y
//     defaults to the NAMED const float at RVA 0x00C75350 (`fld`), so the three
//     defaults are not spelled the same way in the source.
// The 8-byte gap is one float round-trip: retail materialises y in memory on the
// item path -- `mov eax,[esi+0x34]` / `mov [esp+0x14],eax` / `fld [esp+0x14]`
// (11 bytes) -- where MSVC just does `fld [esi+0x34]` (3). Retail also reserves
// 0x18 of frame with the three live slots 8 bytes apart (-24, -16, -8) against
// MSVC's 8, so there are three more slots it never touches. `volatile float y`
// would force the store but retail's zero path has NO store for y, so that is
// not it either. Something makes y a real memory local only on one arm.
extern const float g_bfmeZeroAG;

struct BfmeVec3AG
{
	BfmeVec3AG(float x, float y, float z)
	{
		m_bfmeXAG = x;
		m_bfmeYAG = y;
		m_bfmeZAG = z;
	}

	float m_bfmeXAG;
	float m_bfmeYAG;
	float m_bfmeZAG;
};

class BfmeItemAG
{
public:
	virtual void bfmeV00AG();
	virtual void bfmeV01AG();
	virtual void bfmeV02AG();
	virtual void bfmeV03AG();
	virtual void bfmeV04AG();
	virtual void bfmeV05AG();
	virtual void bfmeV06AG();
	virtual void bfmeV07AG();
	virtual void bfmeV08AG();
	virtual void bfmeV09AG();
	virtual void bfmeV10AG();
	virtual void bfmeV11AG();
	virtual void bfmeV12AG();
	virtual void bfmeV13AG();
	virtual void bfmeV14AG();
	virtual void bfmeV15AG();
	virtual void bfmeV16AG();
	virtual void bfmeV17AG();
	virtual void bfmeV18AG();
	virtual void bfmeV19AG();
	virtual void bfmeUpdateAG();

	unsigned char m_bfmeHeadAG[0x20];
	float m_bfmeXAG;
	unsigned char m_bfmeMidAG[0xc];
	float m_bfmeYAG;
	unsigned char m_bfmeMid2AG[0xc];
	float m_bfmeZAG;
};

class BfmeHolderAG
{
public:
	unsigned char m_bfmeHeadAG[8];
	BfmeItemAG *m_bfmeItemAG;
};

class BfmeOwnerAG
{
public:
	BfmeVec3AG bfmeGetAG();

	unsigned char m_bfmeHeadAG[0xc];
	BfmeHolderAG *m_bfmeHolderAG;
};

BfmeVec3AG BfmeOwnerAG::bfmeGetAG()
{
	float x = 0.0f;
	float y = g_bfmeZeroAG;
	float z = 0.0f;

	BfmeItemAG *item = m_bfmeHolderAG->m_bfmeItemAG;

	if (item != 0)
	{
		item->bfmeUpdateAG();

		x = item->m_bfmeXAG;
		y = item->m_bfmeYAG;
		z = item->m_bfmeZAG;
	}

	return BfmeVec3AG(x, y, z);
}
