// ?d_006a5e60@@YAXXZ
// partial score=0.95 date=2026-09-07
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006A5E60 releases one audio item and frees its stream slot.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_0002669d();

class Rva006A5E60PlayingAudio
{
	public:
	char m_pad00[8];
	int m_stream;
	int m_type;
	char m_pad10[4];
	void *m_audioEvent;
};

struct Rva006A5E60StreamSlot
{
	char m_pad00[0x10];
	void *m_audio;
	char m_pad14[0x2c];
};

class Rva006A5E60MutexGuard
{
	void *m_mutex;
	unsigned char m_held;

public:
	Rva006A5E60MutexGuard(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	~Rva006A5E60MutexGuard()
	{
		if (m_held)
			ReleaseMutex(m_mutex);
	}
};

class ClientSubsystem
{
public:
#define RVA006A5E60_SLOT(n) virtual void slot##n();
	RVA006A5E60_SLOT(00) RVA006A5E60_SLOT(01) RVA006A5E60_SLOT(02) RVA006A5E60_SLOT(03)
	RVA006A5E60_SLOT(04) RVA006A5E60_SLOT(05) RVA006A5E60_SLOT(06) RVA006A5E60_SLOT(07)
	RVA006A5E60_SLOT(08) RVA006A5E60_SLOT(09) RVA006A5E60_SLOT(10) RVA006A5E60_SLOT(11)
	RVA006A5E60_SLOT(12) RVA006A5E60_SLOT(13) RVA006A5E60_SLOT(14) RVA006A5E60_SLOT(15)
	RVA006A5E60_SLOT(16) RVA006A5E60_SLOT(17) RVA006A5E60_SLOT(18) RVA006A5E60_SLOT(19)
	RVA006A5E60_SLOT(20) RVA006A5E60_SLOT(21) RVA006A5E60_SLOT(22) RVA006A5E60_SLOT(23)
	RVA006A5E60_SLOT(24) RVA006A5E60_SLOT(25) RVA006A5E60_SLOT(26) RVA006A5E60_SLOT(27)
	RVA006A5E60_SLOT(28) RVA006A5E60_SLOT(29) RVA006A5E60_SLOT(30) RVA006A5E60_SLOT(31)
	RVA006A5E60_SLOT(32) RVA006A5E60_SLOT(33) RVA006A5E60_SLOT(34) RVA006A5E60_SLOT(35)
	RVA006A5E60_SLOT(36) RVA006A5E60_SLOT(37) RVA006A5E60_SLOT(38) RVA006A5E60_SLOT(39)
	RVA006A5E60_SLOT(40) RVA006A5E60_SLOT(41) RVA006A5E60_SLOT(42) RVA006A5E60_SLOT(43)
	RVA006A5E60_SLOT(44) RVA006A5E60_SLOT(45) RVA006A5E60_SLOT(46) RVA006A5E60_SLOT(47)
	RVA006A5E60_SLOT(48) RVA006A5E60_SLOT(49) RVA006A5E60_SLOT(50) RVA006A5E60_SLOT(51)
	RVA006A5E60_SLOT(52) RVA006A5E60_SLOT(53) RVA006A5E60_SLOT(54) RVA006A5E60_SLOT(55)
	RVA006A5E60_SLOT(56) RVA006A5E60_SLOT(57) RVA006A5E60_SLOT(58) RVA006A5E60_SLOT(59)
	RVA006A5E60_SLOT(60) RVA006A5E60_SLOT(61) RVA006A5E60_SLOT(62) RVA006A5E60_SLOT(63)
	RVA006A5E60_SLOT(64) RVA006A5E60_SLOT(65) RVA006A5E60_SLOT(66) RVA006A5E60_SLOT(67)
	RVA006A5E60_SLOT(68) RVA006A5E60_SLOT(69) RVA006A5E60_SLOT(70)
#undef RVA006A5E60_SLOT
	virtual void notify(void *argument);

	char m_pad04[0x958];
	void *m_mutex;
	char m_pad960[0x1e4];
	Rva006A5E60StreamSlot *m_streamSlots;

	void releasePlayingAudio(Rva006A5E60PlayingAudio *argument);
};

#pragma comment(linker, "/alternatename:?releasePlayingAudio@ClientSubsystem@@QAEXPAVRva006A5E60PlayingAudio@@@Z=?j_0002669d@@YAXXZ")

// ?notify@ClientSubsystem@@UAEXPAX@Z
void ClientSubsystem::notify(void *argument)
{
	Rva006A5E60PlayingAudio *playing =
		(Rva006A5E60PlayingAudio *)argument;
	void *mutex = m_mutex;
	Rva006A5E60MutexGuard guard(mutex);

	releasePlayingAudio(playing);

	int *type = &playing->m_type;
	if (*type == 2)
	{
		int *stream = &playing->m_stream;
		m_streamSlots[*stream].m_audio = 0;
	}
}
