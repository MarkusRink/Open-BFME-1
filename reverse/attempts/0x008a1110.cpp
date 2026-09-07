// ??0Rva008A1110Value@@QAE@H@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script value constructor (101 B): base sets the type bits
// and registers the value in the idle-hook pool when there is room (else
// clears the pooled bit) then the derived class stores its payload.
struct Rva008995E0Pool { int m_capacity; int m_count; struct Rva008995E0Base** m_items; };
extern Rva008995E0Pool* Rva008995E0IdleHook;
struct Rva008995E0Base {
	virtual ~Rva008995E0Base();
	unsigned int m_flags;
	Rva008995E0Base(unsigned int typeBits)
	{
		unsigned int flags = (m_flags & 0xF0008005) | typeBits;
		m_flags = flags;
		Rva008995E0Pool* pool = Rva008995E0IdleHook;
		int capacity = pool->m_capacity;
		int* count = &pool->m_count;
		if (*count < capacity) {
			pool->m_items[*count] = this;
			(*count)++;
		} else {
			m_flags = flags & 0xBFFFFFFF;
		}
	}
};
struct Rva008A1110Value : Rva008995E0Base {
	int m_value;
	Rva008A1110Value(int value);
};
Rva008A1110Value::Rva008A1110Value(int value)
	: Rva008995E0Base(0x40008007), m_value(value)
{
}
