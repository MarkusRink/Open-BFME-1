// ?bfmeApply@BaseHeightMapResetBuffer@@QAE_NPAX0PAUCoord3D@@@Z
// partial score=0.82 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeheightmap /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// Retail 0x007331F0.  The surrounding reset-buffer methods use the same
// 12000 records at +0x1B0 with a count at +0x2A7CB0.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_USE_STATIC_LIB

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void normalize();
};

class TerrainLogic;

class BfmeThingCOF
{
public:
	Bool bfmeAskCOF();
	void bfmeRunCOF(void *a, void *b, void *c, void *d);
};

struct BaseHeightMapResetEntry
{
	Coord3D m_position;
	char m_pad0c[0x40 - 0x0c];
	int m_treeIndex;
	char m_pad44[0x58 - 0x44];
	void *m_owner;
	char m_pad5c[0x6c - 0x5c];
	Real m_height6c;
	Real m_height70;
	Coord3D m_normal;
	void *m_field80;
	int m_field84;
	int m_field88;
	int m_field8c;
	Real m_field90;
	int m_field94;
	int m_field98;
	int m_field9c;
	int m_fielda0;
	Real m_fielda4;
	int m_fielda8;
	int m_fieldac;
	int m_fieldb0;
	int m_fieldb4;
	Real m_fieldb8;
	int m_fieldbc;
	char m_padc0[0x08];
	void *m_fieldc8;
	char m_padcc[0x1c];
};

struct BaseHeightMapResetTreeInner
{
	char m_pad00[0x20];
	BfmeThingCOF *m_cof;
	char m_pad24[0x08];
	Real m_scale2c;
	Real m_scale30;
	char m_pad34[0x04];
	Real m_height38;
	char m_pad3c[0x20];
};

struct BaseHeightMapResetTree
{
	char m_pad00[0x20];
	BaseHeightMapResetTreeInner m_inner;
};

class BaseHeightMapResetBuffer
{
public:
	Bool bfmeApply(void *owner, void *unused, Coord3D *position);

private:
	char m_pad00[0x1b0];
	BaseHeightMapResetEntry m_entries[12000];
	int m_count;
	char m_pad2a7cb4[0x08];
	BaseHeightMapResetTree m_trees[64];
};

extern const Real BfmeZeroRange;
extern TerrainLogic *TheTerrainLogic;

Bool BaseHeightMapResetBuffer::bfmeApply(void *owner, void *, Coord3D *position)
{
	BaseHeightMapResetBuffer *self = this;
	if (owner == 0)
		return false;

	int index = 0;
	if (self->m_count <= 0)
		return false;

	void **record = (void **)((char *)self + 0x208);
	while (*record != owner)
	{
		++index;
		record = (void **)((char *)record + 0xe8);
		if (index >= self->m_count)
			return false;
	}

	BaseHeightMapResetEntry *entry = &self->m_entries[index];
	if (entry == 0)
		return false;
	if (entry->m_field80 != 0 || entry->m_fieldc8 != 0)
		return false;

	BaseHeightMapResetTreeInner *tree = &self->m_trees[entry->m_treeIndex].m_inner;
	Real height = *(Real *)((char *)TheTerrainLogic + 0x18f8);
	if (height <= BfmeZeroRange)
		height = tree->m_height38;

	entry->m_normal = *position;
	entry->m_normal.normalize();
	entry->m_field84 = 0;
	entry->m_height6c = height * tree->m_scale2c;
	entry->m_field80 = (void *)1;
	entry->m_field8c = 0;
	entry->m_height70 = height * tree->m_scale30;

	Coord3D local = entry->m_position;
	if (tree->m_cof != 0 && !tree->m_cof->bfmeAskCOF())
		tree->m_cof->bfmeRunCOF(&local, 0, 0, 0);

	entry->m_field94 = 0;
	entry->m_field98 = 0;
	entry->m_field9c = 0;
	entry->m_fielda0 = 0;
	entry->m_fielda4 = 1.0f;
	entry->m_fielda8 = 0;
	entry->m_fieldac = 0;
	entry->m_fieldb0 = 0;
	entry->m_fieldb4 = 0;
	entry->m_fieldb8 = 1.0f;
	entry->m_fieldbc = 0;
	entry->m_field9c = entry->m_position.x;
	entry->m_fieldac = entry->m_position.y;
	entry->m_fieldbc = entry->m_position.z;
	return true;
}
