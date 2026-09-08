// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: GeometryUpgrade module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0011DFA0 allocates 0x94
// bytes and calls this constructor.  Its matched destructor independently
// fixes the +0x08 upgrade subobject, two twelve-byte vector members at
// +0x70/+0x7C, and three trailing AsciiStrings.

#include <vector>

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_unmodelled[ 0x68 ];
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class __declspec(novtable) GeometryUpgradeModuleDataPrimaryBase
{
public:
	virtual ~GeometryUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_unmodelled_04;
};

class __declspec(novtable) GeometryUpgradeModuleDataIntermediateBase
	: public GeometryUpgradeModuleDataPrimaryBase
{
protected:
	UpgradeModuleDataSub m_upgradeData; // +0x08
};

class GeometryUpgradeModuleData : public GeometryUpgradeModuleDataIntermediateBase
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();

private:
	_STL::vector<unsigned int> m_geometryNames; // +0x70
	_STL::vector<unsigned int> m_modelNames;    // +0x7C
	BFMERetailAsciiString m_name0;              // +0x88
	BFMERetailAsciiString m_name1;              // +0x8C
	BFMERetailAsciiString m_name2;              // +0x90
};

// ??0GeometryUpgradeModuleData@@QAE@XZ
GeometryUpgradeModuleData::GeometryUpgradeModuleData()
{
	m_name0.clear();
	m_name1.clear();
	m_name2.clear();
}
