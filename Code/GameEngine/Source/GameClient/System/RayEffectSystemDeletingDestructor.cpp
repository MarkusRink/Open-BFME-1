// cl: /O2
// Open-BFME: RayEffectSystem scalar-deleting destructor wrapper, retail
// 0x005D37C0 (30 bytes). RayEffectSystem vtable 0x01110130 slot 0 routes
// here through ILT 0x0044A665; the matched constructor at 0x005D3720
// installs that vtable and the wrapper calls destructor ILT 0x00018467.

class RayEffectSystem
{
public:
    __declspec(noinline) virtual ~RayEffectSystem();
};

RayEffectSystem::~RayEffectSystem()
{
}
