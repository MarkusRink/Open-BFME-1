// ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GarrisonContain constructor.  The module factory, matched
// destructor, OpenContain base call, and 3x40 Coord3D array fix the identity
// and layout independently.

class Thing;
class ModuleData;

class OpenContainPrimaryBase { public: virtual ~OpenContainPrimaryBase() {} private: unsigned char m_pad[8]; };
template <int Number> class OpenContainSecondaryBase { public: virtual ~OpenContainSecondaryBase() {} };
class OpenContainWideSecondaryBase { public: virtual ~OpenContainWideSecondaryBase() {} private: unsigned char m_pad[12]; };

struct GarrisonRecordTail
{
	void clearWithPrefix()
	{
		((unsigned int *)this)[-1] = 0;
		m_words[0] = 0; m_words[1] = 0;
		m_words[2] = 0; m_words[3] = 0;
	}
	unsigned int m_words[4];
};

struct GarrisonBaseRecord
{
	unsigned int m_first;
	GarrisonRecordTail m_tail;
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase, public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase, public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>, public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>, public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	OpenContain(Thing *, const ModuleData *);
	virtual ~OpenContain();
protected:
	unsigned char m_unreconstructed_38[0x9c];
	unsigned int m_d4;
	GarrisonBaseRecord m_records[40];
	unsigned int m_3f8;
};

class Coord3D
{
public:
	Coord3D();
	~Coord3D();
	void zero() { x = 0; y = 0; z = 0; }
private:
	unsigned int x, y, z;
};

class GarrisonContain : public OpenContain
{
public:
	GarrisonContain(Thing *, const ModuleData *);
	virtual ~GarrisonContain();
private:
	Coord3D m_garrisonPoint[3][40];
	unsigned int m_tail[6];
	bool m_flag9b4;
	bool m_flag9b5;
	bool m_flag9b6;
};

// ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z
GarrisonContain::GarrisonContain(Thing *thing, const ModuleData *data)
	: OpenContain(thing, data)
{
	m_d4 = 0;
	m_flag9b5 = false;
	m_3f8 = 0;
	m_flag9b4 = false;
	for (int i = 0; i != 40; ++i)
	{
		m_records[i].m_tail.clearWithPrefix();
		m_garrisonPoint[0][i].zero();
		m_garrisonPoint[1][i].zero();
		m_garrisonPoint[2][i].zero();
	}
	m_tail[0] = 0;
	m_tail[1] = 0;
	m_tail[2] = 0;
	m_flag9b6 = false;
	m_tail[3] = 0;
	m_tail[4] = 0;
	m_tail[5] = 0;
}
