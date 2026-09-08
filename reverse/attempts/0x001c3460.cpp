// ?bfmeGetYA@BfmeHostYA@@QAEMXZ
// partial score=0.94 date=2026-09-08
// pin needed: ?bfmeApplyYA@LocomotorOverridable@@QAEHPAVPlayer@@H@Z,0x0004B01F
class Player;

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();
	int bfmeApplyYA(Player *pl, int mode);

	unsigned char m_bfmeHeadYA[4];
	LocomotorOverridable *m_bfme04YA;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

static __forceinline LocomotorOverridable *bfmeFinalYA(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YA == 0)
		return p;

	return p->m_bfme04YA->friend_getFinalOverride();
}

class BfmeHostYA
{
public:
	float bfmeGetYA();

	unsigned char m_bfmeHeadYA[4];
	LocomotorOverridable *m_bfme04YA;
	unsigned char m_bfmeMidYA[0x234];
	Team *m_bfme23CYA;
};

float BfmeHostYA::bfmeGetYA()
{
	Team *team = m_bfme23CYA;
	Player *pl = 0;

	if (team != 0)
		pl = team->getControllingPlayer();

	if (pl == 0)
		return BfmeZeroRange;

	return g_bfmeDefaultBU / (float)bfmeFinalYA(m_bfme04YA)->bfmeApplyYA(pl, -1);
}
