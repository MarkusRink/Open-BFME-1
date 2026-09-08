// cl: /DNDEBUG /MD /EHsc
// Open-BFME-1: the VS2003 ATL GetStringTypeExWFake fallback for Windows 9x.

typedef unsigned short WCHAR;
typedef unsigned long DWORD;

extern "C"
{
	__declspec(dllimport) int __stdcall GetStringTypeA(DWORD locale, DWORD infoType,
		const char *src, int count, unsigned short *charType);
	__declspec(dllimport) int __stdcall WideCharToMultiByte(DWORD codePage, DWORD flags,
		const WCHAR *src, int count, char *dst, int dstCount,
		const char *defaultChar, int *usedDefaultChar);
}

typedef unsigned int (__stdcall *W3AtlAcpProc)(void);

namespace ATL
{
	extern W3AtlAcpProc g_pfnGetThreadACP;

	inline unsigned int _AtlGetConversionACP(void) throw()
	{
		return g_pfnGetThreadACP();
	}
}

class Rva0005CBD0Buffer
{
public:
	void grow(unsigned int size);
};

class Rva0005C6B0Holder
{
public:
	void release(void) throw();
};

namespace ATL
{
template <class T, int t_nFixedBytes = 128>
class CTempBuffer
{
public:
	CTempBuffer(void) throw() : m_cursor(0) {}

	~CTempBuffer(void) throw()
	{
		if (m_cursor != reinterpret_cast<T *>(m_buffer))
		{
			((Rva0005C6B0Holder *)this)->release();
		}
	}

	operator T *(void) const throw()
	{
		return m_cursor;
	}

	T *Allocate(unsigned int elements) throw(...)
	{
		return AllocateBytes(elements * sizeof(T));
	}

private:
	T *AllocateBytes(unsigned int bytes)
	{
		if (bytes > 0x80)
		{
			((Rva0005CBD0Buffer *)this)->grow(bytes);
		}
		else
		{
			m_cursor = reinterpret_cast<T *>(m_buffer);
		}

		return m_cursor;
	}

	T *m_cursor;
	unsigned char m_buffer[t_nFixedBytes];
};

int __stdcall GetStringTypeExWFake(DWORD locale, DWORD infoType,
	const WCHAR *src, int count, unsigned short *charType)
{
	int ansiCount;
	CTempBuffer<char> ansi;

	ansiCount = WideCharToMultiByte(_AtlGetConversionACP(), 0, src, count,
		0, 0, 0, 0);
	ansi.Allocate(ansiCount);
	WideCharToMultiByte(_AtlGetConversionACP(), 0, src, count, ansi, ansiCount, 0, 0);

	if (count == -1)
	{
		ansiCount = -1;
	}

	return GetStringTypeA(locale, infoType, ansi, ansiCount, charType);
}
}
