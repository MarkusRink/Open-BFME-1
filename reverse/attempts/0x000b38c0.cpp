// ?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z
// partial score=0.96 date=2026-09-07
// Retail 0x000B38C0, 140B size-exact. Named by the byte-true call in
// Code/GameEngine/Source/Common/INI/ini.cpp.
// 135/140 bytes match; all 8 reloc sites align. Structure proven: compare
// (AsciiString::compare via thunk 0x000220C5) gates an inlined
// InterlockedDecrement + scalar-deleting-dtor release with null, then
// UnicodeString::set (0x00C87C90) INSIDE the if (je skips it when equal),
// then releaseBuffer dtor (0x00C87940) for the by-value arg. m_eventName is
// at +0x14 (class must NOT redeclare the compiler vptr: no explicit m_vtable
// member). Landed as dedicated TU Code/GameEngine/Source/Common/Audio/
// AudioEventRTSSetEventName.cpp (home TU AudioEventRTS.cpp keeps its
// present-unmatched body; its inline string ops cannot emit the out-of-line
// compare/set calls).
// Blocker: &m_eventName lands in EBX, retail EBP (push/lea/push-arg/mov-ecx/
// pop = 5 bytes). Stable across member-access, pointer-local,
// reference-local formulations. Pins needed once it flips: compare ->
// 0x000220C5 thunk, StringBase::set -> 0x00C87C90, ~StringBase ->
// 0x00C87940 (run decode_calls on the TU).
// cl: /DNDEBUG /MD /EHsc
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void set(const StringBase<T> &other);

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int compare(const AsciiString &other) const;
};

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class CountedPtr
{
public:
	void operator=(int nullValue)
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = (AudioEventInfo *)nullValue;
		}
	}

	AudioEventInfo *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	void setEventName(AsciiString name);

private:
	AsciiString m_filenameToLoad;	// +0x04
	CountedPtr m_eventInfo;		// +0x08
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;	// +0x14
};

// ?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z
void AudioEventRTS::setEventName(AsciiString name)
{
	AsciiString *eventName = &m_eventName;
	if (name.compare(*eventName) != 0)
	{
		m_eventInfo = 0;
		eventName->set(name);
	}
}
