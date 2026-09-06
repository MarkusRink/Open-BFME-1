// ?fireCallback@@YAXPAURva008633B0Ctx@@PAURva008633B0Item@@@Z
struct Rva008633B0Ctx { char m_pad[0x40]; void* m_slots[1]; };
struct Rva008633B0Item { void* m_owner; int m_index; int m_count; void (__cdecl* m_func)(void*, int, Rva008633B0Ctx*, int, void*); void* m_param; };
void fireCallback(Rva008633B0Ctx* c, Rva008633B0Item* it)
{
	if (c->m_slots[it->m_index]) {
		it->m_func(it->m_owner, it->m_index, c, it->m_count, it->m_param);
		it->m_count++;
	}
}
