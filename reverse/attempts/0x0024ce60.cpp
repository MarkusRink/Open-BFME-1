// ?bfmeReactCK@BfmeHostCK@@QAEXPAVBfmeSrcCK@@@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 102/102 at exact size, ONE instruction different: the vftable load for the
// slot-17 call in the SECOND arm is `mov edx,[esi]` where retail has
// `mov eax,[esi]`. The identical call in the first arm already matches.
// Naming the this-0x20 base in a local in the second arm does not move it.
// Everything else falls out: the guard, the && chain that drops both failures
// into the flag test, the secondary-base `add esi,-0x20` recomputed per arm
// (spell the cast inline in each arm -- hoisting it above the branch computes
// it once and breaks both), and the two non-virtual forwards.
class BfmeThingCK;
class BfmeSrcCK;

class BfmeThingCK
{
public:
	virtual void bfmeSlot000T();
	virtual void bfmeSlot001T();
	virtual void bfmeSlot002T();
	virtual void bfmeSlot003T();
	virtual void bfmeSlot004T();
	virtual void bfmeSlot005T();
	virtual void bfmeSlot006T();
	virtual void bfmeSlot007T();
	virtual void bfmeSlot008T();
	virtual void bfmeSlot009T();
	virtual void bfmeSlot010T();
	virtual void bfmeSlot011T();
	virtual void bfmeSlot012T();
	virtual void bfmeSlot013T();
	virtual void bfmeSlot014T();
	virtual void bfmeSlot015T();
	virtual void bfmeSlot016T();
	virtual void bfmeSlot017T();
	virtual void bfmeSlot018T();
	virtual void bfmeSlot019T();
	virtual void bfmeSlot020T();
	virtual void bfmeSlot021T();
	virtual void bfmeSlot022T();
	virtual void bfmeSlot023T();
	virtual void bfmeSlot024T();
	virtual void bfmeSlot025T();
	virtual void bfmeSlot026T();
	virtual void bfmeSlot027T();
	virtual void bfmeSlot028T();
	virtual void bfmeSlot029T();
	virtual void bfmeSlot030T();
	virtual void bfmeSlot031T();
	virtual void bfmeSlot032T();
	virtual void bfmeSlot033T();
	virtual void bfmeSlot034T();
	virtual void bfmeSlot035T();
	virtual void bfmeSlot036T();
	virtual void bfmeSlot037T();
	virtual void bfmeSlot038T();
	virtual void bfmeSlot039T();
	virtual void bfmeSlot040T();
	virtual void bfmeSlot041T();
	virtual void bfmeSlot042T();
	virtual void bfmeSlot043T();
	virtual void bfmeSlot044T();
	virtual void bfmeSlot045T();
	virtual void bfmeSlot046T();
	virtual void bfmeSlot047T();
	virtual void bfmeSlot048T();
	virtual void bfmeSlot049T();
	virtual void bfmeSlot050T();
	virtual void bfmeSlot051T();
	virtual void bfmeSlot052T();
	virtual void bfmeSlot053T();
	virtual void bfmeSlot054T();
	virtual void bfmeSlot055T();
	virtual void bfmeSlot056T();
	virtual void bfmeSlot057T();
	virtual void bfmeSlot058T();
	virtual void bfmeSlot059T();
	virtual void bfmeSlot060T();
	virtual void bfmeSlot061T();
	virtual void bfmeSlot062T();
	virtual void bfmeSlot063T();
	virtual void bfmeMarkCK();
};

class BfmeOwnerCK
{
public:
	virtual void bfmeSlot000O();
	virtual void bfmeSlot001O();
	virtual void bfmeSlot002O();
	virtual void bfmeSlot003O();
	virtual void bfmeSlot004O();
	virtual void bfmeSlot005O();
	virtual void bfmeSlot006O();
	virtual void bfmeSlot007O();
	virtual void bfmeSlot008O();
	virtual void bfmeSlot009O();
	virtual void bfmeSlot010O();
	virtual void bfmeSlot011O();
	virtual void bfmeSlot012O();
	virtual void bfmeSlot013O();
	virtual void bfmeSlot014O();
	virtual void bfmeSlot015O();
	virtual void bfmeSlot016O();
	virtual void bfmeSlot017O();
	virtual void bfmeSlot018O();
	virtual void bfmeSlot019O();
	virtual void bfmeSlot020O();
	virtual void bfmeSlot021O();
	virtual void bfmeSlot022O();
	virtual void bfmeSlot023O();
	virtual void bfmeSlot024O();
	virtual void bfmeSlot025O();
	virtual BfmeThingCK *bfmeGetCK();
};

class BfmeSubCK
{
public:
	virtual void bfmeSlot000S();
	virtual void bfmeSlot001S();
	virtual void bfmeSlot002S();
	virtual void bfmeSlot003S();
	virtual void bfmeSlot004S();
	virtual void bfmeSlot005S();
	virtual void bfmeSlot006S();
	virtual void bfmeSlot007S();
	virtual void bfmeSlot008S();
	virtual void bfmeSlot009S();
	virtual void bfmeSlot010S();
	virtual void bfmeSlot011S();
	virtual void bfmeSlot012S();
	virtual void bfmeSlot013S();
	virtual void bfmeSlot014S();
	virtual void bfmeSlot015S();
	virtual void bfmeSlot016S();
	virtual void bfmeFinishCK();

	void bfmeFirstCK(BfmeSrcCK *src);
	void bfmeSecondCK(BfmeSrcCK *src);
};

class BfmeSrcCK
{
public:
	unsigned char m_bfmeHeadCK[0x94];
	unsigned char m_bfmeFlagsCK;
	unsigned char m_bfmeMidCK[0x167];
	BfmeOwnerCK *m_bfmeOwnerCK;
	unsigned char m_bfmeTailCK[0x14];
	int m_bfmeGuardCK;
};

class BfmeHostCK
{
public:
	void bfmeReactCK(BfmeSrcCK *src);
};

void BfmeHostCK::bfmeReactCK(BfmeSrcCK *src)
{
	if (src->m_bfmeGuardCK != 0)
		return;

	BfmeOwnerCK *owner = src->m_bfmeOwnerCK;
	BfmeThingCK *thing;

	if (owner != 0 && (thing = owner->bfmeGetCK()) != 0)
	{
		thing->bfmeMarkCK();
		((BfmeSubCK *)((char *)this - 0x20))->bfmeFirstCK(src);
		((BfmeSubCK *)((char *)this - 0x20))->bfmeFinishCK();
	}
	else if ((src->m_bfmeFlagsCK & 0x20) != 0)
	{
		((BfmeSubCK *)((char *)this - 0x20))->bfmeSecondCK(src);
		((BfmeSubCK *)((char *)this - 0x20))->bfmeFinishCK();
	}
}
