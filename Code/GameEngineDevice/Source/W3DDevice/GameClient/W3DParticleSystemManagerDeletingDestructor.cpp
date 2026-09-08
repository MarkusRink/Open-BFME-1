// cl: /O2
// Open-BFME: W3DParticleSystemManager scalar-deleting destructor wrapper,
// retail 0x006FA930 (30 bytes).  The primary vtable at 0x0112039C routes
// through ILT 0x0043DE6A to this wrapper; the adjacent retail source-path
// string names W3DFXParticleSystem.cpp.

class W3DParticleSystemManager
{
public:
	__declspec(noinline) virtual ~W3DParticleSystemManager();
};

W3DParticleSystemManager::~W3DParticleSystemManager()
{
}
