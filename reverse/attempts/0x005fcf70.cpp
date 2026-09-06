// ?d_005fcf70@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ParticleSystem
{
public:
	void getPosition(Coord3D *pos);

	private:
		unsigned char m_pad[0x12c];

	public:
	unsigned int m_field12c;
};

ParticleSystem *Make00001B18();

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make00001B18();
		return target;
	}

private:
	ParticleSystem *m_target;
};

class BfmeThingCOF
{
public:
	bool bfmeAskCOF();
	void bfmeRunCOF(void *a, void *b, void *c, void *d);
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, void *normal);
};

extern TerrainLogic *TheTerrainLogic;

class ParticleTerrainCollisionModule
{
public:
	virtual void slot00();
	virtual void update();

private:
	BfmeParticleSystemPtr m_system;
	unsigned char m_pad08[0x15];
	bool m_deactivate;
	unsigned char m_pad1e[0x1a];
	BfmeThingCOF * volatile m_eventFX;
	unsigned char m_pad3c[4];
	bool m_active;
	unsigned char m_pad41[3];
};

void ParticleTerrainCollisionModule::update()
{
	ParticleSystem *system = m_system.operator->();
	Coord3D position;
	system->getPosition(&position);
	if (!m_active)
		return;

	if (!m_eventFX)
		return;
	if (position.z <= TheTerrainLogic->getGroundHeight(position.x, position.y, 0))
	{
		BfmeThingCOF *eventFX = m_eventFX;
		if (eventFX != 0 && !eventFX->bfmeAskCOF())
			eventFX->bfmeRunCOF(&position, 0, 0, 0);

		bool deactivate = m_deactivate;
		m_active = false;
		if (deactivate)
		{
			if (!m_system)
			{
				system = Make00001B18();
				system->m_field12c = 1;
			}
			else
			{
				system = m_system;
				system->m_field12c = 1;
			}
		}
	}
}
