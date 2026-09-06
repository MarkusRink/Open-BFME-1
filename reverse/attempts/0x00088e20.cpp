// ??0BfmeScopeCS@@QAE@PAX0PAURva002E5FF0Str@@@Z (identity unknown)
// partial score=0.75 date=2026-09-07
// 144 bytes against retail's 146, structure essentially recovered: the null
// data parameter falls back to the global Rva01336E50Str, a string temporary
// is built from the literal at 0x0107C7C4, the base half of the scope object
// (vfptr = _bfmeVftVE, inner pointer) is filled in, a four-argument stdcall
// registrar is called with a function pointer (thunk 0x0001579E) and `this`,
// its result and the third parameter are stored, and finally the derived
// vftable 0x0107C804 is written.
// Blocker: retail uses SEH prologue Form A (`push -1` first) plus a `push ecx`
// frame slot for the string; a named local gives Form B here and a
// const-reference temporary gives Form B as well and loses six more bytes.
// That contradicts the direction recorded in seh-prologue-has-two-forms, so
// the form is evidently not decided by named-vs-temporary alone.
// Five siblings share this size (0x00088F50, 0x00450460, 0x0074A2C0,
// 0x0074A3B0, 0x0074A590) so cracking the prologue form is worth six bodies.
extern "C" int _bfmeVftVE[];
extern "C" int _bfmeVftCS[];
extern "C" char _bfmeLitCS[];

struct Rva002E5FF0Str
{
	int m_bfmeDataCS;
};

extern Rva002E5FF0Str Rva01336E50Str;

class BfmeStrCS
{
public:
	BfmeStrCS(const char *text);
	~BfmeStrCS();

	int m_bfmeTextCS;
};

void __cdecl bfmeCallbackCS(void);

void * __stdcall bfmeRegisterCS(BfmeStrCS *name, Rva002E5FF0Str *data, void *fn,
	void *owner);

class BfmeScopeCS
{
public:
	BfmeScopeCS(void *extra, void *inner, Rva002E5FF0Str *data);

	int *m_bfmeVfCS;
	void *m_bfmeInnerCS;
	void *m_bfmeArgCS;
	void *m_bfmeExtraCS;
	int m_bfmePadCS;
};

BfmeScopeCS::BfmeScopeCS(void *extra, void *inner, Rva002E5FF0Str *data)
{
	if (data == 0)
		data = &Rva01336E50Str;

	BfmeStrCS name(_bfmeLitCS);

	m_bfmeVfCS = _bfmeVftVE;
	m_bfmeInnerCS = inner;
	m_bfmeArgCS = bfmeRegisterCS(&name, data, (void *)&bfmeCallbackCS, this);
	m_bfmeExtraCS = extra;
	m_bfmeVfCS = _bfmeVftCS;
}
