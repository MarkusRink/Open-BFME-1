// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Local semantic ABI slice for retail RVA 0x00924810.
//
// The existing header names this role Get_Poly_Surface_Type, and its inline
// body has the same NDEBUG operations.  Since the retail body has no surviving
// symbol row or direct call edge, this method name is address-qualified and
// records the recovered role without asserting a historical decorated name.

#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
	char _prefix_through_5c[0x60];
	ShareBufferClass<unsigned char> *PolySurfaceType; // retail this+0x60

public:
	// Recovered role/address label only; original standalone symbol is unknown.
	unsigned char Rva00924810PolySurfaceTypeAt(int poly_index) const;
};

unsigned char MeshGeometryClass::Rva00924810PolySurfaceTypeAt(int poly_index) const
{
	unsigned char *type = PolySurfaceType->Get_Array();
	return type[poly_index];
}
