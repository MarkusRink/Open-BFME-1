// ?d_0021e5d0@@YAXXZ
// partial score=0.94 date=2026-09-06
// Near-miss attempt for ?d_0021e5d0@@YAXXZ at 0x0021E5D0.
// The complete source attempt remains in GarrisonContain.cpp in this worktree.

class BfmeWeaponRangeCall
{
public:
	Bool isWithinAttackRange(const Object *source, const Coord3D *targetPos, Int extra) const;
};

class BfmeGarrisonPointIndexInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0; virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual Int getObjectGarrisonPointIndex(ObjectID objectID) = 0;
};

Bool GarrisonContain::attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos)
{
	if (!source || !targetPos || !weapon)
		return FALSE;

	BfmeGarrisonPointIndexInterface *bfmeContain = reinterpret_cast<BfmeGarrisonPointIndexInterface *>(
		(char *)this);
	GarrisonContain *contain = reinterpret_cast<GarrisonContain *>(bfmeContain);

	Int existingIndex = bfmeContain->getObjectGarrisonPointIndex(source->getID());
	if (existingIndex != GARRISON_INDEX_INVALID)
		contain->removeObjectFromGarrisonPoint(source, existingIndex);

	if (bfmeContain->getObjectGarrisonPointIndex(source->getID()) == GARRISON_INDEX_INVALID)
	{
		Int conditionIndex = contain->findConditionIndex();
		Int placeIndex = contain->findClosestFreeGarrisonPointIndex(conditionIndex, targetPos);
		if (placeIndex != GARRISON_INDEX_INVALID)
			contain->putObjectAtGarrisonPoint(source, INVALID_ID, conditionIndex, placeIndex);
	}

	BfmeWeaponRangeCall *rangeWeapon = reinterpret_cast<BfmeWeaponRangeCall *>(weapon);
	if (rangeWeapon->isWithinAttackRange(source, targetPos, 0))
		return TRUE;

	existingIndex = bfmeContain->getObjectGarrisonPointIndex(source->getID());
	if (existingIndex != GARRISON_INDEX_INVALID)
		contain->removeObjectFromGarrisonPoint(source, existingIndex);
	return FALSE;
}
