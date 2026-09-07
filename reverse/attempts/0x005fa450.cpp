// ?bfmeDrawZT@@YGXHHM@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// This stash is the LIFTED-FIRST variant: 82/83, prologue matches exactly, one
// byte short. Declaring `ground` first instead gives 83 bytes (correct size) but
// the prologue load order flips (retail loads a1 into eax before the fld of a3;
// MSVC loads a3 first). Interleaving the six stores in retail's emitted order
// gives 82 with a worse prologue in both variants.
// Everything else is settled: __stdcall (x, y, z) with ret 0xc, two 12-byte
// {int,int,float} locals, `(float)(z + <const double at RVA 0x00C7FD90>)` for the
// lifted one, and a thiscall virtual slot 11 on TheTacticalView (RVA 0x00EF1600)
// taking (&ground, &lifted, 0xccaaffff, 0) -- so the caller cleans only its own
// 0x18 of locals.
// The one byte is an encoding-length effect, not a missing instruction: retail
// emits `push 0` BEFORE filling the structs, so esp is 4 lower and the stores
// use the 4-byte `mov [esp+N]` form where MSVC (pushing later) can use the
// 3-byte `mov [esp]` form for the first field. Nothing in the source orders an
// argument push ahead of preceding statements, so this needs a scheduling
// lever, not a respelling.
extern const double g_bfmeLiftZT;

struct BfmeVec3ZT
{
	int m_bfmeXZT;
	int m_bfmeYZT;
	float m_bfmeZZT;
};

class BfmeViewZT
{
public:
	virtual void bfmeV00ZT();
	virtual void bfmeV01ZT();
	virtual void bfmeV02ZT();
	virtual void bfmeV03ZT();
	virtual void bfmeV04ZT();
	virtual void bfmeV05ZT();
	virtual void bfmeV06ZT();
	virtual void bfmeV07ZT();
	virtual void bfmeV08ZT();
	virtual void bfmeV09ZT();
	virtual void bfmeV10ZT();
	virtual void bfmeLineZT(BfmeVec3ZT *from, BfmeVec3ZT *to, unsigned int colour, int flag);
};

extern BfmeViewZT *TheBfmeViewZT;

void __stdcall bfmeDrawZT(int x, int y, float z)
{
	BfmeVec3ZT lifted;
	BfmeVec3ZT ground;

	lifted.m_bfmeXZT = x;
	lifted.m_bfmeYZT = y;
	lifted.m_bfmeZZT = (float)(z + g_bfmeLiftZT);

	ground.m_bfmeXZT = x;
	ground.m_bfmeYZT = y;
	ground.m_bfmeZZT = z;

	TheBfmeViewZT->bfmeLineZT(&ground, &lifted, 0xccaaffff, 0);
}
