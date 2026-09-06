// ?angleBetween@@YAMPBURva003FD650Vec3@@0@Z
// partial score=0.95 date=2026-09-06
extern "C" float __cdecl acosf(float);
struct Rva003FD650Vec3 { float x; float y; float z; };
extern const float Rva003FD650One;
extern const float Rva003FD650MinusOne;
extern const float Rva003FD650One2;
extern const float Rva003FD650Zero;
float angleBetween(const Rva003FD650Vec3* a, const Rva003FD650Vec3* b)
{
	float dot = a->z * b->z + a->y * b->y + a->x * b->x;
	if (dot > Rva003FD650One)
		return Rva003FD650Zero;
	if (dot < Rva003FD650MinusOne)
		dot = -1.0f;
	else if (!(dot < Rva003FD650One2))
		return Rva003FD650Zero;
	return acosf(dot);
}
