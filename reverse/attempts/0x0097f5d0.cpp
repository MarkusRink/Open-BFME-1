// ?bfmeMakeCGE@@YAHPAVBfmeSubCGE@@@Z
// partial score=0.25 date=2026-09-07
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
#include "part_emt.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "assetmgr.h"
#include "part_ldr.h"
#include "w3derr.h"
#include "chunkio.h"
#include "scene.h"
#include "texture.h"
#include "wwprofile.h"
#include <limits.h>
#include "gcd_lcm.h"
#include "texture.h"
#include "part_ldr.h"

// The conversion caller passes the emitter-definition object through its
// BfmeSubCGE ABI name.  The retail virtual calls and field offsets are the
// ParticleEmitterDefClass layout, so keep the view local to this helper.
class BfmeSubCGE : public ParticleEmitterDefClass
{
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEEmitterTexture
{
};

class BFMEWaterTrackTextureHandle
{
public:
	BFMEEmitterTexture *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mip_count, int format);

static inline void BFMEAssignWaterTrackTexture(
	BFMEEmitterTexture *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

int bfmeMakeCGE(BfmeSubCGE *sub)
{
	const ParticleEmitterDefClass &definition = *sub;
	ParticleEmitterClass *pemitter = NULL;
	const char *ptexture_filename = definition.Get_Texture_Filename();
	BFMEEmitterTexture *ptexture = NULL;
	if (ptexture_filename && ptexture_filename[0]) {
		BFMEAssignWaterTrackTexture(
			ptexture,
			BFMEGetWaterTrackTexture((char *)ptexture_filename, 0, 0));
	}

	ShaderClass shader;
	definition.Get_Shader(shader);

	ParticlePropertyStruct<Vector3> color_keys;
	ParticlePropertyStruct<float> opacity_keys;
	ParticlePropertyStruct<float> size_keys;
	ParticlePropertyStruct<float> rotation_keys;
	ParticlePropertyStruct<float> frame_keys;
	ParticlePropertyStruct<float> blur_time_keys;

	definition.Get_Color_Keyframes(color_keys);
	definition.Get_Opacity_Keyframes(opacity_keys);
	definition.Get_Size_Keyframes(size_keys);
	definition.Get_Rotation_Keyframes(rotation_keys);
	definition.Get_Frame_Keyframes(frame_keys);
	definition.Get_Blur_Time_Keyframes(blur_time_keys);

	pemitter = NEW_REF(ParticleEmitterClass, (
		definition.Get_Emission_Rate(),
		definition.Get_Burst_Size(),
		definition.Get_Creation_Volume(),
		definition.Get_Velocity(),
		definition.Get_Velocity_Random(),
		definition.Get_Outward_Vel(),
		definition.Get_Vel_Inherit(),
		color_keys,
		opacity_keys,
		size_keys,
		rotation_keys,
		definition.Get_Initial_Orientation_Random(),
		frame_keys,
		blur_time_keys,
		definition.Get_Acceleration(),
		definition.Get_Lifetime(),
		definition.Get_Future_Start_Time(),
		(TextureClass *)ptexture,
		shader,
		definition.Get_Max_Emissions(),
		0,
		false,
		definition.Get_Render_Mode(),
		definition.Get_Frame_Mode(),
		definition.Get_Line_Properties()));

	if (color_keys.KeyTimes != NULL) delete [] color_keys.KeyTimes;
	if (color_keys.Values != NULL) delete [] color_keys.Values;
	if (opacity_keys.KeyTimes != NULL) delete [] opacity_keys.KeyTimes;
	if (opacity_keys.Values != NULL) delete [] opacity_keys.Values;
	if (size_keys.KeyTimes != NULL) delete [] size_keys.KeyTimes;
	if (size_keys.Values != NULL) delete [] size_keys.Values;
	if (rotation_keys.KeyTimes != NULL) delete [] rotation_keys.KeyTimes;
	if (rotation_keys.Values != NULL) delete [] rotation_keys.Values;
	if (frame_keys.KeyTimes != NULL) delete [] frame_keys.KeyTimes;
	if (frame_keys.Values != NULL) delete [] frame_keys.Values;
	if (blur_time_keys.KeyTimes != NULL) delete [] blur_time_keys.KeyTimes;
	if (blur_time_keys.Values != NULL) delete [] blur_time_keys.Values;

	pemitter->Set_Name(definition.Get_Name());

	if (ptexture) {
		((BFMEWaterTrackTexture *)ptexture)->Release_Ref();
		ptexture = 0;
	}

	return (int)pemitter;
}
