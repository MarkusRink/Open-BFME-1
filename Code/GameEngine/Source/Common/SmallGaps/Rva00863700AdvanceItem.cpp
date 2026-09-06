// ?advanceItem@@YAHPAURva00863700Ctx@@PAURva00863700Item@@@Z
struct Rva00863700Ctx { char m_pad[0x40]; void* m_slots[1]; };
struct Rva00863700Item { int m_count; int m_cur; int m_index; };
int advanceItem(Rva00863700Ctx* c, Rva00863700Item* it)
{
	void* t = c->m_slots[it->m_index];
	if (t) {
		if (it->m_count == it->m_cur)
			return 0;
		it->m_cur++;
	}
	return 1;
}
