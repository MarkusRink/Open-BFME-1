// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include "xfer.h"

struct BfmeParticleSystemMatrixView
{
	float row0[ 4 ];
	float row1[ 4 ];
	float row2[ 4 ];
};

// ?BfmeParticleSystemXferMatrix@@YAXAAVXfer@@PAX@Z
void BfmeParticleSystemXferMatrix( Xfer &xfer, void *value )
{
	BfmeParticleSystemMatrixView *matrix =
		static_cast<BfmeParticleSystemMatrixView *>( value );
	Xfer &current = xfer == matrix->row0[ 0 ] == matrix->row0[ 1 ] == matrix->row0[ 2 ];
	float *row1 = matrix->row1;

	Xfer &next = current == matrix->row0[ 3 ]
		== row1[ 0 ] == row1[ 1 ] == row1[ 2 ];
	float *row2 = matrix->row2;

	next == row1[ 3 ]
		== row2[ 0 ] == row2[ 1 ] == row2[ 2 ] == row2[ 3 ];
}
