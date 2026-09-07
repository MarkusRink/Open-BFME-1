// ?bfmeDoTM@BfmeOwnerTM@@QAEXPAVBfmeMsgTM@@@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 111/111 bytes; 5 of 34 instructions differ, all from ONE choice: which
// register the two arms of `target` merge into.
//   retail  then: mov ecx,eax / jmp   else: mov ecx,esi   then push 59h
//   ours    then: jmp            else: mov eax,esi        then push 59h, mov ecx,eax
// Needed to get here: the global read into a local (it is used twice and lives
// in edi across both calls) and an explicit if/ELSE for target -- initialising
// `target = actor` up front and overwriting it in the if costs 2 bytes and
// hoists `mov ecx,esi` above the flag test.
// Tried: an extra local for the lookup result inside the then-arm (same 5).
class BfmeThingTM;

class BfmeInnerTM
{
public:
	BfmeThingTM *bfmeResolveTM(void);
};

class BfmeThingTM
{
public:
	int m_bfmeSpareTM;
	BfmeInnerTM *m_bfmeInnerTM;
	unsigned char m_bfmeGapTM[0xc0];
	int m_bfmeFlagsTM;
};

class BfmeActorTM
{
public:
	char bfmeCanTM(int what);

	int m_bfmeSpareTM;
	BfmeThingTM *m_bfmeThingTM;
	unsigned char m_bfmeGapTM[0x70];
	void *m_bfmeOwnerTM;
};

class BfmeMsgTM
{
public:
	unsigned char m_bfmeHeadTM[8];
	void *m_bfmeKeyTM;
};

struct Rva00367E30Logic
{
	BfmeActorTM *bfmeFindTM(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerTM
{
public:
	void bfmeDoTM(BfmeMsgTM *msg);
	void bfmeSendTM(BfmeMsgTM *msg);
};

void BfmeOwnerTM::bfmeDoTM(BfmeMsgTM *msg)
{
	Rva00367E30Logic *logic = TheBfmeGameLogic;
	BfmeActorTM *actor = logic->bfmeFindTM(msg->m_bfmeKeyTM);

	if (!actor)
		return;

	BfmeThingTM *thing = actor->m_bfmeThingTM;

	if (thing && thing->m_bfmeInnerTM)
		thing = thing->m_bfmeInnerTM->bfmeResolveTM();

	BfmeActorTM *target;

	if (thing->m_bfmeFlagsTM & 0x2000000)
	{
		target = logic->bfmeFindTM(actor->m_bfmeOwnerTM);

		if (!target)
			return;
	}
	else
		target = actor;

	if (target->bfmeCanTM(0x59))
		bfmeSendTM(msg);
}
