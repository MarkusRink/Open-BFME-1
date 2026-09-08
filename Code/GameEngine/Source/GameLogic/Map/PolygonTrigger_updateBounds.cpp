// cl: /O2 /G6 /DNDEBUG /MD /EHsc-
// stlport

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

extern const Real g_bfmeK1253;

class PolygonTrigger
{
protected:
	void updateBounds() const;

private:
	unsigned char m_unmodelled_00[0x10];
	ICoord3D *m_points;
	Int m_numPoints;
	unsigned char m_unmodelled_18[4];
	mutable IRegion2D m_bounds;
	mutable Real m_radius;
	mutable Bool m_boundsNeedsUpdate;
};

// ?updateBounds@PolygonTrigger@@IBEXXZ
void PolygonTrigger::updateBounds() const
{
	const Int BIG_INT = 0x7ffff0;
	m_bounds.lo.x = m_bounds.lo.y = BIG_INT;
	m_bounds.hi.x = m_bounds.hi.y = -BIG_INT;
	Int i;
	for (i = 0; i < m_numPoints; ++i)
	{
		if (m_points[i].x < m_bounds.lo.x)
			m_bounds.lo.x = m_points[i].x;
		if (m_points[i].y < m_bounds.lo.y)
			m_bounds.lo.y = m_points[i].y;
		if (m_points[i].x > m_bounds.hi.x)
			m_bounds.hi.x = m_points[i].x;
		if (m_points[i].y > m_bounds.hi.y)
			m_bounds.hi.y = m_points[i].y;
	}
	m_boundsNeedsUpdate = 0;
	Real halfWidth = (m_bounds.hi.x - m_bounds.lo.x) / 2.0f;
	Real halfHeight = (m_bounds.hi.y + m_bounds.lo.y) / 2.0f;
	m_radius = sqrt(halfHeight * halfHeight + halfWidth * halfWidth);
}
