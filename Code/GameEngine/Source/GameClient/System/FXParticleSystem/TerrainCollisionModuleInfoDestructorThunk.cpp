// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainCollisionModuleInfo dtor. SEH BFMERetailAsciiString @+0x4 PropagandaTower pattern.

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

namespace FXParticleSystem
{

class TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfoBase() {}
};

class __declspec(novtable) TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfo();
private:
	BFMERetailAsciiString m_buffer;
};

// ??1TerrainCollisionModuleInfo@FXParticleSystem@@UAE@XZ
TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo()
{
}

} // namespace FXParticleSystem
