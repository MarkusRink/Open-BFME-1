// ?slot70@Rva006AEA10AudioManager@@QAE?AVAudioEventInfoRef@@ABVAsciiString@@@Z
// partial score=0.99 date=2026-09-07
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x006AEA10: lock the BFME audio-event table and return its retained
// event-info pointer for one string key.  The vtable slot at +0x118 and the
// neighboring AudioManager methods identify the owner; the method name remains
// address-derived because the BFME-only slot has no Zero Hour declaration.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef long Long;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AsciiString
{
public:
	void *m_data;
};

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

bool operator==(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend);

class Rva006AEA10MutexGuard
{
public:
	Rva006AEA10MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006AEA10MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_info(0) {}
	AudioEventInfoRef(AudioEventInfo *info) : m_info(info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	AudioEventInfo *m_info;
};

enum Rva006A7AD0Mapped
{
	Rva006A7AD0MappedZero = 0
};

typedef _STL::hash_map<AsciiString, Rva006A7AD0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva006A7AD0Map;

struct Rva006AEA10Node
{
	Rva006AEA10Node *m_next;
	AsciiString m_key;
	AudioEventInfo *m_info;
};

class Rva006AEA10AudioManager
{
public:
	AudioEventInfoRef slot70(const AsciiString &eventName);

private:
	char m_pad70[0x70];
	Rva006A7AD0Map m_events;
	char m_pad95c[0x95c - 0x70 - sizeof(Rva006A7AD0Map)];
	void *m_mutex;
};

AudioEventInfoRef Rva006AEA10AudioManager::slot70(const AsciiString &eventName)
{
	volatile Long constructionState = 0;
	_ReadWriteBarrier();
	Rva006AEA10MutexGuard guard(m_mutex);
	Rva006A7AD0Map::const_iterator it = m_events.find(eventName);
	Rva006AEA10Node *node = *(Rva006AEA10Node **)&it;
	if (node == 0)
		return AudioEventInfoRef();
	return AudioEventInfoRef(node->m_info);
}
