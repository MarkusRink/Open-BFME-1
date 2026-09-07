// ?getVelocity@BoxEmissionVolumeModule@FXParticleSystem@@QAE?AUCoord3D@2@PBU32@MM@Z
// partial score=0.9 date=2026-09-07
// ?getVelocity@BoxEmissionVolumeModule@FXParticleSystem@@QAE?AUCoord3D@2@PBV32@MM@Z
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D() {}
	Coord3D( float xValue, float yValue, float zValue )
		: x( xValue ), y( yValue ), z( zValue ) {}
	~Coord3D() {}

	float x;
	float y;
	float z;

	__forceinline float length() const
	{
		return (float)sqrt( x * x + y * y + z * z );
	}

	__forceinline void normalize()
	{
		float len = length();
		if ( len != BfmeZeroRange )
		{
			float scale = g_bfmeDefaultBU / len;
			x *= scale;
			y *= scale;
			z *= scale;
		}
	}
};

class BoxEmissionVolumeModule
{
public:
	Coord3D getVelocity( const Coord3D *position, float speed, float );
};

Coord3D BoxEmissionVolumeModule::getVelocity(
	const Coord3D *position, float speed, float )
{
	Coord3D velocity;
	velocity.x = position->x;
	velocity.y = position->y;
	velocity.z = position->z;
	velocity.normalize();
	return Coord3D( velocity.x * speed, velocity.y * speed, velocity.z * speed );
}

}
