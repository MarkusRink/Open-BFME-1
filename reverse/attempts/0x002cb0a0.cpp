// ?loadDockPositions@DockUpdate@@IAEXXZ
// partial score=0.62 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DockUpdate::loadDockPositions, retail 0x002CB0A0, 323 bytes.
//
// The retail body obtains the drawable through Object's vtable, reads the
// DockStart, DockAction, DockEnd, and DockWaiting bones, and copies the waiting
// bones into the approach vector when its size matches the configured count.

typedef float Real;
typedef bool Bool;

class Matrix3D
{
};

struct Coord3D
{
public:
	Coord3D();
	~Coord3D();

	Coord3D &operator=(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
		return *this;
	}

	Real x;
	Real y;
	Real z;
};

class Drawable
{
public:
	int getPristineBonePositions(const char *name, int firstBone,
		Coord3D *positions, Matrix3D *transform, int count, int extra) const;
};

class Thing
{
};

class Object : public Thing
{
public:
	virtual void virtual0();
	virtual void virtual1();
	virtual void virtual2();
	virtual void virtual3();
	virtual void virtual4();
	virtual void virtual5();
	virtual void virtual6();
	virtual void virtual7();
	virtual void virtual8();
	virtual void virtual9();
	virtual Drawable *getDrawable() const;
};

struct Coord3DVector
{
	Coord3D *m_begin;
	Coord3D *m_end;
	Coord3D *m_capacity;

	int size() const
	{
		return static_cast<int>(m_end - m_begin);
	}

	Coord3D &operator[](int index)
	{
		return m_begin[index];
	}
};

class DockUpdate
{
protected:
	void loadDockPositions();
	unsigned char m_unmodelled_000[0x24];
	Coord3D m_enterPosition;
	Coord3D m_dockPosition;
	Coord3D m_exitPosition;
	int m_numberApproachPositions;
	int m_numberApproachPositionBones;
	Bool m_positionsLoaded;
	unsigned char m_unmodelled_051[0x54 - 0x51];
	Coord3DVector m_approachPositions;
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) + 0x08);
	}
};

// ?loadDockPositions@DockUpdate@@IAEXXZ present-unmatched
void DockUpdate::loadDockPositions()
{
	Drawable *drawable = getObject()->getDrawable();

	if (drawable)
	{
		drawable->getPristineBonePositions("DockStart", 0,
			&m_enterPosition, 0, 1, 0);
		drawable->getPristineBonePositions("DockAction", 0,
			&m_dockPosition, 0, 1, 0);
		drawable->getPristineBonePositions("DockEnd", 0,
			&m_exitPosition, 0, 1, 0);

		if (m_numberApproachPositions != -1)
		{
			Coord3D approachBones[10];
			m_numberApproachPositionBones = drawable->getPristineBonePositions(
				"DockWaiting", 1, approachBones, 0,
				m_numberApproachPositions, 0);

			if (m_numberApproachPositions == m_approachPositions.size())
			{
				for (int copyIndex = 0;
					copyIndex < m_numberApproachPositions; ++copyIndex)
					m_approachPositions[copyIndex] = approachBones[copyIndex];
			}
		}
		else
		{
			m_numberApproachPositionBones = 0;
		}

		m_positionsLoaded = true;
	}
}
