// ?_heap_abort@@YAXXZ
// partial score=0.9 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

extern "C" void *_ReturnAddress(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReturnAddress)
#pragma intrinsic(_ReadWriteBarrier)

class CrashStream
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual CrashStream &Write(const char *text);
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void Done(bool die);
};

class DebugInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void CaptureCallSite(unsigned address, int enabled);
	virtual void FlushCapture();
	virtual void slot25(); virtual void slot26();
	virtual CrashStream *BeginCrash(int channel, int level);
};

extern DebugInterface *TheDebug;

#pragma optimize("y", off)
void _heap_abort(void)
{
	unsigned volatile caller = (unsigned)_ReturnAddress();
	_ReadWriteBarrier();
	DebugInterface *debug = TheDebug;
	_ReadWriteBarrier();
	debug->CaptureCallSite(caller, 1);
	TheDebug->FlushCapture();
	TheDebug->BeginCrash(0, 0)->Write("Fatal heap error.").Done(true);
}
#pragma optimize("y", on)
