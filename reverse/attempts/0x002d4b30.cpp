// ??0GenerateMinefieldBehaviorModuleData@@QAE@XZ
// partial score=0.96 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// readable source family: Code/GameEngine/Source/GameLogic/Object/Behavior/GenerateMinefieldBehavior.cpp

typedef unsigned char Byte;

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class GMBUpgradeMuxData
{
public:
	GMBUpgradeMuxData();
	~GMBUpgradeMuxData();

private:
	Byte m_data[0x68];
};

class GMBAsciiString
{
public:
	GMBAsciiString();
	~GMBAsciiString();

private:
	void *volatile m_data;
};

class GMBDefaultString
{
public:
	~GMBDefaultString();

	void set(const char *text, int length);
	void *volatile m_data;
};

class GMBBehaviorModuleData
{
private:
	int m_data;
};

class GMBBoolPadding
{
public:
	~GMBBoolPadding();
	Byte m_data[2];
};

class GenerateMinefieldBehaviorModuleData : private GMBBehaviorModuleData,
	private GMBUpgradeMuxData
{
public:
	GenerateMinefieldBehaviorModuleData();
	virtual ~GenerateMinefieldBehaviorModuleData();

private:
	GMBAsciiString m_mineName;
	void *m_generationFX;
	float m_distanceAroundObject;
	float m_minesPerSquareFoot;
	bool m_onDeath;
	bool m_borderOnly;
	GMBBoolPadding m_padding82;
	GMBDefaultString m_bfmeDefaultName;
};

GenerateMinefieldBehaviorModuleData::GenerateMinefieldBehaviorModuleData() :
	m_generationFX(0),
	m_distanceAroundObject(0.0f),
	m_minesPerSquareFoot(0.0f)
{
	GMBDefaultString *defaultName = &m_bfmeDefaultName;
	m_onDeath = false;
	defaultName->m_data = 0;
	_ReadWriteBarrier();
	defaultName->set("<UNSPECIFIED>", 13);
	m_borderOnly = false;
}
