// ?broadcast@Rva0088A1F0Owner@@QAEXXZ
// partial score=0.82 date=2026-09-06
// ?broadcast@Rva0088A1F0Owner@@QAEXXZ
// Address-derived: walk the singly-linked list at this->m_c, and for each
// node whose interface pointer (m_10) is non-null, call vtable slot 3 with
// (this->m_9cf4, &this->m_9cf8, 0) then vtable slot 4 with no args.
struct Rva0088A1F0Iface
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void call3(void* a1, void* a2, void* a3);
	virtual void call4();
};

struct Rva0088A1F0Node
{
	Rva0088A1F0Node* m_next;
	unsigned char m_pad4[0x10 - 4];
	Rva0088A1F0Iface* m_10;
};

struct Rva0088A1F0Owner
{
	unsigned char m_pad0[0xc];
	Rva0088A1F0Node* m_c;
	unsigned char m_pad10[0x9cf4 - 0x10];
	void* m_9cf4;
	unsigned char m_9cf8[4];

	void broadcast();
};

void Rva0088A1F0Owner::broadcast()
{
	for (Rva0088A1F0Node* n = m_c; n; n = n->m_next)
	{
		Rva0088A1F0Iface* iface = n->m_10;
		if (iface)
		{
			iface->call3(m_9cf4, m_9cf8, 0);
			n->m_10->call4();
		}
	}
}
