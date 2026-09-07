// ?d_00733e30@@YAXXZ
// partial score=0.53 date=2026-09-07
// cl: /O2 /DNDEBUG /MD /EHsc /G5
// Retail 0x00733E30.  The tree records start at +0x1B0 and use a 0xE8
// stride.  Their count is at +0x2A7CB0, and the 0x5C-byte type records start
// at +0x2A7CBC.

typedef int Int;
typedef float Real;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct BfmeTreeQueryRecord
{
    char m_pad00[0x1B0];
    Coord3D m_location;
    Real m_scale;
    char m_pad1C0[0x30];
    Int m_treeType;
    unsigned char m_visible;
    char m_pad1F5[0x0F];
    Real m_radius;
    char m_pad208[0x28];
    Int m_queryState;
};

struct BfmeTreeQueryStride
{
    char m_bytes[0xE8];
};

struct BfmeTreeQueryType
{
    char m_pad00[0x2A7CBC];
    void *m_data;
    void *m_mesh;
	char m_pad08[0x1C];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
    unsigned char m_textureFlags[4];
    char m_pad48[0x14];
};

struct BfmeTreeTypeStride
{
    char m_bytes[0x5C];
};

class Rva00733E30TreeBuffer
{
public:
	bool queryTree(Int index, Coord3D *location, Real *radius,
		Coord2D *primary, Coord2D *secondary);

};

bool Rva00733E30TreeBuffer::queryTree(Int index, Coord3D *location,
	Real *radius, Coord2D *primary, Coord2D *secondary)
{
    if (index >= *(Int *)((char *)this + 0x2A7CB0))
        return false;

    BfmeTreeQueryStride *records = reinterpret_cast<BfmeTreeQueryStride *>(this);
    Int treeType = *(Int *)(records[index].m_bytes + 0x1F0);
    Int treeTypeForType = treeType;
    if (treeType < 0)
        return false;

    _ReadWriteBarrier();
    BfmeTreeQueryRecord *record = reinterpret_cast<BfmeTreeQueryRecord *>(
        (unsigned int)records + index * 0xE8);
    if (!record->m_visible)
        return false;
    BfmeTreeTypeStride *types = reinterpret_cast<BfmeTreeTypeStride *>(this);
    BfmeTreeQueryType *type = reinterpret_cast<BfmeTreeQueryType *>(
        types + treeTypeForType);
    void *data = type->m_data;
    if (!data || !type->m_textureFlags[0])
		return false;

	if (record->m_queryState)
		return false;

    location->x = record->m_location.x;
    location->y = record->m_location.y;
    location->z = record->m_location.z;
    Real value = record->m_radius * record->m_scale * *(Real *)0x010A13C0;
    if (*(volatile Real *)0x0108882C < value)
        value = *(volatile Real *)0x0108882C;
	*radius = value;
	*primary = type->m_primaryTextureCoords[1];
	*secondary = type->m_secondaryTextureCoords[1];
	return true;
}
