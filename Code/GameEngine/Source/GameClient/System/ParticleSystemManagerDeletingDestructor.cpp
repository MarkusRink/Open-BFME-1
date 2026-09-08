// cl: /O2
// Open-BFME: ParticleSystemManager scalar-deleting destructor wrapper,
// retail 0x005CC080 (30 bytes).  The primary vtable at 0x0110FDCC routes
// through ILT 0x0042DD99 to this wrapper.

class ParticleSystemManager
{
public:
	__declspec(noinline) virtual ~ParticleSystemManager();
};

ParticleSystemManager::~ParticleSystemManager()
{
}
