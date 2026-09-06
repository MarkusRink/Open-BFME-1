// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgradeModuleData dtor.
// Member @+0x10, triple BFMERetailAsciiString @+0x78/+0x7c/+0x80.

class ObjectCreationUpgradeModuleDataMemberA
{
public:
	~ObjectCreationUpgradeModuleDataMemberA();
private:
	unsigned char m_pad[0x68];
};

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
};

class ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ObjectCreationUpgradeModuleData
	: public ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleData();
private:
	ObjectCreationUpgradeModuleDataMemberA m_a;
	BFMERetailAsciiString m_b;
	BFMERetailAsciiString m_c;
	BFMERetailAsciiString m_d;
};

// ??1ObjectCreationUpgradeModuleData@@UAE@XZ
ObjectCreationUpgradeModuleData::~ObjectCreationUpgradeModuleData()
{
}
