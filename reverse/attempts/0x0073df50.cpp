// ?bfmeVisibleYE@BfmeOwnerYE@@QAEHPAUBfmeVec3YE@@M@Z (identity unknown)
// partial score=0.6 date=2026-09-07
// 88/91. Structure and both callees are identified -- retail calls
// ?Update_Frustum@CameraClass@@IBEXXZ (0x00931DF0) on the camera cached from
// this+0x104, then ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVSphereClass@@@Z
// (0x008DB060) cdecl with (camera+0x104, &sphere), and the tail
// dec/neg/sbb/neg is `result != 1` ([[sbb-select-needs-inverted-test]]).
// The sphere is a 16-byte local: x,y,z at entry-16/-12/-8 and the radius
// parameter at entry-4.
// UNSOLVED, the whole gap: retail copies x and y through the x87 stack
// (fld [eax]; fld [eax+4]; fxch st(1); fstp; fstp) and z through an integer
// register, and reserves 0x1c of stack -- 12 bytes more than the sphere needs,
// with one leftover store of z at entry-20. Plain float member assignment makes
// MSVC use integer moves throughout (88 bytes, no x87 at all); adding an
// explicit Vector3 temporary and copying it into the sphere makes it worse
// (105 bytes, the whole copy goes through memory). The x87 pair probably means
// x and y are by-value float ARGUMENTS to an inlined constructor while z is
// not -- try a Vec3(float,float,float) ctor plus Sphere(const Vec3&, float)
// next; that combination has not been tried.
struct BfmeVec3YE
{
	float m_bfmeXYE;
	float m_bfmeYYE;
	float m_bfmeZYE;
};

struct BfmeSphereYE
{
	BfmeVec3YE m_bfmeCenterYE;
	float m_bfmeRadiusYE;
};

int __cdecl bfmeOverlapYE(void *frustum, BfmeSphereYE *sphere);

class BfmeCameraYE
{
public:
	void bfmeUpdateYE();

	unsigned char m_bfmeHeadYE[0x104];
	unsigned char m_bfmeFrustumYE[4];
};

class BfmeOwnerYE
{
public:
	int bfmeVisibleYE(BfmeVec3YE *center, float radius);

	unsigned char m_bfmeHeadYE[0x104];
	BfmeCameraYE *m_bfmeCameraYE;
};

int BfmeOwnerYE::bfmeVisibleYE(BfmeVec3YE *center, float radius)
{
	BfmeSphereYE sphere;

	sphere.m_bfmeCenterYE.m_bfmeXYE = center->m_bfmeXYE;
	sphere.m_bfmeCenterYE.m_bfmeYYE = center->m_bfmeYYE;
	sphere.m_bfmeCenterYE.m_bfmeZYE = center->m_bfmeZYE;
	sphere.m_bfmeRadiusYE = radius;

	BfmeCameraYE *camera = m_bfmeCameraYE;

	camera->bfmeUpdateYE();

	return bfmeOverlapYE(camera->m_bfmeFrustumYE, &sphere) != 1;
}
