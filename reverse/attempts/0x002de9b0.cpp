// ?doNugget@SpawnAndFadeNugget@@UBEXPBVDamageInfo@@PBUCoord3D@@@Z
// partial score=0.92 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// BFME SpawnAndFadeNugget weapon nugget, retail 0x002DE9B0.

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

namespace WWMath
{
	class InlineTrig
	{
	public:
		static __forceinline Real Sin(Real radians)
		{
			Real result;
			__asm {
				fld dword ptr [radians]
				fsin
				fstp dword ptr [result]
			}
			return result;
		}

		static __forceinline Real Cos(Real radians)
		{
			Real result;
			__asm {
				fld dword ptr [radians]
				fcos
				fstp dword ptr [result]
			}
			return result;
		}
	};
}

struct Coord3D
{
	Real x, y, z;
};

class ObjectStatusMaskType
{
public:
	ObjectStatusMaskType()
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
	}

	UnsignedInt m_bits[3];
};

class AsciiString
{
};

class ThingTemplate
{
};

class Team
{
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	Real m_orientation;
	char m_pad48[0x23c - 0x48];
	Team *m_team;
};

class GameLogic
{
public:
	Object *bfmeFind1011(Int id);
};

extern GameLogic *TheBfmeGameLogic;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *g_bfmeOtherBN;

typedef Object *(__fastcall *ThingFactoryNewObjectCall)(
	BfmeThingFactory *, ObjectStatusMaskType *, ThingTemplate *, Team *,
	const volatile ObjectStatusMaskType &, void *);

extern void j_0004494a();

class BFMEObjectLayerQuery
{
public:
	Int getLayer() const;
};

class BfmeThingPositionSetter
{
public:
	void setPosition(const Coord3D *position);
};

class BfmeD1044
{
public:
	void bfmeStep1044(Int value);
};

class BfmeDrop987
{
public:
	void bfmeClear987(Int first, Int second);
};

class BfmeSubBIA
{
public:
	void *ask();
};

struct BfmeAskResult
{
	char m_pad00[0xdc];
	UnsignedInt m_flags;
};

struct BfmeAskLink
{
	char m_pad00[4];
	BfmeSubBIA *m_query;
};

struct BfmeSpawnedObject
{
	char m_pad00[4];
	BfmeAskLink *m_link;
};

class TerrainLogic
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual Real getLayerForDestination(Real x, Real y, Int layer) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
public:
	char m_pad00[0x0c];
	BFMEPathfinderMapShim *m_pathfinder;
};

extern AI *TheAI;

class DamageInfo
{
	public:
	char m_pad00[8];
	Int m_sourceID;
};

class SpawnAndFadeNugget
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void doNugget(const DamageInfo *damageInfo,
		const Coord3D *position) const;

	char m_pad00[0x58 - 4];
	char m_objectTargetFilter[4];
	AsciiString m_spawnedObjectName;
	Coord3D m_spawnOffset;
};

// ?doNugget@SpawnAndFadeNugget@@UBEXPBVDamageInfo@@PBUCoord3D@@@Z
void SpawnAndFadeNugget::doNugget(const DamageInfo *damageInfo,
	const Coord3D *) const
{
	Object *source = TheBfmeGameLogic->bfmeFind1011(damageInfo->m_sourceID);
	const ThingTemplate *thingTemplate = g_bfmeOtherBN->findTemplate(m_spawnedObjectName);
	if (!thingTemplate)
		return;

	ObjectStatusMaskType statusMask;
	Object *spawned = ((ThingFactoryNewObjectCall)j_0004494a)(
		g_bfmeOtherBN, &statusMask, (ThingTemplate *)thingTemplate,
		source->m_team, statusMask, 0);

	Coord3D position;
	position.x = source->m_position.x;
	position.y = source->m_position.y;
	position.z = source->m_position.z;
	Real orientation = source->m_orientation;
	Real sinOrientation = WWMath::InlineTrig::Sin(orientation);
	Real cosOrientation = WWMath::InlineTrig::Cos(orientation);
	position.x += m_spawnOffset.x * cosOrientation - m_spawnOffset.y * sinOrientation;
	position.y += m_spawnOffset.x * sinOrientation + m_spawnOffset.y * cosOrientation;
	position.z = TheTerrainLogic->getLayerForDestination(
		position.x, position.y,
		((const BFMEObjectLayerQuery *)source)->getLayer());

	((BfmeThingPositionSetter *)spawned)->setPosition(&position);
	((BfmeD1044 *)spawned)->bfmeStep1044(1);
	((BfmeDrop987 *)source)->bfmeClear987(8, 22);

	BfmeAskLink *link = ((BfmeSpawnedObject *)spawned)->m_link;
	if (link && link->m_query)
	{
		BfmeAskResult *result = (BfmeAskResult *)link->m_query->ask();
		if (result->m_flags & 0x400)
			TheAI->m_pathfinder->addObjectToPathfindMap(spawned);
	}
}
