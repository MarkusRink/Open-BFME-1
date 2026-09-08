// ?Rva002E3750SetModule@@YADDPBD@Z
// partial score=0.99 date=2026-09-08
// The Lua ShowModule and HideModule callbacks share this module-name helper.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

struct BfmeStrAE
{
	char *m_bfmeDataAE;
};

class BfmeOwnerAE
{
public:
	char bfmeSetAE(BfmeStrAE *name, char on);
};

struct BfmeTargetBR
{
	char m_bfmePad[0x0c];
	BfmeOwnerAE *m_bfmeOwner;
};

struct BfmeOwnerBR
{
	char m_bfmePad[0x78];
	BfmeTargetBR *m_bfmeTarget;
};

extern BfmeOwnerBR *g_bfmeOwnerBR;

// ?Rva002E3750SetModule@@YADDPBD@Z
char Rva002E3750SetModule(char on, const char *text)
{
	if (g_bfmeOwnerBR->m_bfmeTarget != 0) {
		const BfmeTargetBR *target = g_bfmeOwnerBR->m_bfmeTarget;
		const char *nameText = text;
		BfmeOwnerAE *owner = target->m_bfmeOwner;
		BFMERetailAsciiString name(nameText);
		if (owner != 0)
			return owner->bfmeSetAE((BfmeStrAE *)&name, on == 0);
	}
	return 0;
}
