// ?hasHigherPathPriority@AIUpdateInterface@@QBE_NPAV1@@Z
// partial score=0.92 date=2026-09-06
Bool AIUpdateInterface::hasHigherPathPriority(AIUpdateInterface *otherAI) const
{
	const BFMEAIUpdateFields &selfFields =
		*reinterpret_cast<const BFMEAIUpdateFields *>(this);
	const Object *object = selfFields.getObject();
	const Object *other = reinterpret_cast<const BFMEAIUpdateFields *>(otherAI)->getObject();
	register UnsignedInt pathKindMask = 0x4000;

	if (bfmePathPriorityKind(object, pathKindMask) && !bfmePathPriorityKind(other, pathKindMask))
		return FALSE;
	if (!bfmePathPriorityKind(object, pathKindMask) && bfmePathPriorityKind(other, pathKindMask))
		return FALSE;

	if (object->getCrushableLevel() > other->getCrushableLevel())
		return FALSE;

	if (object->isKindOf((KindOfType)9) && other->isKindOf((KindOfType)8)) {
		return FALSE;
	}
	if (object->isKindOf((KindOfType)8) && other->isKindOf((KindOfType)9)) {
		return FALSE;
	}

	const Coord3D *ourDirection = object->getUnitDirectionVector2D();
	volatile Coord3D ourDir;
	ourDir.x = ourDirection->x;
	ourDir.y = ourDirection->y;
	const Coord3D *otherDirection = other->getUnitDirectionVector2D();
	Coord3D otherDir;
	otherDir.x = otherDirection->x;
	otherDir.y = otherDirection->y;
	if (ourDir.x*otherDir.x + ourDir.y*otherDir.y <= 0) {
		return selfFields.getObject()->getID() < other->getID();
	}
	Coord2D combinedDir;
	combinedDir.x = ourDir.x + otherDir.x;
	combinedDir.y = ourDir.y + otherDir.y;
	Coord2D vectorToOther;
	vectorToOther.x = other->getPosition()->x - object->getPosition()->x;
	vectorToOther.y = other->getPosition()->y - object->getPosition()->y;
	Real dotProduct = combinedDir.x*vectorToOther.x + combinedDir.y*vectorToOther.y;
	if (dotProduct>0) return FALSE;
	if (dotProduct<0) return TRUE;
	return selfFields.getObject()->getID() < other->getID();
}
