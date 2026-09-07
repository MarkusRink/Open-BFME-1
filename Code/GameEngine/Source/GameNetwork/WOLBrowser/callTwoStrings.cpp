// ?callTwoStrings@@YAXPBD0@Z
// Open-BFME7: 0x00959410 (133 B gap) forwards two C strings to the two-BSTR
// invoke wrapper on the WOL browser dispatch pointer when it is set; the
// smart pointer arrow raises E_POINTER through _com_issue_error.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

class BfmeThingVGP
{
public:
	void *m_bfme00;
	void *m_bfme04;
	int m_bfme08;
	int bfmeGoVGP() throw();
};

class BfmeBstrVGP
{
public:
	BfmeThingVGP *m_data;
	BfmeBstrVGP(const char *text) throw();
	// MSVC71 _bstr_t copies retain Data_t; a shallow owning copy is invalid.
	BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data)
	{ if (m_data) InterlockedIncrement((long volatile *)&m_data->m_bfme08); }
	~BfmeBstrVGP() throw()
	{
		if (m_data)
			m_data->bfmeGoVGP();
	}
};

class Rva00958D30
{
public:
	long invoke(BfmeBstrVGP first, BfmeBstrVGP second);
};
extern void __stdcall _com_issue_error(long error);
struct Rva00959410Ptr
{
	Rva00958D30 *m_p;
	Rva00958D30 *operator->() const
	{
		if (!m_p)
			_com_issue_error(0x80004003);
		return m_p;
	}
	operator bool() const { return m_p != 0; }
};
extern Rva00959410Ptr Rva00959410Dispatch;
void callTwoStrings(const char *first, const char *second)
{
	if (Rva00959410Dispatch)
		Rva00959410Dispatch->invoke(first, second);
}
