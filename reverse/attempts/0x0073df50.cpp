// ?d_0073df50@@YAXXZ
// partial score=0.7 date=2026-09-07
class Vector3EUF
{
public:
	Vector3EUF() {}
	Vector3EUF(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};

class BfmeFrustumEUF
{
public:
	unsigned char m_bfmeBodyEUF[4];
};

class BfmeSphereEUF
{
public:
	Vector3EUF Center;
	float Radius;
};

class BfmeCamEUF
{
public:
	void bfmeUpdateFrustumEUF();

	unsigned char m_bfmeHeadEUF[0x104];
	BfmeFrustumEUF m_bfmeFrustumEUF;
};

int bfmeOverlapEUF(const BfmeFrustumEUF &frustum, const BfmeSphereEUF &sphere);

class BfmeHostEUF
{
public:
	int bfmeVisibleEUF(const Vector3EUF *pos, float radius);

	unsigned char m_bfmeHeadEUF[0x104];
	BfmeCamEUF *m_bfmeCamEUF;
};

int BfmeHostEUF::bfmeVisibleEUF(const Vector3EUF *pos, float radius)
{
	BfmeCamEUF *cam = m_bfmeCamEUF;
	Vector3EUF center(pos->X, pos->Y, pos->Z);
	BfmeSphereEUF sphere;

	sphere.Center = center;
	sphere.Radius = radius;

	cam->bfmeUpdateFrustumEUF();

	return bfmeOverlapEUF(cam->m_bfmeFrustumEUF, sphere) != 1;
}
