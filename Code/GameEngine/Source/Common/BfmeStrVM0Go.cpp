// cl: /O2 /Ob0
// ?bfmeGoVM0@BfmeStrVM0@@QAEXH@Z
// The three callers at 0x0040FD20, 0x0040FE40, and 0x0040FE60 name this
// method. The callback address 0x0044AB1F is the ILT for the matched movie
// thread routine at 0x0040ED00.

extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *, int, const char *);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(
	void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern void _bfme_debugRecordCallsite(int);

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18();
	virtual void Slot1C(); virtual void Slot20(); virtual void Slot24();
	virtual void Slot28(); virtual void Slot2C(); virtual void Slot30();
	virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08();
	virtual void Slot0C(); virtual void Slot10(); virtual void Slot14();
	virtual void Slot18(); virtual void Slot1C(); virtual void Slot20();
	virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44();
	virtual void Slot48(); virtual void Slot4C(); virtual void Slot50();
	virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *, void *);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;

class BfmeSubVM0
{
public:
	virtual int Slot00(); virtual int Slot04(); virtual int Slot08();
	virtual int Slot0C(); virtual int Slot10(); virtual int Slot14();
	virtual int Slot18(); virtual int Slot1C(); virtual int Slot20();
	virtual int Slot24(); virtual int Slot28(); virtual int Slot2C();
	virtual int Slot30(); virtual int Slot34(); virtual int Slot38();
	virtual int Slot3C(); virtual int Slot40();
};

class BfmeStrVM0
{
public:
	virtual int Slot00(); virtual int Slot01(); virtual int Slot02(); virtual int Slot03();
	virtual int Slot04(); virtual int Slot05(); virtual int Slot06(); virtual int Slot07();
	virtual int Slot08(); virtual int Slot09(); virtual int Slot10(); virtual int Slot11();
	virtual int Slot12(); virtual int Slot13(); virtual int Slot14(); virtual int Slot15();
	virtual int Slot16(); virtual int Slot17(); virtual int Slot18(); virtual int Slot19();
	virtual int Slot20(); virtual int Slot21(); virtual int Slot22(); virtual int Slot23();
	virtual int Slot24(); virtual int Slot25(); virtual int Slot26(); virtual int Slot27();
	virtual int Slot28(); virtual int Slot29(); virtual int Slot30(); virtual int Slot31();
	virtual int Slot32(); virtual int Slot33(); virtual int Slot34(); virtual int Slot35();
	virtual int Slot36(); virtual int Slot37(); virtual int Slot38(); virtual int Slot39();
	virtual int Slot40(); virtual int Slot41(); virtual int Slot42(); virtual int Slot43();
	virtual int Slot44(); virtual int Slot45(); virtual int Slot46(); virtual int Slot47();
	virtual int Slot48(); virtual int Slot49(); virtual int Slot50(); virtual int Slot51();
	virtual int Slot52(); virtual int Slot53(); virtual int Slot54(); virtual int Slot55();
	virtual int Slot56(); virtual int Slot57(); virtual int Slot58(); virtual int Slot59();
	virtual bool Slot60();

	void bfmeGoVM0(int);

	char m_pad30[0x30];
	BfmeSubVM0 *m_34;
	void *m_38;
	void *volatile m_3C;
	void *volatile m_40;
	char m_pad44[0x18];
	int volatile m_5C;
	char m_pad60[0xD8];
	int volatile m_138;
};

static long long *const g_bfmeClock = (long long *)0x012F1278;
static volatile long long *const g_bfmeClockResult = (volatile long long *)0x012F1290;
static double *const g_bfmeClockScale = (double *)0x010F0D58;
static double *const g_bfmeClockFactor = (double *)0x010EE5F0;
static double *const g_bfmeClockSeconds = (double *)0x012F12A8;

void BfmeStrVM0::bfmeGoVM0(int state)
{
	if (m_3C || m_40)
		return;

	if (state != 5)
	{
		int divisor = m_34->Slot40() - 2;
		long long quotient = *g_bfmeClock / divisor;
		// MSVC 7.1 schedules the quotient stores before fild in equivalent C++.
		// Keep this four-instruction x87 sequence to match the retail order.
		__asm fild qword ptr [g_bfmeClock]
		*g_bfmeClockResult = quotient;
		__asm fdivr qword ptr [g_bfmeClockScale]
		__asm fmul qword ptr [g_bfmeClockFactor]
		__asm fstp qword ptr [g_bfmeClockSeconds]
	}

	m_3C = CreateMutexA(0, 0, 0);
	m_40 = CreateMutexA(0, 1, 0);
	m_138 = 0;

	if (m_40 == 0)
		return;
	if (m_3C == 0)
		return;

	m_5C = state;
	void *thread = CreateThread(0, 0, (unsigned long (__stdcall *)(void *))0x0044AB1F, this, 0, 0);
	if (!SetThreadPriority(thread, 2))
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String((const char *)0x010F0D90)->Finish(1);
	}

	unsigned long result;
	do
	{
		result = WaitForSingleObject(m_3C, 1);
		if (result == 0)
			ReleaseMutex(m_3C);
	} while (result != 0x102);
}
