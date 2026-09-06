// ?zeroChunkVectors@Rva007B96E0Owner@@QAEXXZ
// partial score=0.9 date=2026-09-06
struct Rva007B96E0Vec3 { float x; float y; float z; };
struct Rva007B96E0Chunk { char m_pad[0x68]; Rva007B96E0Chunk* m_next; char m_pad2[0x1200 - 0x6c]; Rva007B96E0Vec3 m_vectors[0xa0]; };
struct Rva007B96E0Owner { Rva007B96E0Chunk* m_first; void zeroChunkVectors(); };
void Rva007B96E0Owner::zeroChunkVectors()
{
	for (Rva007B96E0Chunk* c = m_first; c; c = c->m_next) {
		for (int i = 0; i < 0xa0; ++i) {
			c->m_vectors[i].z = 0.0f;
			c->m_vectors[i].y = 0.0f;
			c->m_vectors[i].x = 0.0f;
		}
	}
}
