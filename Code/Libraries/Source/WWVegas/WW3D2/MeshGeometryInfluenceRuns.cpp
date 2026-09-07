// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail RVA 0x00924760, complete 174-byte accessor for compact influence runs.
// The original member name is unknown; Rva00924760InfluenceRuns records the
// recovered address and role. The influence reader at 0x00925380 passes twice
// the run count and writes two unsigned shorts per run through the result.
// This TU models only the pointer at MeshGeometryClass+0x5c, not the full class.

#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
	char _prefix_through_58[0x5c];
	ShareBufferClass<unsigned short> *InfluenceRunBuffer; // retail this+0x5c

protected:
	// Recovered role/address label only; original source name is unknown.
	unsigned short *Rva00924760InfluenceRuns(int count);
};

unsigned short *MeshGeometryClass::Rva00924760InfluenceRuns(int count)
{
	if (count && InfluenceRunBuffer == NULL) {
		InfluenceRunBuffer = NEW_REF(ShareBufferClass<unsigned short>,
			(count, "MeshGeometryClass::InfluenceRunBuffer", 0));
	}

	if (InfluenceRunBuffer != NULL) {
		return InfluenceRunBuffer->Get_Array();
	}
	return NULL;
}
