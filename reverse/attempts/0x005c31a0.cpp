// ?isInvisible@Particle@@QAE_NXZ
// partial score=0.88 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Particle::isInvisible, retail 0x005C31A0 (91 bytes).
// BFME delegates the particle-type-specific test to its modular particle
// handlers; the Generals source supplies the method identity and default.

typedef bool Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum ParticleType
{
	PARTICLE = 1,
	DRAWABLE = 2,
	STREAK = 3,
	VOLUME_PARTICLE = 4,
	SMUDGE = 5,
	TYPE6 = 6,
	TYPE7 = 7
};

class ParticleSystem
{
public:
	ParticleType getParticleType() const { return m_particleType; }

	unsigned char m_unmodelled_000[0x08];
	ParticleType m_particleType;
};

ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
	}

private:
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class ParticleVisibilityModule
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual Bool isInvisible(ParticleType type);
};

class Particle
{
public:
	Bool isInvisible();

private:
	unsigned char m_unmodelled_000[0x4C];
	ParticleSystemHandle m_system;
	unsigned char m_unmodelled_058[0x18];
	void *m_renderObject;
	unsigned char m_unmodelled_074[0x18];
	ParticleVisibilityModule *m_defaultModule;
	ParticleVisibilityModule *m_specialModule;
};

Bool Particle::isInvisible()
{
	if (m_renderObject)
		return false;

	ParticleSystem *system = m_system.operator->();
	ParticleType type = system->m_particleType;
	_ReadWriteBarrier();
	switch (type)
	{
		case PARTICLE:
		case DRAWABLE:
		case SMUDGE:
		case TYPE6:
			if (m_defaultModule)
				return m_defaultModule->isInvisible(type);
			return false;

		case STREAK:
		case VOLUME_PARTICLE:
		case TYPE7:
			if (m_specialModule)
				return m_specialModule->isInvisible(type);
			return false;
	}

	return true;
}
