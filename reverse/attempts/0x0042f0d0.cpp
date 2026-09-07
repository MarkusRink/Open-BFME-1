// ?bfmeCheckCT@@YGDVBFMERetailAsciiString@@@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 94/106. The logic is right -- a by-value AsciiString parameter, a null test
// on its buffer, a `cmp word ptr [eax+4],0` length test, char return, and the
// destructor running on every path under the SEH frame.
// Retail DUPLICATES the destructor + epilogue into two blocks, one per return
// value (`xor al,al` at +0x35, `mov al,1` at +0x5b), each with its own
// releaseBuffer call and fs:[0] restore. MSVC merges them: one releaseBuffer,
// one epilogue, and a conditional al. That merge is the whole 12-byte gap.
// Same decision as 0x0061DD60 and 0x00457090 -- see
// [[zero-materialisation-is-unstable]]'s neighbours; no flag reaches it
// (/Ot /Og /Gy /Ob0 /Oy- were swept on 0x00457090).
struct BfmeBufCT
{
	unsigned char m_bfmeHeadCT[4];
	unsigned short m_bfmeLenCT;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBufferCT(); }

	void releaseBufferCT();

	BfmeBufCT *m_bfmeBufCT;
};

char __stdcall bfmeCheckCT(BFMERetailAsciiString text)
{
	if (text.m_bfmeBufCT == 0)
		return 0;

	if (text.m_bfmeBufCT->m_bfmeLenCT == 0)
		return 0;

	return 1;
}
