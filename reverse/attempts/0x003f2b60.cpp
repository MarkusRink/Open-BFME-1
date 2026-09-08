// ?isCheckForAdjust@Rva003F2B60@@QAE_NHH@Z
// partial score=0.30 date=2026-09-08
// Candidate reconstruction for retail RVA 0x003F2B60, 355 bytes.
// The four debug strings identify the Pathfinder adjustment helper. The
// enclosing record stores the Pathfinder call arguments at offsets 0x00-0x30
// and remembers the best ally count at +0x28.

typedef int Int;
typedef bool Bool;

class Object
{
public:
	Bool isKindOf(Int kind) const;
};

class LocomotorSet;
class PathfindCell;
struct Coord3D;

class Pathfinder
{
public:
	Bool checkForAdjust(Object *, const LocomotorSet *, Bool, Int, Int, Int,
		Int, Bool, PathfindCell **, Int, Coord3D *, Int, Coord3D *);
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void __cdecl j_0003a17a(void *, const char *, ...);

class Rva003F2B60
{
public:
	Bool isCheckForAdjust(Int cellX, Int cellY);

private:
	Pathfinder *m_pathfinder;
	Object *m_obj;
	const LocomotorSet *m_locomotorSet;
	Bool m_isHuman;
	Bool m_onlyIfLayer;
	char m_padding[2];
	Int m_layer;
	Int m_cellY;
	Int m_cellX;
	Int m_radius;
	Int m_foundWithAllies;
	Int m_bestCellX;
	Int m_bestCellY;
	Coord3D *m_dest;
	PathfindCell **m_fromSlot;
};

Bool Rva003F2B60::isCheckForAdjust(Int cellX, Int cellY)
{
	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC,
			(const char *)0x010EFD4C, cellX, cellY);

	if (!m_pathfinder->checkForAdjust(m_obj, m_locomotorSet, m_isHuman,
		cellX, cellY, m_layer, m_radius, m_onlyIfLayer,
		m_fromSlot, m_radius, (Coord3D *)&cellY, m_cellX, m_dest))
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC,
				(const char *)0x010EFD0C);
		return 0;
	}

	Int allyCount = cellY;
	Bool isInfantry = m_obj->isKindOf(0x7C);
	if (allyCount == 0 || isInfantry)
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC,
				(const char *)0x010EFC08,
				allyCount ? (const char *)0x0107FA58 : (const char *)0x01080180,
				isInfantry ? (const char *)0x0107FA58 : (const char *)0x01080180);
		return 1;
	}

	if (allyCount >= m_foundWithAllies && m_foundWithAllies != 0)
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC,
				(const char *)0x010EFC68,
				allyCount, m_foundWithAllies);
		return 0;
	}

	m_foundWithAllies = allyCount;
	m_bestCellX = cellX;
	m_bestCellY = cellY;

	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC,
			(const char *)0x010EFCB8, allyCount, m_foundWithAllies);

	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC,
			(const char *)0x010EFC68, allyCount, m_foundWithAllies);

	return 0;
}
