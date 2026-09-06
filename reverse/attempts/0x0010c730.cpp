// ?BfmeParticleSystemXferMatrix@@YAXAAVXfer@@PAX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include "xfer.h"
#include "matrix3d.h"

struct BfmeMatrix3DLayout
{
	Vector4 row[ 3 ];
};

// ?BfmeParticleSystemXferMatrix@@YAXAAVXfer@@PAX@Z
void BfmeParticleSystemXferMatrix( Xfer &xfer, void *value )
{
	BfmeMatrix3DLayout *matrix = (BfmeMatrix3DLayout *)value;
	xfer == matrix->row[ 0 ].X == matrix->row[ 0 ].Y == matrix->row[ 0 ].Z == matrix->row[ 0 ].W
		== matrix->row[ 1 ].X == matrix->row[ 1 ].Y == matrix->row[ 1 ].Z == matrix->row[ 1 ].W
		== matrix->row[ 2 ].X == matrix->row[ 2 ].Y == matrix->row[ 2 ].Z == matrix->row[ 2 ].W;
}
