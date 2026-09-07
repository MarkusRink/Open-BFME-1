// ?registerAll@Rva003A4AD0Owner@@QAEXXZ
// partial score=0.9 date=2026-09-06
struct Rva003A4AD0Item { char m_pad[0xa4]; int m_key; };
struct Rva003A4AD0Game { char m_pad[0x168]; char m_slot[1]; void registerKey(int key, int flag); };
extern Rva003A4AD0Game* g_bfmeGameCW;
void __stdcall Rva003A4AD0Reset(void* slot, int a, int b);
struct Rva003A4AD0Owner {
	char m_pad[0x48];
	Rva003A4AD0Item** m_begin;
	Rva003A4AD0Item** m_end;
	unsigned int size() const { return m_end - m_begin; }
	void registerAll();
};
void Rva003A4AD0Owner::registerAll()
{
	Rva003A4AD0Reset(g_bfmeGameCW->m_slot, 0, 0);
	for (unsigned int i = 0; i < size(); ++i)
		g_bfmeGameCW->registerKey(m_begin[i]->m_key, 0);
}
