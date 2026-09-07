// cl: /DNDEBUG /MD /EHsc
//
// BFME's road buffer constructor at retail RVA 0x006DED60. The BaseHeightMap
// constructor allocates this 0x110-byte object for its road buffer, and the
// reset path calls the matching road-buffer cleanup at 0x00706E60.

// stlport
#include <set>

class Rva006DED60RoadRef
{
public:
	Rva006DED60RoadRef();
	~Rva006DED60RoadRef();

	unsigned int m_first;
	unsigned int m_second;
	unsigned char m_flag;
};

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > Rva006DED60RoadSet;

class Rva006DED60RoadBuffer
{
public:
	Rva006DED60RoadBuffer();

	void freeRoadBuffers();
	void allocateRoadBuffers();

private:
	void *m_vertexBuffer;
	void *m_indexBuffer;
	int m_numRoads;
	int m_initializedRoads;
	int m_maxRoadVertices;
	int m_maxRoadIndices;
	Rva006DED60RoadRef m_roadRefs[10];
	unsigned int m_padding90;
	Rva006DED60RoadSet m_roadSets[10];
	unsigned char m_initialized;
};

Rva006DED60RoadBuffer::Rva006DED60RoadBuffer()
{
	m_initialized = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_numRoads = 0;
	m_initializedRoads = 0;
	m_maxRoadIndices = 0xea60;
	m_maxRoadVertices = 0x7530;

	for (int i = 0; i < 10; ++i)
		m_roadRefs[i].m_first = 0;

	freeRoadBuffers();
	allocateRoadBuffers();
	m_initialized = 1;
}
