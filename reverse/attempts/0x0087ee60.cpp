// d_0087ee60
// partial score=0.92 date=2026-09-07
// cl: /O2 /Ob1 /G5
// stlport
// Open-BFME: GeometryInfo::calcBoundingStuff, retail 0x0087EE60, 301 bytes.

#include <vector>
#include <math.h>

typedef float Real;

inline const Real *bfmeMax(const Real *a, const Real *b)
{
	return (*a > *b) ? a : b;
}

struct GeometryBounds
{
	Real m_minX;
	Real m_minY;
	Real m_minZ;
	Real m_maxX;
	Real m_maxY;
	Real m_maxZ;
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Real m_offsetX;
	Real m_offsetY;
	Real m_offsetZ;
	char m_name[4];
	bool m_enabled;
	char m_padding[3];

	__declspec(noinline) Real getBoundingCircleRadius() const;
	__declspec(noinline) Real getBoundingSphereRadius() const;
};

extern const Real g_bfmeK1257;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void unknown();
	virtual const char *getName() const;
};

class GeometryInfo : public Snapshot
{
private:
	void calcBoundingStuff();

	bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	Real m_boundingSphereRadius;
	Real m_boundingCircleRadius;
	Real m_centerX;
	Real m_centerY;
	Real m_centerZ;
	Real m_extentX;
	Real m_extentY;
	std::vector<GeometryShape> m_shapes;

	void getBounds(GeometryBounds *bounds);
};

#pragma comment(linker, "/alternatename:?getBounds@GeometryInfo@@AAEXPAUGeometryBounds@@@Z=?d_0087e650@@YAXXZ")

inline Real sqr(Real x)
{
	return x * x;
}

__declspec(noinline) Real GeometryShape::getBoundingCircleRadius() const
{
	Real y = m_offsetY;
	Real result = 0.0f;
		switch (m_type)
	{
		case 0:
		case 1:
			result = sqrt(sqr(m_offsetX) + sqr(y)) + m_majorRadius;
			break;
		case 2:
			result = sqrt(sqr(fabs(m_offsetX) + m_majorRadius) + sqr(fabs(y) + m_minorRadius));
			break;
	}
	return result;
}

#pragma comment(linker, "/alternatename:?getBoundingSphereRadius@GeometryShape@@QBEMXZ=?d_0087ed70@@YAXXZ")

__declspec(noinline) Real GeometryShape::getBoundingSphereRadius() const
{
	Real result = 0.0f;
	switch (m_type)
	{
		case 0:
			result = sqrt(sqr(m_offsetX) + sqr(m_offsetY) + sqr(m_offsetZ)) + m_majorRadius;
			break;
		case 1:
		{
			Real xy = sqrt(sqr(m_offsetX) + sqr(m_offsetY));
			result = sqrt(sqr(xy + m_majorRadius) + sqr(fabs(m_offsetZ) + m_height * 0.5f));
			break;
		}
		case 2:
			result = sqrt(sqr(fabs(m_offsetX) + m_majorRadius) +
				sqr(fabs(m_offsetY) + m_minorRadius) +
				sqr(fabs(m_offsetZ) + m_height * 0.5f));
			break;
	}
	return result;
}

// ?calcBoundingStuff@GeometryInfo@@AAEXXZ present-unmatched
void GeometryInfo::calcBoundingStuff()
{
	GeometryBounds bounds;
	std::vector<GeometryShape>::const_iterator shape = m_shapes.begin();
	Real *sphereRadius = &m_boundingSphereRadius;
	Real *circleRadius = &m_boundingCircleRadius;
	*sphereRadius = 0.0f;
	*circleRadius = 0.0f;

	while (shape != m_shapes.end())
	{
		if (!shape->m_enabled)
		{
			++shape;
			continue;
		}

		Real sphereValue = shape->getBoundingSphereRadius();
		*sphereRadius = *bfmeMax(sphereRadius, &sphereValue);
		Real circleValue = shape->getBoundingCircleRadius();
		*circleRadius = *bfmeMax(circleRadius, &circleValue);
		++shape;
	}

	getBounds(&bounds);
	m_centerX = 0.0f;
	m_centerX += (bounds.m_minX + bounds.m_maxX) * g_bfmeK1257;
	m_centerY = 0.0f;
	m_centerY += (bounds.m_minY + bounds.m_maxY) * g_bfmeK1257;
	m_centerZ = 0.0f;
	m_centerZ += (bounds.m_minZ + bounds.m_maxZ) * g_bfmeK1257;

	Real negativeMinX = -bounds.m_minX;
	m_extentX = *bfmeMax(&bounds.m_maxX, &negativeMinX);
	Real negativeMaxY = -bounds.m_maxY;
	m_extentY = *bfmeMax(&bounds.m_maxY, &negativeMaxY);
}
