// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// Retail 0x0078F950.  The caller's object is forwarded unchanged to the
// shared handler; the explicit one-byte local preserves the retail
// mov/test branch shape while the argument record selects one of the two
// already reconstructed 0x2F8-byte object factories.

class Rva007903F0VptrCtor;
class Rva00790480VptrCtor;

Rva007903F0VptrCtor *__stdcall Rva0078F100New(void *argument);
Rva00790480VptrCtor *__stdcall Rva0078F180New(void *argument);

typedef void *(__stdcall *Rva0078F950Factory)(void *argument);

struct Rva0078F950Record
{
	int m_head;
	signed char m_kind;
	char m_gap[19];
	Rva0078F950Factory m_factory;
};

class Rva0078F950Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

void Rva0078F950Owner::selectFactory(Rva0078F950Record *record)
{
	signed char kind = record->m_kind;

	if (kind & 0x80)
		record->m_factory = (Rva0078F950Factory)Rva0078F180New;
	else
		record->m_factory = (Rva0078F950Factory)Rva0078F100New;

	dispatchFactory(record);
}
