// ?resetElements@Rva007048C0Owner@@QAEXXZ
struct Rva007048C0Elem { char m_body[0xbc]; void reset(); };
struct Rva007048C0Owner {
	int m_0;
	Rva007048C0Elem* m_elems;
	int m_count;
	bool m_active;
	char m_pad[0x50 - 0xd];
	bool m_done;
	void resetElements();
};
void Rva007048C0Owner::resetElements()
{
	if (!m_active)
		return;
	for (int i = 0; i < m_count; ++i)
		m_elems[i].reset();
	m_done = true;
}
