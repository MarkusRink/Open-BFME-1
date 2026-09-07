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
// Original semantic body: meshmdlio.cpp; BFME field views are local here.
#include "dx8wrapper.h"
#include "w3d_file.h"

class MeshLoadContextClass
{
	unsigned char padding[0x8c];
public:
	int CurPass;
};

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
	bool Has_Color_Array(int array) { return ColorArray[array] != 0; }
	unsigned *Get_Color_Array(int array,bool create = true);
	void Set_DCG_Source(int pass,VertexMaterialClass::ColorSourceType source)
	{
		DCGSource[pass] = source;
	}
};

class MeshModelClass
{
	unsigned char geometry_padding[0x28];
	int VertexCount;
	unsigned char material_padding[0x9c - 0x2c];
public:
	MeshMatDescClass *CurMatDesc;

	unsigned *Get_Color_Array(int array,bool create = true)
	{
		return CurMatDesc->Get_Color_Array(array,create);
	}

protected:
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
