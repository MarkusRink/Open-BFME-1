// ?doDisplayCounter@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.55 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of DISPLAY_COUNTER.
// Retail RVA 0x002F9660 (235 bytes), ExecuteAction DISPLAY_COUNTER arm.

typedef bool Bool;

template <typename T>
struct StringHeader
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	T data[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void concat(const T *str, int len);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase();

	StringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const { return m_data ? m_data->data : ""; }
	int getLength() const { return m_data ? m_data->length : 0; }
	void concat(const char *str, int len)
	{
		((StringBase<char> *)this)->concat(str, len);
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class BFMEScriptEngineFlagLookup
{
	friend class ScriptActions;

	AsciiString canonicalFlagName(const AsciiString &name);
};

class ScriptEngine;

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

class InGameUI
{
public:
	void addNamedTimer(const AsciiString &timerName,
		const UnicodeString &text, Bool isCountdown);
};

extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;

#define TheScriptEngine (*(ScriptEngine **)0x012F076C)

class ScriptActions
{
protected:
	void doDisplayCounter(const AsciiString &, const AsciiString &);
};

// ?doDisplayCounter@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doDisplayCounter(const AsciiString &counterName,
	const AsciiString &counterText)
{
	AsciiString canonical =
		((BFMEScriptEngineFlagLookup *)TheScriptEngine)->canonicalFlagName(counterName);
	__declspec(align(4)) char slash = '/';
	canonical.concat(&slash, 1);
	canonical.concat(counterName.str(), counterName.getLength());
	UnicodeString translated = TheGameText->fetch(counterText);
	TheInGameUI->addNamedTimer(canonical, translated, false);
}
