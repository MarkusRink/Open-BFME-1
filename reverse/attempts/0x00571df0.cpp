// ?bfmeFormatCY@BfmeOwnCY@@QAEXHPADD@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 70 bytes against retail's 76; structure is settled. A flag guard, a
// two-byte "0" written through the buffer (a single word store, so the source
// is a 16-bit store or an inlined one-char strcpy), an empty-range test, an
// unsigned bound check against (end - begin) over 8-byte pairs, then sprintf
// through the dllimport pointer with g_aptPalantirNumberFormat.
// Residue: retail keeps the buffer parameter in edx for the whole body (no
// call intervenes so a scratch register is safe) and uses esi only for the
// range end; MSVC parks the buffer in esi and pushes it at the top, which
// also moves the shrink-wrapped exit.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

extern char g_aptPalantirNumberFormat[];

class BfmePairCY
{
public:
	int m_bfmeFirstCY;
	int m_bfmeSecondCY;
};

class BfmeOwnCY
{
public:
	void bfmeFormatCY(int index, char *buffer, char flag);

	unsigned char m_bfmeHeadCY[0x264];
	BfmePairCY *m_bfmeBeginCY;
	BfmePairCY *m_bfmeEndCY;
};

void BfmeOwnCY::bfmeFormatCY(int index, char *buffer, char flag)
{
	if (flag)
		return;

	*(unsigned short *)buffer = 0x30;

	if (m_bfmeBeginCY == m_bfmeEndCY)
		return;

	if ((unsigned int)index >= (unsigned int)(m_bfmeEndCY - m_bfmeBeginCY))
		return;

	sprintf(buffer, g_aptPalantirNumberFormat, m_bfmeBeginCY[index].m_bfmeFirstCY);
}
