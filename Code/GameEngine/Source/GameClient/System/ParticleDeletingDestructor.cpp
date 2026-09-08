// cl: /O2
// Open-BFME: Particle scalar-deleting destructor wrapper, retail 0x005CF050
// (30 bytes). Particle vtable 0x0110FE8C slot 0 routes here through ILT
// 0x0043F558; slot 1 is Particle::loadPostProcess and slot 2 returns
// "FXParticle", independently proving the class identity.

class Particle
{
protected:
    __declspec(noinline) virtual ~Particle();
};

Particle::~Particle()
{
}
