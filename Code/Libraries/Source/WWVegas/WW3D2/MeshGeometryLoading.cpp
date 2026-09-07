// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME MeshGeometryClass::read_aabtree at 0x00923930, complete 149 bytes.
// Mesh chunk 0x90 selects the arm at 0x009700A8 and this culling-tree loader.
// The original GeneralsMD meshgeometry.cpp body releases the prior tree,
// allocates its replacement, loads the chunk and binds the tree to this mesh.
// BFME CullTree is at +0x90; the allocation is 0x1C bytes. This callee itself
// returns true in AL. RET 4 at 0x009239C2 ends before padding at 0x009239C5.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "sphere.h"
#include "multilist.h"
#include "chunkio.h"

class MeshGeometryClass;

class AABTreeClass : public W3DMPO, public RefCountClass
{
public:
    AABTreeClass(void);
    void Load_W3D(ChunkLoadClass &cload);
    void Set_Mesh(MeshGeometryClass *mesh);
private:
    char _storage[0x14]; // total AABTreeClass size 0x1c (retail allocator operand)
};

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
protected:
    bool read_aabtree(ChunkLoadClass &cload);

protected:
    void *UserText;               // BFME this+0x10
    void *MeshName;               // BFME this+0x14
    int Flags;                    // BFME this+0x18
    char SortLevel;               // BFME this+0x1c
    uint32 W3dAttributes;         // BFME this+0x20
    int PolyCount;                // BFME this+0x24
    int VertexCount;              // BFME this+0x28
    void *Poly;                   // BFME this+0x2c
    void *Vertex;                 // BFME this+0x30
    void *Slot34;                 // BFME this+0x34
    void *Slot38;                 // BFME this+0x38
    void *Slot3c;                 // BFME this+0x3c
    void *Slot40;                 // BFME this+0x40
    void *Slot44;                 // BFME this+0x44
    void *Slot48;                 // BFME this+0x48
    void *Slot4c;                 // BFME this+0x4c
    void *Slot50;                 // BFME this+0x50
    void *Slot54;                 // BFME this+0x54
    void *Slot58;                 // BFME this+0x58
    void *Slot5c;                 // BFME this+0x5c
    void *Slot60;                 // BFME this+0x60
    void *Slot64;                 // BFME this+0x64
    Vector3 BoundBoxMin;          // BFME this+0x68
    Vector3 BoundBoxMax;          // BFME this+0x74
    SphereClass BoundSphere;      // BFME this+0x80, radius at +0x8c
    AABTreeClass *CullTree;       // BFME this+0x90
};

// ?read_aabtree@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_aabtree(ChunkLoadClass &cload)
{
    REF_PTR_RELEASE(CullTree);
    CullTree = NEW_REF(AABTreeClass,());
    CullTree->Load_W3D(cload);
    CullTree->Set_Mesh(this);
    return true;
}
