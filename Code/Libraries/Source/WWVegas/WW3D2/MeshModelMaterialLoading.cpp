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
// BFME MeshModelClass::read_shaders, RVA 0x0096EA60, complete 197 bytes.
// read_prelit_material chunk 0x29 selects arm 0x0096FCAE; the call at
// 0x0096FCB2 reaches this body. The main read_chunks dispatcher agrees.
// This is the array of 16-byte W3dShaderStruct values, converted by
// W3dUtilityClass::Convert_Shader and appended to the context shader vector.
// ShaderCount is context+0x80; DynamicVectorClass<ShaderClass> is at +0xAC.
// The final RET 8 at 0x0096EB22 ends before INT3 padding at 0x0096EB25.
// Original algorithm: GeneralsMD WW3D2/meshmdlio.cpp. Actual vector/shader
// headers are reused; the BFME default shader word is explicit below.
#include "w3d_file.h"
#include "shader.h"
#include "w3d_util.h"
#include "vector.h"
class ChunkLoadClass {
public:
    unsigned long Read(void *, unsigned long);
};
class MeshLoadContextClass {
    friend class MeshModelClass;
    unsigned char beforeInfo[0x78];
    W3dMaterialInfoStruct MatInfo;
    unsigned char beforeShaders[0xac-0x88];
    DynamicVectorClass<ShaderClass> Shaders;
    int Add_Shader(ShaderClass shader) {
        int index=Shaders.Count();
        Shaders.Add(shader);
        return index;
    }
};
class MeshModelClass {
protected:
    bool read_shaders(ChunkLoadClass &, MeshLoadContextClass *);
};
bool MeshModelClass::read_shaders(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
    W3dShaderStruct shader;
    for (unsigned int i=0;i<context->MatInfo.ShaderCount;i++) {
        if (cload.Read(&shader,sizeof(shader)) != sizeof(shader)) return false;
        // BFME default shader word; the shared header retains the legacy cull bit.
        ShaderClass newshader(0x0010441b);
        W3dUtilityClass::Convert_Shader(shader,&newshader);
        int index=context->Add_Shader(newshader);
    }
    return true;
}
