// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMachineName@IPEnumeration@@: Code/GameEngine/Source/GameNetwork/IPEnumeration.cpp
// BFME's implementation follows the released Zero Hour routine, returning
// the shared empty string when WinSock setup or hostname discovery fails.

typedef unsigned short WORD;

struct WSADATA
{
	WORD wVersion;
	unsigned char remainder[0x18e];
};

extern "C" __declspec(dllimport) int __stdcall WSAStartup(WORD version, WSADATA *data);
extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);
extern "C" __declspec(dllimport) int __stdcall gethostname(char *name, int length);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	AsciiString(const char *text);

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class IPEnumeration
{
public:
	AsciiString getMachineName(void);

private:
	void *m_IPlist;
	bool m_isWinsockInitialized;
};

AsciiString IPEnumeration::getMachineName(void)
{
	volatile int error = 0;

	if (!m_isWinsockInitialized)
	{
		WORD version = 0x0202;
		WSADATA data;
		if (WSAStartup(version, &data) != 0)
			return AsciiString::TheEmptyString;

		if ((unsigned char)data.wVersion != 2 ||
			(unsigned char)(data.wVersion >> 8) != 2)
		{
			WSACleanup();
			return AsciiString::TheEmptyString;
		}

		m_isWinsockInitialized = true;
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0)
		return AsciiString::TheEmptyString;

	return AsciiString(hostname);
}
