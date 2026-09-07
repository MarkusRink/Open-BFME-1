// ?framesUntilNext@Rva00256FD0Owner@@QAEHXZ
// partial score=0.7 date=2026-09-06
struct Rva00256FD0Logic { char m_pad[0x3c]; unsigned int m_frame; };
extern Rva00256FD0Logic* TheBfmeGameLogic;
struct Rva00256FD0Link { Rva00256FD0Link* m_next; Rva00256FD0Link* m_prev; int m_id; unsigned int m_frame; };
struct Rva00256FD0Owner {
	char m_pad[0x20];
	Rva00256FD0Link* m_head;
	int framesUntilNext();
};
int Rva00256FD0Owner::framesUntilNext()
{
	unsigned int frame = TheBfmeGameLogic->m_frame;
	unsigned int best = 0;
	for (Rva00256FD0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		int id = n->m_id;
		unsigned int f = n->m_frame;
		if (f < best || best == 0)
			best = f;
	}
	if (best == 0)
		return 0x3fffffff;
	int delta = best - frame;
	if (delta > 0)
		return delta;
	return 1;
}
