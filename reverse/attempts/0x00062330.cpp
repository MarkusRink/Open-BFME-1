// ?bfmeCmdDH@@YAHPAPADH@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 152/151. A console command handler: argc guard, argv[1] wrapped in a string
// temporary that is `set` into a GLOBAL UnicodeString whose address is taken as
// an immediate (mov ecx,0x12f08a4 -- pin it as a data symbol, not a pointer),
// then three flag stores and `return 2`.
// The [[bind-temporary-to-const-ref]] lever is required here for the
// lea/push form, and the guard must be written positively
// (`if (argc >= 2) { ... return 2; } return 1;`) or the return-1 block lands
// inline instead of last.
// The single byte is [[eax-short-form-global]]: retail loads the SECOND
// TheWritableGlobalData read into EAX and gets the 5-byte `a1` short form,
// MSVC picks edx and pays 6. eax is dead at that point in both builds.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDH;

private:
	void releaseBuffer();
};

class UnicodeString
{
public:
	void setDH(const BFMERetailAsciiString &text);

	void *m_bfmeBufDH;
};

extern UnicodeString g_bfmeTargetDH;
extern bool g_aiTargetDispatchSuppressed;

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadDH[0x29];
	unsigned char m_bfmeFlagDH;
	unsigned char m_bfmeMidDH[0xb8a];
	unsigned char m_bfmeOtherDH;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

int __cdecl bfmeCmdDH(char **argv, int argc)
{
	if (argc >= 2)
	{
		{
			const BFMERetailAsciiString &text = BFMERetailAsciiString(argv[1]);

			g_bfmeTargetDH.setDH(text);
		}

		g_aiTargetDispatchSuppressed = true;
		TheWritableGlobalData->m_bfmeFlagDH = 1;
		TheWritableGlobalData->m_bfmeOtherDH = 0;

		return 2;
	}

	return 1;
}
