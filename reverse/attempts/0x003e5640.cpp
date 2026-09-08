// ??0BfmeCheckMovementInfo@@QAE@PAVPathfinder@@PAVObject@@HHHHH@Z
// partial score=0.45 date=2026-09-08
// cl: /DNDEBUG /MD
//
// Retail 0x003E5640: BfmeCheckMovementInfo constructor used by both
// eight- and six-argument Pathfinder::isLinePassable.

typedef int Int;
typedef unsigned char Bool;

class Object;

class Pathfinder
{
public:
	void bfmeQuery( Object *obj, Int *radius, Bool *center );
};

class Player
{
public:
	char m_padding00[0xc8];
	Int m_flagsC8;
	char m_paddingCC[0xd4 - 0xcc];
	Int m_flagsD4;
	char m_paddingD8[0x444 - 0xd8];
	Int m_field444;
	char m_padding448[0x4cc - 0x448];
	Bool m_field4cc;
};

class BfmeSubBIA
{
public:
	Player *bfmeAskBIA();
};

class Team
{
public:
	char m_padding00[4];
	BfmeSubBIA *m_bia;
};

class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID();
};

class Object
{
public:
	Bool bfmeIsComputerControlled() const;

	char m_padding00[4];
	Team *m_team;
	char m_padding08[0x1fc];
	AIUpdateInterface *m_ai;
};

static __forceinline Player *getBfmePlayer( Object *obj )
{
	Team *team = obj->m_team;
	if (team == 0)
		return 0;
	BfmeSubBIA *bia = team->m_bia;
	if (bia == 0)
		return 0;
	return bia->bfmeAskBIA();
}

class BfmeCheckMovementInfo
{
public:
	BfmeCheckMovementInfo( Pathfinder *pathfinder, Object *obj, Int zone,
		Int considerTransient, Int isCrusher, Int restrictSurfaces,
		Int allowPinched );

	Pathfinder *m_pathfinder;
	Object *m_obj;
	Bool m_isCrusher;
	char m_padding09[3];
	Int m_scratch0c;
	Int m_scratch10;
	Int m_scratch14;
	Int m_radius;
	Bool m_center;
	Bool m_padding1d;
	Int m_mode;
	Int m_scratch24;
	Int m_scratch28;
	union
	{
		struct
		{
			Int m_coordinateZone;
			Int m_coordinateSamePlayer;
			Int m_coordinatePlayerIndex;
		};
		struct
		{
			Bool m_padding2c;
			Bool m_padding2d;
			char m_padding2e[2];
			Int m_zoneSentinel;
		};
	};
	Int m_scratch34;
	Bool m_playerIsComputer;
	Bool m_padding39;
	Bool m_padding3a;
	char m_padding3b;
	Int m_scratch3c;
	char m_padding40[8];
	Int m_zone;
	Bool m_samePlayer;
	Bool m_computer;
	char m_padding4e[2];
	Int m_playerIndex;
	Bool m_allowPinched;
	char m_padding55[3];
};

BfmeCheckMovementInfo::BfmeCheckMovementInfo(
	Pathfinder *pathfinder, Object *obj, Int zone, Int considerTransient,
	Int isCrusher, Int restrictSurfaces, Int allowPinched )
{
	m_pathfinder = pathfinder;
	m_isCrusher = isCrusher;
	m_obj = obj;
	m_scratch0c = 0;
	m_scratch10 = 0;
	m_scratch14 = 0;
	m_radius = 0;
	m_padding1d = 0;
	m_mode = 0;
	m_scratch24 = 0;
	m_scratch28 = 0;
	m_padding2c = 0;
	m_padding2d = 0;
	m_zoneSentinel = -1;
	m_scratch34 = 0;
	m_playerIsComputer = 0;
	m_padding39 = 0;
	m_padding3a = 0;
	m_scratch3c = 0;

	Player *player = getBfmePlayer( obj );
	Int playerIndex = player->m_field444;
	player = getBfmePlayer( obj );
	Bool samePlayer = player->m_field4cc == 0;
	Bool computer = obj->bfmeIsComputerControlled();
	m_zone = zone;
	m_samePlayer = samePlayer;
	m_computer = computer;
	m_playerIndex = playerIndex - 1;
	m_allowPinched = allowPinched;
	m_coordinateZone = m_zone;
	m_coordinateSamePlayer = m_samePlayer;
	m_coordinatePlayerIndex = m_playerIndex;
	m_center = considerTransient;

	if (restrictSurfaces) {
		player = getBfmePlayer( obj );
		if ((player->m_flagsC8 & 0x800) != 0)
			m_mode = 15;
	}
	if (m_mode == 0)
		m_mode = 13;

	m_scratch24 = obj->m_ai->getIgnoredObstacleID();

	player = getBfmePlayer( obj );
	if ((player->m_flagsD4 & 0x1000) != 0) {
		m_radius = 1;
		m_center = 1;
		return;
	}
	m_pathfinder->bfmeQuery( obj, &m_radius, &m_center );
}
