// ??0W3DOverlordTankDrawModuleData@@QAE@XZ
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: W3DOverlordTankDrawModuleData default construction. The Zero
// Hour source body is empty; BFME's inherited data layout constructs the
// upgrade and die-mux blocks after initializing the reference fields.

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class ThingRef
{
public:
	ThingRef() : m_ptr(0) {}
	__declspec(nothrow) ~ThingRef();

private:
	void *m_ptr;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_data[0x68];
};

class Rva002551A0DieMuxData
{
public:
	Rva002551A0DieMuxData();
	~Rva002551A0DieMuxData();

private:
	unsigned char m_data[0x2c];
};

class W3DOverlordTankDrawModuleData : public Snapshot
{
public:
	W3DOverlordTankDrawModuleData();
	virtual ~W3DOverlordTankDrawModuleData();

private:
	unsigned char m_gap04[4];
	ThingRef m_ref;
	unsigned int m_value0c;
	bool m_enabled;
	unsigned char m_gap11[3];
	UpgradeModuleDataSub m_upgradeData;
	Rva002551A0DieMuxData m_dieMuxData;
};

// ??0W3DOverlordTankDrawModuleData@@QAE@XZ
W3DOverlordTankDrawModuleData::W3DOverlordTankDrawModuleData()
	: m_value0c(0),
	  m_enabled(true)
{
}
