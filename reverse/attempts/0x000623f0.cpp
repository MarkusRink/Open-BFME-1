// ?bfmeCmdDI@@YAHPAPADH@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 152/151. Byte-for-byte the same body as 0x00062330 with a different global
// UnicodeString (0x012F08A8 instead of 0x012F08A4), and the SAME single-byte
// residue: retail takes the second TheWritableGlobalData read in EAX for the
// 5-byte `a1` encoding, MSVC picks edx. See reverse/attempts/0x00062330.cpp for
// the two levers this body still needs (bound const-ref temporary, positive
// argc guard) -- both are already applied below.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDI;

private:
	void releaseBuffer();
};

class UnicodeString
{
public:
	void setDI(const BFMERetailAsciiString &text);

	void *m_bfmeBufDI;
};

extern UnicodeString g_bfmeTargetDI;
extern bool g_aiTargetDispatchSuppressed;

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadDI[0x29];
	unsigned char m_bfmeFlagDI;
	unsigned char m_bfmeMidDI[0xb8a];
	unsigned char m_bfmeOtherDI;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

int __cdecl bfmeCmdDI(char **argv, int argc)
{
	if (argc >= 2)
	{
		{
			const BFMERetailAsciiString &text = BFMERetailAsciiString(argv[1]);

			g_bfmeTargetDI.setDI(text);
		}

		g_aiTargetDispatchSuppressed = true;
		TheWritableGlobalData->m_bfmeFlagDI = 1;
		TheWritableGlobalData->m_bfmeOtherDI = 0;

		return 2;
	}

	return 1;
}
