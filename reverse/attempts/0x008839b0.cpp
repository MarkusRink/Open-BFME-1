// ?trackFree@Rva008838F0Owner@@QAEXPAXI@Z
// partial score=0.95 date=2026-09-06
// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);
extern "C" __declspec(dllimport) void * __stdcall Rva01358DDC(int flags, void *value);
extern "C" __declspec(dllimport) void __stdcall Rva01358E44(void *value);

struct Rva008838F0Node
{
	Rva008838F0Node *m_next;
	char m_pad04[4];
	UnsignedInt m_key;
	char m_pad0c[8];
	void *m_value;
	char m_pad18[0x9c - 0x18];
	int m_slot;
};

class Rva008838F0Owner
{
public:
	void trackFree(void *value, UnsignedInt key);

private:
	char m_pad00[0x0c];
	Rva008838F0Node *m_buckets[0x2b7b];
	Rva008838F0Node *m_slots[0x7530];
	UnsignedInt m_slotIndex;
	Rva008838F0Node *m_current;
	unsigned char m_disabled;
	char m_pad282c1[7];
	void *m_lock;
};

void Rva008838F0Owner::trackFree(void *value, UnsignedInt key)
{
	if (m_disabled)
		return;

	if (m_lock)
		Rva01358D18Enter(m_lock);

	Rva008838F0Node **link = &m_buckets[key % 0x2b7b];
	while (*link && (*link)->m_key != key)
		link = &(*link)->m_next;

	Rva008838F0Node *node = *link;
	if (node && node->m_slot < 0)
	{
		Rva008838F0Node *replacement = m_slots[m_slotIndex];
		if (replacement)
		{
			Rva008838F0Node **replacementLink =
				&m_buckets[replacement->m_key % 0x2b7b];
			while (*replacementLink && *replacementLink != replacement)
				replacementLink = &(*replacementLink)->m_next;

			*replacementLink = replacement->m_next;
			replacement->m_next = m_current;
			if (replacement->m_value)
			{
				Rva01358E44(Rva01358DDC(0, replacement->m_value));
				replacement->m_value = 0;
			}

			m_current = replacement;
			node->m_slot = m_slotIndex;
			m_slots[m_slotIndex] = node;
			if (++m_slotIndex == 0x7530)
				m_slotIndex = 0;
		}
	}

	if (m_lock)
		Rva01358E74Leave(m_lock);
}
