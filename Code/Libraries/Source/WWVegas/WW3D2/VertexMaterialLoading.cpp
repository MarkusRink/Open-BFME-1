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
// BFME VertexMaterialClass::Parse_W3dVertexMaterialStruct at 0x00921C80,
// complete 421 bytes. The material reader at 0x00923520 calls this at
// 0x0092363A after reading a W3dVertexMaterialStruct and optional name.
// Four original RGB-to-float conversions fill the pointed D3D material;
// shininess, opacity and the two material flags follow. Retail uses the
// material pointer at +8, flags at +0x0C, name at +0x1C and dirty byte +0x68.
// RET 4 at 0x00921E22 ends before INT3 padding at 0x00921E25.
// Keeping this pure parser visible also preserves ECX for the subsequent
// mapper-argument call in Load_W3D, as in the retail translation unit.
// Original bodies: GeneralsMD WW3D2/vertmaterial.cpp and w3d_util.cpp.
#include "wwstring.h"
#include "w3d_file.h"
#include "w3d_util.h"
#include "vector3.h"
#include "d3d8.h"
inline void W3dUtilityClass::Convert_Color(const W3dRGBStruct &rgb,Vector3 *set) { set->X=(float)rgb.R/255.0f; set->Y=(float)rgb.G/255.0f; set->Z=(float)rgb.B/255.0f; }
class ChunkLoadClass {
public:
    bool Open_Chunk();
    bool Close_Chunk();
    unsigned long Cur_Chunk_ID();
    unsigned long Cur_Chunk_Length();
    unsigned long Read(void *,unsigned long);
};
class VertexMaterialClass {
    unsigned char beforeMaterial[8];
    D3DMATERIAL8 *Material;
    unsigned int Flags;
    unsigned char beforeName[0x1c-0x10];
    StringClass Name;
    unsigned char beforeDirty[0x68-0x20];
    bool CRCDirty;
public:
    enum FlagsType { DEPTH_CUE=0,DEPTH_CUE_TO_ALPHA,COPY_SPECULAR_TO_DIFFUSE };
    void Set_Flag(FlagsType flag,bool onoff) { CRCDirty=true; if (onoff) Flags|=(1<<flag); else Flags&=~(1<<flag); }
    void Set_Ambient(const Vector3 &color) { CRCDirty=true; Material->Ambient.r=color.X; Material->Ambient.g=color.Y; Material->Ambient.b=color.Z; }
    void Set_Diffuse(const Vector3 &color) { CRCDirty=true; Material->Diffuse.r=color.X; Material->Diffuse.g=color.Y; Material->Diffuse.b=color.Z; }
    void Set_Specular(const Vector3 &color) { CRCDirty=true; Material->Specular.r=color.X; Material->Specular.g=color.Y; Material->Specular.b=color.Z; }
    void Set_Emissive(const Vector3 &color) { CRCDirty=true; Material->Emissive.r=color.X; Material->Emissive.g=color.Y; Material->Emissive.b=color.Z; }
    void Set_Shininess(float shin) { CRCDirty=true; Material->Power=shin; }
    void Set_Opacity(float o) { CRCDirty=true; Material->Diffuse.a=o; }
    void Set_Name(const char *name) { Name=name; }
    void Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &);
    void Parse_Mapping_Args(const W3dVertexMaterialStruct &,char *,char *);
    bool Load_W3D(ChunkLoadClass &);
};
void VertexMaterialClass::Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct & vmat)
{
	Vector3 tmp;
	W3dUtilityClass::Convert_Color(vmat.Ambient,&tmp);
	Set_Ambient(tmp);
	
	W3dUtilityClass::Convert_Color(vmat.Diffuse,&tmp);
	Set_Diffuse(tmp);
	
	W3dUtilityClass::Convert_Color(vmat.Specular,&tmp);
	Set_Specular(tmp);

	W3dUtilityClass::Convert_Color(vmat.Emissive,&tmp);
	Set_Emissive(tmp);

	Set_Shininess(vmat.Shininess);
	Set_Opacity(vmat.Opacity);

	if (vmat.Attributes & W3DVERTMAT_USE_DEPTH_CUE) {
		Set_Flag(VertexMaterialClass::DEPTH_CUE,true);
	}

	if (vmat.Attributes & W3DVERTMAT_COPY_SPECULAR_TO_DIFFUSE) {
		Set_Flag(VertexMaterialClass::COPY_SPECULAR_TO_DIFFUSE,true);
	}
}


