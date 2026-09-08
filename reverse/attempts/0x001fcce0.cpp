// ?bfmeCheck2XO@BfmeOwnerXO@@QAEDPAVObject@@@Z
// partial score=0.97 date=2026-09-08
class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadXO[4];
	LocomotorOverridable *m_bfme04XO;
	unsigned char m_bfmeMidXO[0xc0];
	unsigned char m_bfmeC8XO;
};

class Object
{
public:
	int getLayer() const;

	unsigned char m_bfmeHeadXO[4];
	LocomotorOverridable *m_bfme04XO;
};

class BfmeOwnerXO
{
public:
	char bfmeCheck2XO(Object *obj);

	unsigned char m_bfmeHeadXO[0x2c];
	int m_bfme2CXO;
};

static __forceinline LocomotorOverridable *bfmeFinalXO(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XO == 0)
		return p;

	return p->m_bfme04XO->friend_getFinalOverride();
}

char bfmeCheckXO(Object *obj)
{
	if (obj == 0)
		return 0;
	else if ((bfmeFinalXO(obj->m_bfme04XO)->m_bfmeC8XO & 4) != 0)
		return 0;
	else
		return obj->getLayer() == 1;
}

char BfmeOwnerXO::bfmeCheck2XO(Object *obj)
{
	if (m_bfme2CXO != 1)
		return 0;

	if (obj != 0 && (bfmeFinalXO(obj->m_bfme04XO)->m_bfmeC8XO & 4) == 0 && obj->getLayer() == 1)
		return 1;

	return 0;
}
