// ?Init_Alternate@MeshMatDescClass@@QAEXAAV1@0@Z
// partial score=0.992424 date=2026-09-07
// cl: /ICode/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/meshmatdesc.cpp                        $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 1/18/02 8:03p                                               $*
 *                                                                                             *
 *                    $Revision:: 28                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Retail disagrees with the WW3D2-local vertmaterial.h about VertexMaterialClass
// on two points that Post_Load_Process is the first body to feel:
//   - it is 0x6C, not 0x70. Set_Ambient_Color_Source (0x00921160) writes
//     [ecx+0x10], so the local header's extra `_bfme_vmat_v0` dword ahead of
//     MaterialOld is not there; the reference copy, which omits it, is right.
//   - it has no pooled operator new. The allocation here is a bare
//     `push 0x6c; call ??2@YAPAXI@Z`, not the getClassMemoryPool() +
//     allocateFromW3DMemPool pair W3DMPO_GLUE generates.
// The local header is shared by 17 other TUs, so take the reference layout by
// angle-bracket include (its VERTMATERIAL_H guard then swallows the local copy
// meshmatdesc.h pulls in) and drop the glue for the length of that include only.
#include "always.h"
#pragma push_macro("W3DMPO_GLUE")
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include <vertmaterial.h>
#pragma pop_macro("W3DMPO_GLUE")

#include "meshmatdesc.h"
#include "texture.h"
#include "vertmaterial.h"
#include "realcrc.h"
#include	"dx8wrapper.h"
#include "dx8caps.h"
#include "meshmdl.h"


/**************************************************************************************************
**
**
** MatBufferClass Implementation
**
**
**************************************************************************************************/
void MeshMatDescClass::Init_Alternate(MeshMatDescClass & default_materials,MeshMatDescClass & alternate_materials)
{
	// just copy the counts
	PassCount = default_materials.PassCount;
	VertexCount = default_materials.VertexCount;
	PolyCount = default_materials.PolyCount;

	// Color arrays
	for (int array=0; array<MAX_COLOR_ARRAYS; array++) {
		if (alternate_materials.ColorArray[array] != NULL) {
			REF_PTR_SET(ColorArray[array],alternate_materials.ColorArray[array]);
		} else {
			REF_PTR_SET(ColorArray[array],default_materials.ColorArray[array]);
		}
	}

	// Copy the uv-arrays from the alternate materials to start.  Needed uv arrays from
	// the default material set will be brought over as encountered below
	for (int i=0; i<alternate_materials.Get_UV_Array_Count(); i++) {
		REF_PTR_SET(UV[i],alternate_materials.UV[i]);
	}

	// add-ref the arrays in default_materials except when the same array is present in alternate_materials
	for (int pass = 0; pass < MAX_PASSES; pass++) {
		for (int stage = 0; stage < MAX_TEX_STAGES; stage++) {

			// UV Coorindate arrays, Each UVSource[pass][stage] which is -1 in the alternate_materials
			// but not -1 in the default_materials causes us to copy over a uv array from the default_materials
			// and set its index into our UVSource array.
			if (alternate_materials.UVSource[pass][stage] == -1) {
				if (default_materials.UVSource[pass][stage] != -1) {

					// Look up the uv array in default_materials that we need to bring over.
					int default_uv_source = default_materials.UVSource[pass][stage];
					UVBufferClass * uvarray = default_materials.UV[default_uv_source];
					int found_index = -1;

					// Check if we already have it.
					for (int i=0; i<Get_UV_Array_Count(); i++) {
						if (uvarray->Get_CRC() == UV[i]->Get_CRC()) {
							found_index = i;
							break;
						}
					}

					// If we already have it, just set the source index.  Otherwise add-ref it
					// into a new slot in our uv array and set that index.
					if (found_index != -1) {
						UVSource[pass][stage] = found_index;
					} else {
						int new_index = Get_UV_Array_Count();
						REF_PTR_SET(UV[new_index],default_materials.UV[default_uv_source]);
						UVSource[pass][stage] = new_index;
					}
				}
			} else {
				UVSource[pass][stage] = alternate_materials.UVSource[pass][stage];
			}

			// Texture pointer(s):  If alternate_materials has either a single texture or an array of textures,
			// then add-ref only the texture data it contains.  Otherwise, add-ref the data in default_materials.
			if ((alternate_materials.Texture[pass][stage] != NULL) || (alternate_materials.TextureArray[pass][stage])) {
				REF_PTR_SET(Texture[pass][stage] , alternate_materials.Texture[pass][stage]);
				REF_PTR_SET(TextureArray[pass][stage] , alternate_materials.TextureArray[pass][stage]);
			} else {
				REF_PTR_SET(Texture[pass][stage] , default_materials.Texture[pass][stage]);
				REF_PTR_SET(TextureArray[pass][stage] , default_materials.TextureArray[pass][stage]);
			}
		}

		// Vertex color configuration
		if (alternate_materials.DCGSource[pass] == VertexMaterialClass::MATERIAL) {
			DCGSource[pass] = default_materials.DCGSource[pass];
		} else {
			DCGSource[pass] = alternate_materials.DCGSource[pass];
		}

		// Shaders, currently I can't tell if the alternate data has a shader...  Can't override the shader for now.
		Shader[pass] = default_materials.Shader[pass];
		REF_PTR_SET(ShaderArray[pass],default_materials.ShaderArray[pass]);

		// Vertex Materials.  If alternate_materials has either a single or array of materials, then copy them
		if ((alternate_materials.Material[pass] != NULL) || (alternate_materials.MaterialArray[pass] != NULL)) {
			REF_PTR_SET(Material[pass],alternate_materials.Material[pass]);
			REF_PTR_SET(MaterialArray[pass],alternate_materials.MaterialArray[pass]);
		} else {
			// Dont share vertex materials! (because the UVSources can be different!)
			if (default_materials.Material[pass]) {
				Material[pass] = NEW_REF(VertexMaterialClass,(*(default_materials.Material[pass])));
			} else {
				if (default_materials.MaterialArray[pass]) {
					WWDEBUG_SAY(("Unimplemented case: mesh has more than one default vertex material but no alternate vertex materials have been defined.\r\n"));
				}
				Material[pass] = NULL;
			}
		}
	}
}

