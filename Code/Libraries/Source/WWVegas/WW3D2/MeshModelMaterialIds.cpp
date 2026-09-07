// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
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
// BFME material-index loading from the original meshmdlio.cpp algorithms.
// read_texture_ids: RVA 0x0096DB40, full 317 bytes. Texture-stage chunk 0x49
// selects arm 0x0096ED9D; its call at 0x0096EDA1 reaches this body and checks
// AL against 1. RET 8 at +0x13A ends before three INT3 bytes at +0x13D.
// The BFME owning texture handle ABI is shared with MaterialRemapMesh.cpp.
// Peek_Texture at 0x0096D080 indexes the context array at +0xF8, copies
// a four-byte handle, and increments its 16-bit reference count at +4.
// The local field views retain BFME layouts without changing shared headers.
#include "w3d_file.h"

class TextureClass {
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
    void Release_Ref();
};

class BfmeHandleCX {
public:
    TextureClass *p;

    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) {
            p->Add_Ref();
        }
    }
    ~BfmeHandleCX() {
        if (p) {
            p->Release_Ref();
        }
    }
};

class ChunkLoadClass {
public:
    unsigned long Cur_Chunk_Length();
    unsigned long Read(void *buffer, unsigned long bytes);
};

class MeshMatDescClass {
protected:
    int PassCount;
    int VertexCount;
    int PolyCount;
    void *UV[8];
    int UVSource[4][2];
    void *ColorArray[2];
    int DCGSource[4];
    int DIGSource[4];
    BfmeHandleCX Texture[4][2];
    void *Shader[4];
    void *Material[4];
    void *TextureArray[4][2];
    void *MaterialArray[4];
    void *ShaderArray[4];
public:
    bool Has_Texture_Data(int pass, int stage) {
        return Texture[pass][stage].p != 0 ||
               TextureArray[pass][stage] != 0;
    }
    void Set_Single_Texture(const BfmeHandleCX &texture, int pass, int stage);
    void Set_Texture(int index, const BfmeHandleCX &texture, int pass, int stage);
};

class MeshLoadContextClass {
    unsigned char padding_88[0x88];
public:
    unsigned long PrelitChunkID;
    int CurPass;
    int CurTexStage;
private:
    unsigned char padding_94[0x10c - 0x94];
public:
    MeshMatDescClass AlternateMatDesc;
    BfmeHandleCX Peek_Texture(int index);
};

class MeshModelClass {
    unsigned char padding_00[0x24];
public:
    int PolyCount;
private:
    unsigned char padding_28[0x94 - 0x28];
public:
    MeshMatDescClass *DefMatDesc;
    int Get_Polygon_Count() const {
        return PolyCount;
    }
protected:
    bool read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

bool MeshModelClass::read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    unsigned long texid;
    int pass = context->CurPass;
    int stage = context->CurTexStage;
    MeshMatDescClass *matdesc = DefMatDesc;

    if (DefMatDesc->Has_Texture_Data(pass, stage)) {
        matdesc = &(context->AlternateMatDesc);
    }

    if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
        cload.Read(&texid, sizeof(texid));
        matdesc->Set_Single_Texture(context->Peek_Texture(texid), pass, stage);
    } else {
        for (int i = 0; i < Get_Polygon_Count(); i++) {
            cload.Read(&texid, sizeof(unsigned long));
            if (texid != 0xffffffff) {
                matdesc->Set_Texture(i, context->Peek_Texture(texid), pass, stage);
            }
        }
    }

    return true;
}
