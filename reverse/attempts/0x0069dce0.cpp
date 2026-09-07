// ?erase@Rva0069DCE0Owner@@QAEPAURva0069DCE0Elem@@PAU2@@Z
// partial score=0.8 date=2026-09-06
// ?erase@Rva0069DCE0Owner@@QAEPAURva0069DCE0Elem@@PAU2@@Z
// Address-derived: vector-style erase(position) for 8-byte elements -- shift
// everything after position down by one slot, shrink the end pointer, return
// position.
struct Rva0069DCE0Elem
{
	int a;
	int b;
};

struct Rva0069DCE0Owner
{
	Rva0069DCE0Elem* m_begin;
	Rva0069DCE0Elem* m_end;

	Rva0069DCE0Elem* erase(Rva0069DCE0Elem* position);
};

Rva0069DCE0Elem* Rva0069DCE0Owner::erase(Rva0069DCE0Elem* position)
{
	Rva0069DCE0Elem* next = position + 1;
	if (next != m_end)
	{
		int count = (int)(m_end - next);
		if (count > 0)
		{
			char* p = (char*)position;
			do
			{
				*(int*)(p + 0) = *(int*)(p + 8);
				*(int*)(p + 4) = *(int*)(p + 0xc);
				p += 8;
			} while (--count);
		}
	}
	--m_end;
	return position;
}
