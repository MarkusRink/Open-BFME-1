// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DieModuleData ctor. GenBase009A1A30 base + DieMuxData @+8.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x009A1A30 here (vptr
// 0x01141640 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. GenBase009A1A30 is the neutral,
// address-derived spelling symbols.csv already pins at that body.
class GenBase009A1A30
{
public:
	GenBase009A1A30();
	virtual ~GenBase009A1A30() {}
private:
	unsigned char m_pad[4];
};

class DieMuxData
{
public:
	DieMuxData();
private:
	unsigned char m_opaque[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public GenBase009A1A30
{
public:
	DieModuleData();
	virtual void dieModuleDataAnchor();
private:
	DieMuxData m_mux;
};

// ??0DieModuleData@@QAE@XZ
DieModuleData::DieModuleData()
{
}
