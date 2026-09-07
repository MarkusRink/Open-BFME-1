// cl: /DNDEBUG /MD
//
// Open-BFME: the Pathfinder queries that answer a question about a straight
// segment of the world.
//
//   ?snapLine@         0x003E6AF0, 110 bytes
//   ?isLinePassable@   0x003EE7A0, 131 bytes  (eight arguments)
//   ?isLinePassable@   0x003EE8D0, 119 bytes  (six arguments)
//   ?lineClear@        0x003EE970, 102 bytes
//
// One body four times: build a payload object on the stack, convert both world
// endpoints to cell coordinates with worldToCell, walk the cells between them,
// and turn the walk's verdict into the answer. snapLine is the only one that
// does anything else -- when the walk reports a hit it copies the payload's
// working position back over the caller's destination.
//
// The payload type is not decoration: it IS the dispatch. Retail has a dozen
// cell-space line walks, each taking a different user-data struct, and picking
// the struct picks the walker. These four reach three of them, and one file each
// could only ever declare "the" iterateCellsAlongLine, so nothing said that
// different bodies are being called:
//
//   Rva003DE480Struct     ILT 0x00005713 -> 0x003DE480   snapLine
//   BfmeCheckMovementInfo ILT 0x00029DF7 -> 0x003E7F80   both isLinePassable
//   Rva003E5A50Info       ILT 0x0001DAA2 -> 0x003E8440   lineClear
//
// A fifth query belongs in this file and is not in it: lineBlocked (0x003EE850,
// ILT 0x00023DDF -> 0x003E81E0, payload Rva003DB640Info) is the same body
// answering the opposite question -- true when the walk DID hit something. It
// stays in Pathfinder_lineBlocked.cpp because that file also DEFINES
// Rva003DB640Info's constructor, for which the ledger declares no row, and the
// commit hook refuses any newly staged source that defines a function it does
// not know. Give that constructor a row and it belongs here.
//
// The overload set below is the point of the file. It also lines the two
// isLinePassable overloads up: they differ only in what they put in the payload
// -- the eight-argument one takes the caller's crusher and restrict-surfaces
// flags and forces allowPinched off, the six-argument one hard-codes crusher
// off with restrict-surfaces and allowPinched on -- and lineClear answers the
// same "did the walk stay clear" question with a different walker.
//
// The Bool spellings differed across the four files and two of them mattered:
// the predicates return H (int), and worldToCell returns _N (bool). They are
// written out below rather than hidden behind a typedef that meant two things.

typedef int Int;
typedef int Bool;								// the predicates mangle as H
typedef unsigned int size_t;

inline void *operator new(size_t, void *p)
{
	return p;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Pathfinder;

// ---------------------------------------------------------------- snapLine
// The payload Rva003D61C0::set() fills; only its working Coord3D is read back.
struct Rva003D61C0Vec
{
	Int a, b, c;
};

class Rva003D61C0
{
public:
	Rva003D61C0 &set(Int a, Int b, const Rva003D61C0Vec *p);

	Int m_00;
	Int m_04;
	Coord3D m_pos;
};

struct Rva003DE480Struct;

// -------------------------------------------------------- both isLinePassable
class Object;

class BfmeCheckMovementInfo
{
public:
	BfmeCheckMovementInfo(Pathfinder *pathfinder, Object *obj, Int zone,
		Bool considerTransient, Bool isCrusher, Bool restrictSurfaces,
		Bool allowPinched);

	unsigned char m_body[0x58];
};

// --------------------------------------------------------------- lineClear
class Rva003E5A50Info
{
public:
	Rva003E5A50Info(Pathfinder *pathfinder, Object *obj, Int value);

	unsigned char m_body[0x54];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);

	// One name, four callees -- the user-data type is what selects the walker.
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DE480Struct *userData);		///< ILT 0x00005713 -> 0x003DE480
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, BfmeCheckMovementInfo *info);		///< ILT 0x00029DF7 -> 0x003E7F80
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E5A50Info *info);			///< ILT 0x0001DAA2 -> 0x003E8440

	void snapLine(const Coord3D *from, Coord3D *to);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient,
		Bool isCrusher, Bool restrictSurfaces);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient);
	Bool lineClear(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
};

// ?snapLine@Pathfinder@@QAEXPBUCoord3D@@PAU2@@Z
// Walk the segment on LAYER_GROUND and, if the cell iterator reports a hit,
// write the payload's working Coord3D back onto the destination.
void Pathfinder::snapLine(const Coord3D *from, Coord3D *to)
{
	Rva003D61C0 info;
	info.set((Int)this, 4, (const Rva003D61C0Vec *)from);
	ICoord2D start;
	worldToCell(from, &start);
	ICoord2D end;
	worldToCell(to, &end);
	if (iterateCellsAlongLine(start, end, LAYER_GROUND, (Rva003DE480Struct *)&info)) {
		to->x = info.m_pos.x;
		to->y = info.m_pos.y;
		to->z = info.m_pos.z;
	}
}

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2HHH@Z
// The caller's crusher and restrict-surfaces flags, allowPinched forced off.
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient,
	Bool isCrusher, Bool restrictSurfaces)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, isCrusher, restrictSurfaces, 0);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2H@Z
// crusher off, restrict-surfaces and allowPinched on.
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, 0, 1, 1);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}

// ?lineClear@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
Bool Pathfinder::lineClear(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x54];
	Rva003E5A50Info *payload = new (storage) Rva003E5A50Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}
