// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.89 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

namespace FXParticleSystem {

class GameClientRandomVariable
{
public:
	enum DistributionType { UNIFORM = 1 };
	GameClientRandomVariable() : m_low(0.0f), m_high(0.0f), m_distribution(0) {}
	void setRange(float low, float high, DistributionType distribution);

private:
	float m_low;
	float m_high;
	int m_distribution;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class DefaultPhysicsModuleInfo : public Snapshot
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();

private:
	float m_field0;
	float m_field1;
	float m_field2;
	int m_field3;
	GameClientRandomVariable m_var1;
};

DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
{
	m_field0 = 0.0f;
	m_field1 = 0.0f;
	m_field2 = 0.0f;
	m_field3 = 0;
	m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

}
