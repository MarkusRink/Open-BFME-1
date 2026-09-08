// ??0W3DStatusCircle@@QAE@XZ
// partial score=0.94 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0W3DStatusCircle@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DStatusCircle.cpp

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class RenderObjClass
{
public:
    RenderObjClass();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DStatusCircle.h
class W3DStatusCircle : public RenderObjClass
{
public:
    W3DStatusCircle();
};

// ??0W3DStatusCircle@@QAE@XZ
W3DStatusCircle::W3DStatusCircle()
{
	unsigned char *self = (unsigned char *)this;
	unsigned int negative_one = 0xbf800000;
	unsigned int zero = 0;

	*(unsigned int *)(self + 0xc8) = zero;
	*(unsigned int *)(self + 0xcc) = zero;
	*(unsigned int *)(self + 0xd8) = zero;
	_ReadWriteBarrier();
	*(unsigned int *)(self + 0x00) = 0x01121018;
	*(unsigned int *)(self + 0x08) = 0x01121010;
	*(unsigned int *)(self + 0xd0) = negative_one;
	*(unsigned int *)(self + 0xd4) = negative_one;
	*(unsigned int *)(self + 0xdc) = 0x0010441b;
	_ReadWriteBarrier();
	*(unsigned int *)(self + 0xe0) = zero;
	*(unsigned int *)(self + 0xe4) = zero;
	*(unsigned int *)(self + 0xe8) = zero;
}
