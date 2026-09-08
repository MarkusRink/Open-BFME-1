// ?calcCameraConstraints@W3DView@@AAEXXZ
// partial score=0.35 date=2026-09-08
// Probe source for the BFME W3DView camera-constraint helper.
typedef float Real;
typedef int Int;

extern "C" double __cdecl sqrt(double);

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

struct Region2D
{
	struct Point
	{
		Real x;
		Real y;
	};

	Point lo;
	Point hi;
};

class Vector3
{
public:
	Vector3() {}

	Real X;
	Real Y;
	Real Z;

	static Real Find_X_At_Z(Real z, const Vector3 &p1, const Vector3 &p2);
	static Real Find_Y_At_Z(Real z, const Vector3 &p1, const Vector3 &p2);
};

class GlobalData
{
public:
	unsigned char m_padding[0xA88];
	int m_debugAI;
};

class TerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1C() = 0;
	virtual void getExtent(Region3D *extent) = 0;
};

class W3DView
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1C() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2C() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual Int getWidth() = 0;
	virtual void unused40() = 0;
	virtual Int getHeight() = 0;

private:
	void calcCameraConstraints();
	unsigned char m_padding0004[0x1C];
	Int m_originX;
	Int m_originY;
	unsigned char m_padding0028[0x23D0];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	bool m_cameraConstraintValid;

	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
};

#define TheGlobalData (*(GlobalData **)0x012ED5C8)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)

Real Coord3D::length() const
{
	return (Real)sqrt(x * x + y * y + z * z);
}

Real Vector3::Find_X_At_Z(Real z, const Vector3 &p1, const Vector3 &p2)
{
	return p1.X + ((z - p1.Z) * ((p2.X - p1.X) / (p2.Z - p1.Z)));
}

Real Vector3::Find_Y_At_Z(Real z, const Vector3 &p1, const Vector3 &p2)
{
	return p1.Y + ((z - p1.Z) * ((p2.Y - p1.Y) / (p2.Z - p1.Z)));
}

void W3DView::calcCameraConstraints()
{
	if (TheTerrainLogic)
	{
		Region3D mapRegion;
		TheTerrainLogic->getExtent( &mapRegion );

		Real maxEdgeZ = m_groundLevel;
		Coord3D center, bottom;
		ICoord2D screen;

		screen.x = 0.5f * getWidth() + m_originX;
		screen.y = 0.5f * getHeight() + m_originY;

		Vector3 rayStart, rayEnd;

		getPickRay( &screen, &rayStart, &rayEnd );

		center.x = Vector3::Find_X_At_Z( maxEdgeZ, rayStart, rayEnd );
		center.y = Vector3::Find_Y_At_Z( maxEdgeZ, rayStart, rayEnd );
		center.z = maxEdgeZ;

		screen.y = m_originY + 0.95f * getHeight();
		getPickRay( &screen, &rayStart, &rayEnd );
		bottom.x = Vector3::Find_X_At_Z( maxEdgeZ, rayStart, rayEnd );
		bottom.y = Vector3::Find_Y_At_Z( maxEdgeZ, rayStart, rayEnd );
		bottom.z = maxEdgeZ;
		center.x -= bottom.x;
		center.y -= bottom.y;

		Real offset = center.length();

		if ( TheGlobalData->m_debugAI )
			offset = -1000;

		m_cameraConstraint.lo.x = mapRegion.lo.x + offset;
		m_cameraConstraint.hi.x = mapRegion.hi.x - offset;
		m_cameraConstraint.lo.y = mapRegion.lo.y + offset;
		m_cameraConstraint.hi.y = mapRegion.hi.y - offset;
		m_cameraConstraintValid = true;
	}
}
