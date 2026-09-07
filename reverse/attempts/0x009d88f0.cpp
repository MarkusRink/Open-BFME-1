// ?beginBlock@XferSave@@UAEHPBD@Z
// partial score=0.9 date=2026-09-07
// scratch probe for the XferSave slot-5 beginBlock override

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

extern void __cdecl d_009d86e0();

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
	virtual int skip(int count, int flag);
};

// MSVC 7.1 has no callable __thiscall pointer extension in this build.  The
// observed callee consumes ECX as self and one stack dword; passing the name
// twice through __fastcall gives that exact register/stack ABI while keeping
// the generic dump symbol as the direct REL32 target.
typedef void (__fastcall *XferSaveStringFunction)(void *self, const char *name,
	const char *stackName);
class BfmePositionState
{
public:
	void initialize(int *value);
	int m_words[8];
};

class XferSave
{
public:
	virtual int beginBlock(const char *name);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionState m_positionState;
};

int XferSave::beginBlock(const char *name)
{
	if (m_stream == 0)
		return 0;

	int marker = 0x424c4f4b;
	if (m_stream->write(&marker, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_flag)
		reinterpret_cast<XferSaveStringFunction>(&d_009d86e0)(this, name, name);

	_ReadWriteBarrier();
	BfmeByteStream *stream = m_stream;
	int *position = reinterpret_cast<int *>(const_cast<char **>(&name));
	register int streamPosition = stream->skip(0, 1);
	if (streamPosition == -1)
	{
		XferException error;
		_ReadWriteBarrier();
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	*position = streamPosition;
	_ReadWriteBarrier();
	m_positionState.initialize(position);

	int zero = 0;
	if (m_stream->write(&zero, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	return 0;
}
