// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME Display constructor at retail RVA 0x005CBF60.

#include <hash_map>
#include <list>
#include <vector>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

struct DisplayListValue
{
	int m_value[3];
};

struct Gen_t_005cb960_p12cd
{
	int m_value[3];
};

typedef _STL::pair<const int, Gen_t_005cb960_p12cd> DisplayMapPair;
typedef _STL::hash_map<int, Gen_t_005cb960_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<DisplayMapPair> > DisplayMap;

class Display : public SubsystemInterface, public Snapshot
{
public:
	Display();
	virtual ~Display();

private:
	int m_fields[2][14];
	int m_field7c;
	_STL::list<DisplayListValue> m_views;
	void *m_field84;
	void *m_field88;
	void *m_field8c;
	void *m_field90;
	void *m_field94;
	void *m_field98;
	DisplayMap m_map;
	_STL::vector<void *> m_vector;
};

Display::Display()
{
	m_field7c = 0;
	m_field90 = 0;
	m_field98 = 0;
	m_field84 = 0;
	m_field88 = 0;
	m_field8c = 0;
	m_field94 = 0;

	for (unsigned int i = 0; i < 14; ++i)
	{
		m_fields[0][i] = 0;
		m_fields[1][i] = 0;
	}
}
