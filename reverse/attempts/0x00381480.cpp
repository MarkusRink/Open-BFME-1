// ??0ExperienceLevelSystem@@QAE@XZ
// partial score=0.98 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ExperienceLevelSystem constructor, retail 0x00381480.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef float Real;

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void loadIniFilesFromLegend() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}

private:
	void *m_name;
};

struct ExperienceLevel
{
	char m_data[0xd8];
};

typedef _STL::list<ExperienceLevel> ExperienceLevelList;
typedef _STL::pair<const Int, ExperienceLevelList> ExperienceLevelMapPair;
typedef _STL::hash_map<Int, ExperienceLevelList, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<ExperienceLevelMapPair> > ExperienceLevelMap;

struct PendingExperienceLevel
{
	Int m_objectId;
	void *m_level;
	Bool m_showEffect;
};

class ExperienceScalarTable
{
public:
	ExperienceScalarTable(const AsciiString &name);

	std::vector<Real> m_scalars;
	AsciiString m_name;
};

class ExperienceLevelSystem : public SubsystemInterface
{
public:
	ExperienceLevelSystem();
	virtual ~ExperienceLevelSystem();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	ExperienceLevelMap m_levelMap;
	_STL::list<PendingExperienceLevel> m_pending;
	std::vector<ExperienceScalarTable *> m_scalarTables;
	ExperienceScalarTable *m_defaultLevel;
};

// ??0ExperienceLevelSystem@@QAE@XZ
ExperienceLevelSystem::ExperienceLevelSystem()
	: SubsystemInterface(),
	  m_levelMap(100),
	  m_pending(),
	  m_scalarTables()
{
	m_defaultLevel = new ExperienceScalarTable(
		AsciiString((const char *)0x010EA974));
	if (m_defaultLevel != 0)
		m_defaultLevel->m_scalars.push_back(1.0f);
}
