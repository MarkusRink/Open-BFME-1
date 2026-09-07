// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter save entry points return a one-byte bool. Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"
#include "vector3.h"

#define FLOAT_TO_BYTE(fval) ((unsigned char)(max((fval), 0.0F) * 255.0F))
#define VECTOR3_TO_RGBA(vector3, rgba) \
	rgba.R = FLOAT_TO_BYTE((vector3).X); \
	rgba.G = FLOAT_TO_BYTE((vector3).Y); \
	rgba.B = FLOAT_TO_BYTE((vector3).Z)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
protected:
	virtual bool Save_Color_Keyframes(ChunkSaveClass &chunk_save);
	char Pad[0x244];
	Vector3 ColorStart;
	Vector3 ColorRand;
	unsigned int ColorNumKeyFrames;
	float *ColorKeyTimes;
	Vector3 *ColorValues;
};

bool ParticleEmitterDefClass::Save_Color_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	W3dEmitterColorKeyframeStruct info = { 0 };
	info.Time = 0;
	VECTOR3_TO_RGBA(ColorStart, info.Color);

	if (chunk_save.Write(&info, sizeof(info)) == sizeof(info))
	{
		int count = ColorNumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index++)
		{
			info.Time = ColorKeyTimes[index];
			VECTOR3_TO_RGBA(ColorValues[index], info.Color);
			success = (chunk_save.Write(&info, sizeof(info)) == sizeof(info));
		}

		ret_val = (success != false);
	}

	return ret_val;
}
