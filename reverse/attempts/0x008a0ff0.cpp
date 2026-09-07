// ??0Rva008A0FF0ValueStack@@QAE@XZ
// partial score=0.9 date=2026-09-06
struct Rva008A0FF0Value { virtual void s0(); virtual void release(); };
extern void* (__cdecl* Rva008C5D70Alloc)(unsigned int bytes);
struct Rva008A0FF0ValueStack {
	int m_0; int m_4; int m_8; int m_c; int m_10;
	int m_count;
	int m_capacity;
	Rva008A0FF0Value** m_values;
	Rva008A0FF0ValueStack();
	void releaseAll();
};
Rva008A0FF0ValueStack::Rva008A0FF0ValueStack()
	: m_0(0), m_4(0), m_8(0), m_c(0), m_10(0), m_count(0), m_capacity(6),
	m_values((Rva008A0FF0Value**)Rva008C5D70Alloc(6 * sizeof(Rva008A0FF0Value*)))
{
}
// ?releaseAll@Rva008A0FF0ValueStack@@QAEXXZ
void Rva008A0FF0ValueStack::releaseAll()
{
	for (int n = m_count; n > 0; --n) {
		m_values[m_count - 1]->release();
		m_count--;
	}
}
