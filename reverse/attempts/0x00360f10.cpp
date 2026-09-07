// ?sumInactive@Rva00360F10Owner@@QAEHXZ
// partial score=0.8 date=2026-09-06
struct Rva00360F10Elem { char m_pad[0x34]; int m_value; bool m_active; char m_pad2[0xb4 - 0x39]; };
struct Rva00360F10Owner {
	char m_pad[0x30];
	Rva00360F10Elem* m_begin;
	Rva00360F10Elem* m_end;
	unsigned int size() const { return m_end - m_begin; }
	int sumInactive();
};
int Rva00360F10Owner::sumInactive()
{
	int sum = 0;
	for (unsigned int i = 0; i < size(); ++i) {
		if (!m_begin[i].m_active)
			sum += m_begin[i].m_value;
	}
	return sum;
}
