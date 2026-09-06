// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

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

class _bstr_t
{
public:
	BfmeThingVGP *m_data;
	_bstr_t(const char *value);
	_bstr_t(const _bstr_t &other) throw() : m_data(other.m_data) {}
	~_bstr_t() throw()
	{
		if (m_data)
			m_data->bfmeGoVGP();
	}
};

class Rva00958E30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0C;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1C;
		void *slot20;
		void *slot24;
		void *slot28;
		void *slot2C;
		void *slot30;
		long (__stdcall *slot34)(Rva00958E30 *, void *, void *);
	};

	__declspec(noinline) long invoke(_bstr_t arg)
	{
		long value = 0;
		BfmeThingVGP *data = arg.m_data;
		void *text = data ? data->m_bfme00 : 0;
		long result = vtable->slot34(this, text, &value);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return value;
	}

	Vtable *vtable;
};

// forceRva00958E30 is an emission host for the inline COM wrapper.
__declspec(noinline) long forceRva00958E30(Rva00958E30 *self, _bstr_t arg)
{
	return self->invoke(arg);
}
