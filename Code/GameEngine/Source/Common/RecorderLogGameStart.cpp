// cl: /ICode/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc

#include "string_base.h"

typedef long time_t;

extern "C" __declspec(dllimport) time_t __cdecl time(time_t *value);
extern "C" __declspec(dllimport) long __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size,
	unsigned int count, void *stream);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
	AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
	~AsciiString() { base()->releaseBuffer(); }

private:
	StringBase<char> *base() { return (StringBase<char> *)this; }
	const StringBase<char> *base() const { return (const StringBase<char> *)this; }

	StringBase<char>::Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass {
	unsigned char m_prefix[0x0c];
	void *m_file;

protected:
	void logGameStart(AsciiString options);
};

static time_t startTime;

void RecorderClass::logGameStart(AsciiString options)
{
	if (!m_file)
		return;

	time(&startTime);
	unsigned int fileSize = ftell(m_file);
	if (!fseek(m_file, 8, 0))
		fwrite(&startTime, sizeof(time_t), 1, m_file);
	fseek(m_file, fileSize, 0);
}
