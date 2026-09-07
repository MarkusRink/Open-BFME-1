// ?bfmeAtDK@BfmeHostDK@@QAEPAVBFMERetailAsciiString@@H@Z (identity unknown)
// partial score=0.88 date=2026-09-07
// 141/148. Bounds-checked slot accessor with a function-local static
// BFMERetailAsciiString("Invalid Slot") as the fallback. The static guard
// reproduces EXACTLY -- `mov cl,[g] / mov eax,1 / test al,cl / jne / or [g],eax`
// and the atexit registration both fall out of writing a plain
// `static BFMERetailAsciiString invalid("Invalid Slot");`
// (see [[function-local-statics-convert]]).
// Two residues:
//   * retail keeps the begin pointer in ESI (push esi / mov esi,[ecx+0x54] /
//     mov ecx,esi / lea eax,[ecx+eax*4] / pop esi); MSVC avoids the
//     callee-saved save entirely. Naming begin in a local does not force it.
//   * MSVC hoists the index read and its test ABOVE the SEH prologue pushes;
//     retail emits them between `push eax` and `mov fs:[0],esp`.
// Everything else -- the unsigned bound compare, the duplicated epilogue, the
// literal and the returned static address -- matches.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDK;

private:
	void releaseBuffer();
};

class BfmeHostDK
{
public:
	BFMERetailAsciiString *bfmeAtDK(int index);

	unsigned char m_bfmeHeadDK[0x54];
	BFMERetailAsciiString *m_bfmeBeginDK;
	BFMERetailAsciiString *m_bfmeEndDK;
};

BFMERetailAsciiString *BfmeHostDK::bfmeAtDK(int index)
{
	BFMERetailAsciiString *begin = m_bfmeBeginDK;

	if (index >= 0 && (unsigned int)index < (unsigned int)(m_bfmeEndDK - begin))
		return &begin[index];

	static BFMERetailAsciiString invalid("Invalid Slot");

	return &invalid;
}
