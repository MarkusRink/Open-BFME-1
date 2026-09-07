// ?notifyAfterApply@@YAXPAURva00234200Owner@@HH@Z
struct Rva0020AA00Target { void notify(int a, int b); };
struct Rva0020AA00Registry { Rva0020AA00Target* lookup(const int& id); };
extern Rva0020AA00Registry* Rva0020AA00TheRegistry;
struct Rva00234200Owner { char m_pad[0x2b0]; int* m_begin; int* m_end; };
void __cdecl Rva00234200Apply(Rva00234200Owner* owner, int a, int b);
void notifyAfterApply(Rva00234200Owner* owner, int a, int b)
{
	Rva00234200Apply(owner, a, b);
	for (int* it = owner->m_begin; it != owner->m_end; ++it) {
		Rva0020AA00Target* t = Rva0020AA00TheRegistry->lookup(*it);
		if (t)
			t->notify(a, b);
	}
}
