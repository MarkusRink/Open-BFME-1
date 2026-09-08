// ?bfmeResetSkyYV@@YAXXZ
// partial score=0.93 date=2026-09-08
// pins needed (CRLF):
//   ?bfmeSetScaleYV@WaterSkyBoxSettingsOwner@@QAEXPBM@Z,0x00005B0F
//   ?bfmeSetRotationYV@WaterSkyBoxSettingsOwner@@QAEXPBM@Z,0x0003F481
//   ?bfmeSetTextureYV@WaterSkyBoxSettingsOwner@@QAEXPBVBFMERetailAsciiString@@@Z,0x000435D1
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufYV;

private:
	void releaseBuffer();
};

struct BfmeVec3YV
{
	float x;
	float y;
	float z;
};

class BfmeSkyObjYV
{
public:
	virtual void bfmeV0() = 0;
	virtual void bfmeV1() = 0;
	virtual void bfmeV2() = 0;
	virtual void bfmeV3() = 0;
	virtual void bfmeV4() = 0;
	virtual void bfmeV5() = 0;
	virtual void bfmeV6() = 0;
	virtual void bfmeV7() = 0;
	virtual void bfmeV8() = 0;
	virtual void bfmeV9() = 0;
	virtual void bfmeV10() = 0;
	virtual void bfmeV11() = 0;
	virtual void bfmeV12() = 0;
	virtual void bfmeV13() = 0;
	virtual void bfmeV14() = 0;
	virtual void bfmeV15() = 0;
	virtual void bfmeV16() = 0;
	virtual void bfmeV17() = 0;
	virtual void bfmeV18() = 0;
	virtual void bfmeV19() = 0;
	virtual void bfmeV20() = 0;
	virtual void bfmeV21() = 0;
	virtual void bfmeSetColorYV(const BfmeVec3YV *c) = 0;
};

class WaterSkyBoxSettingsOwner
{
public:
	void bfmeSetScaleYV(const float *p);
	void bfmeSetRotationYV(const float *p);
	void bfmeSetTextureYV(const BFMERetailAsciiString *s);

	unsigned char m_bfmeHeadYV[0x250];
	BfmeSkyObjYV *m_bfme250YV;
};

extern WaterSkyBoxSettingsOwner *TheWaterRenderObj;

void bfmeResetSkyYV()
{
	BfmeSkyObjYV *o = TheWaterRenderObj->m_bfme250YV;

	if (o != 0)
	{
		BfmeVec3YV zero;

		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;

		o->bfmeSetColorYV(&zero);
	}

	{
		float v = 1.0f;

		TheWaterRenderObj->bfmeSetScaleYV(&v);

		v = 0.0f;
		TheWaterRenderObj->bfmeSetRotationYV(&v);
	}

	{
		BFMERetailAsciiString name("DefaultSky");

		TheWaterRenderObj->bfmeSetTextureYV(&name);
	}
}
