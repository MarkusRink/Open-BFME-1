// ?projectItems@Rva003C9AB0Owner@@QAEXHPAURva003C9AB0Projector@@@Z
// partial score=0.9 date=2026-09-06
struct Rva003C9AB0Point { float x; float y; };
struct Rva003C9AB0Projector { void project(void* source, Rva003C9AB0Point* out); };
struct Rva003C9AB0Target { char m_pad[0x10]; float x; float y; };
struct Rva003C9AB0Item { int m_0; char m_source[0xe8]; Rva003C9AB0Target* m_target; };
struct Rva003C9AB0Owner {
	char m_pad[0x30];
	Rva003C9AB0Item** m_begin;
	Rva003C9AB0Item** m_end;
	unsigned int size() const { return m_end - m_begin; }
	void projectItems(int unused, Rva003C9AB0Projector* projector);
};
void Rva003C9AB0Owner::projectItems(int unused, Rva003C9AB0Projector* projector)
{
	for (unsigned int i = 0; i < size(); ++i) {
		Rva003C9AB0Point p;
		projector->project(m_begin[i]->m_source, &p);
		Rva003C9AB0Target* t = m_begin[i]->m_target;
		t->x = p.x;
		t->y = p.y;
	}
}
