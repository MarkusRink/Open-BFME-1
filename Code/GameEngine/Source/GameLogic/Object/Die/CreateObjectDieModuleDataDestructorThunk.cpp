// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CreateObjectDieModuleData dtor. PropagandaTower SEH pattern.

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
};

class CreateObjectDieModuleDataBase
{
public:
	virtual ~CreateObjectDieModuleDataBase() {}
private:
	unsigned char m_pad[0x34];
};

class __declspec(novtable) CreateObjectDieModuleData : public CreateObjectDieModuleDataBase
{
public:
	virtual ~CreateObjectDieModuleData();
private:
	BFMERetailAsciiString m_member;
};

// ??1CreateObjectDieModuleData@@UAE@XZ
CreateObjectDieModuleData::~CreateObjectDieModuleData()
{
}
