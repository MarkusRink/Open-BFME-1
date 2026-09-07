// ?notifyFlagged@Rva003BD960Owner@@QAEXH@Z
// partial score=0.9 date=2026-09-06
struct Rva003BD960Item { char m_pad[0x1e]; bool m_flag; void notify(int value); };
struct Rva003BD960Owner {
	char m_pad[0xc];
	Rva003BD960Item** m_begin;
	Rva003BD960Item** m_end;
	unsigned int size() const { return m_end - m_begin; }
	void notifyFlagged(int value);
};
void Rva003BD960Owner::notifyFlagged(int value)
{
	for (unsigned int i = 0; i < size(); ++i) {
		if (m_begin[i]->m_flag)
			m_begin[i]->notify(value);
	}
}
