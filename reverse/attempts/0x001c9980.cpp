// ?bfmeReadyZK@BfmeOwnerZK@@QAEHXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 104/109 bytes. Everything matches except one missing 5-byte block.
// What had to be right: the return type is int (char gives mov al,1 for the
// tail), the whole tail must be NESTED with one trailing `return 0` and the
// state test written as a signed `>= 0` on a char member (`& 0x80` folds to
// shr/not/and or setge), and the two callees differ in return type -- the
// permission call returns bool while the check call returns char, which is
// what makes retail able to zero only al on one path.
// Residue: retail keeps a SEPARATE early-return block for the flag case,
// `pop edi; xor al,al; pop esi; ret` (8-bit), distinct from the shared
// `xor eax,eax` exit; MSVC merges the two because both are a 32-bit zero. The
// 5 bytes are exactly that duplicated epilogue.
class BfmeThingZK;

class BfmeInnerZK
{
public:
	BfmeThingZK *bfmeResolveZK(void);
};

class BfmeThingZK
{
public:
	int m_bfmeSpareZK;
	BfmeInnerZK *m_bfmeInnerZK;
	unsigned char m_bfmeGapZK[0xc0];
	char m_bfmeStateZK;
};

class BfmeActorZK
{
public:
	bool bfmeCanZK(int what);

	unsigned char m_bfmeHeadZK[0x90];
	unsigned char m_bfmeFlagsZK;
};

struct Rva00367E30Logic
{
	BfmeActorZK *bfmeFindZK(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerZK
{
public:
	int bfmeReadyZK(void);
	char bfmeCheckZK(void);

	int m_bfmeSpareZK;
	BfmeThingZK *m_bfmeThingZK;
	unsigned char m_bfmeGapZK[0x70];
	void *m_bfmeKeyZK;
};

int BfmeOwnerZK::bfmeReadyZK(void)
{
	void *key = m_bfmeKeyZK;

	if (key)
	{
		BfmeActorZK *actor = TheBfmeGameLogic->bfmeFindZK(key);

		if (actor && actor->bfmeCanZK(0x6c) && (actor->m_bfmeFlagsZK & 8))
			return 0;
	}

	if (bfmeCheckZK())
	{
		BfmeThingZK *thing = m_bfmeThingZK;

		if (thing && thing->m_bfmeInnerZK)
			thing = thing->m_bfmeInnerZK->bfmeResolveZK();

		if (thing->m_bfmeStateZK >= 0)
			return 1;
	}

	return 0;
}
