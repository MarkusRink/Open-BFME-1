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
// BFME MeshModelClass::read_vertex_colors, RVA 0x0096D140, 373 bytes.
// read_chunks maps W3D_CHUNK_VERTEX_COLORS (0x0D) through selector byte
// 0x0097013F and table slot 0x0097011C to the arm at 0x0097001C;
// its call at 0x00970020 reaches this body. The dispatcher consumes AL
// and tests it against 1, matching the Boolean ABI of the sibling loaders.
// The final RET 8 at 0x0096D2B2 ends immediately before INT3 padding.
// read_dcg: RVA 0x0096D500, complete 773-byte body. Chunk 0x3B selects
// arm 0x0096FBB5; the call at 0x0096FBB9 reaches this body. It returns
// a Boolean in AL and ends with RET 8 at 0x0096D802, then INT3 padding.
// The matched MeshModel constructor establishes DefMatDesc at +0x94,
// AlternateMatDesc at +0x98, and CurMatDesc at +0x9C. Legacy vertex colors
// use CurMatDesc; the DCG reader starts with DefMatDesc.
// Original semantic bodies: meshmdlio.cpp; BFME field views are local here.
#include "dx8wrapper.h"
#include "w3d_file.h"

class MeshMatDescClass
{
	int PassCount;
	int VertexCount;
	int PolyCount;
	void *UV[8];
	int UVSource[4][2];
	void *ColorArray[2];
	VertexMaterialClass::ColorSourceType DCGSource[4];
	VertexMaterialClass::ColorSourceType DIGSource[4];

public:
	VertexMaterialClass::ColorSourceType Get_DCG_Source(int pass) { return DCGSource[pass]; }
	bool Has_Color_Array(int array) { return ColorArray[array] != 0; }
	unsigned *Get_Color_Array(int array,bool create = true);
	void Set_DCG_Source(int pass,VertexMaterialClass::ColorSourceType source)
	{
		DCGSource[pass] = source;
	}
};

class MeshLoadContextClass
{
	unsigned char prelit_padding[0x88];
public:
	unsigned long PrelitChunkID;
	int CurPass;
	unsigned char alternate_padding[0x10c - 0x90];
	MeshMatDescClass AlternateMatDesc;
};

class MeshModelClass
{
	unsigned char geometry_padding[0x28];
	int VertexCount;
	unsigned char material_padding[0x94 - 0x2c];
public:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;

	unsigned *Get_Color_Array(int array,bool create = true)
	{
		return CurMatDesc->Get_Color_Array(array,create);
	}

protected:
	bool read_dcg(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_vertex_colors(ChunkLoadClass &cload,MeshLoadContextClass *context);
};

bool MeshModelClass::read_vertex_colors(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	if (CurMatDesc->Has_Color_Array(0) == 0) {
		W3dRGBStruct color;
		unsigned *dcg = Get_Color_Array(0,true);
		for (int i=0; i<VertexCount; i++) {
			if (cload.Read(&color,sizeof(W3dRGBStruct)) != sizeof(W3dRGBStruct)) {
				return false;
			}

			Vector4 col;
			col.Set((float)color.R / 255.0f,(float)color.G / 255.0f,(float)color.B / 255.0f,1.0f);
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}
	CurMatDesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}

bool MeshModelClass::read_dcg(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	MeshMatDescClass *matdesc = DefMatDesc;
	if (DefMatDesc->Get_DCG_Source(context->CurPass) != VertexMaterialClass::MATERIAL) {
		matdesc = &context->AlternateMatDesc;
	}

	if (matdesc->Has_Color_Array(0) == 0) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col;
			col.Set((float)color.R / 255.0f,(float)color.G / 255.0f,
				(float)color.B / 255.0f,(float)color.A / 255.0f);
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	} else if (context->PrelitChunkID == W3D_CHUNK_PRELIT_VERTEX) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col = DX8Wrapper::Convert_Color(dcg[i]);
			col.W = (float)color.A / 255.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}
