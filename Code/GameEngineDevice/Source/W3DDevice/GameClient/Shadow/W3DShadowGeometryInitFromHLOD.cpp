// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source

#include "always.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/hlod.h"

// BFME adds two typed render-object views immediately after Class_ID.  The
// MeshClass implementations at 0x0092C710 and 0x0092C720 both return the
// receiver unchanged; this body reaches the later slot (+0x14).
class BfmeMeshRenderObjView
{
public:
	virtual void Slot_00(void);
	virtual void Slot_04(void);
	virtual void Slot_08(void);
	virtual int Class_ID(void) const;
	virtual RenderObjClass *Mesh_View_10(void);
	virtual RenderObjClass *Mesh_View_14(void);
};

// The matched constructor and virtual destructor establish the global class
// identity and the two tail fields at +0x2094/+0x2098.  Keeping the preceding
// bytes opaque avoids importing unrelated geometry implementation details.
class W3DShadowGeometry
{
public:
	int initFromHLOD(RenderObjClass *robj);
	int initFromMesh(RenderObjClass *robj, int mesh_index,
		W3DShadowGeometry *parent_geometry);

private:
	unsigned char m_opaque[0x2094];
	int m_meshCount;
	int m_numTotalsVerts;
};

// ?initFromHLOD@W3DShadowGeometry@@QAEHPAVRenderObjClass@@@Z
int W3DShadowGeometry::initFromHLOD(RenderObjClass *robj)
{
	HLodClass *hlod = (HLodClass *)robj;

	m_numTotalsVerts = 0;
	m_meshCount = 0;

	int top = hlod->Get_LOD_Count() - 1;
	for (int i = 0; i < hlod->Get_Lod_Model_Count(top); ++i)
	{
		if (hlod->Peek_Lod_Model(top, i) != 0 &&
			hlod->Peek_Lod_Model(top, i)->Class_ID() == RenderObjClass::CLASSID_MESH)
		{
			RenderObjClass *mesh =
				((BfmeMeshRenderObjView *)hlod->Peek_Lod_Model(top, i))->Mesh_View_14();
			initFromMesh(mesh, i, this);
		}
	}

	return m_meshCount != 0;
}
