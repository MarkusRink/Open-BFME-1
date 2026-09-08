// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// Retail 0x0078F950.  The caller's object is forwarded unchanged to the
// shared handler; the explicit one-byte local preserves the retail
// mov/test branch shape while the argument record selects one of the two
// already reconstructed 0x2F8-byte object factories.

class Rva007903F0VptrCtor;
class Rva00790480VptrCtor;
class Rva00793150VptrCtor;
class Rva007931B0VptrCtor;
class Rva00798510VptrCtor;
class Rva007985A0VptrCtor;
class Rva00796A60VptrCtor;
class Rva00796AF0VptrCtor;
class Rva00793D30VptrCtor;
class Rva00793E00VptrCtor;
class Rva007961D0VptrCtor;
class Rva00796260VptrCtor;
class Rva0078FCA0VptrCtor;
class Rva0078FD30VptrCtor;
class Rva007996A0VptrCtor;
class Rva00799730VptrCtor;
class Rva00790C40VptrCtor;
class Rva00790CD0VptrCtor;

Rva007903F0VptrCtor *__stdcall Rva0078F100New(void *argument);
Rva00790480VptrCtor *__stdcall Rva0078F180New(void *argument);
Rva00793150VptrCtor *__stdcall Rva0078F200New(void *argument);
Rva007931B0VptrCtor *__stdcall Rva0078F280New(void *argument);
Rva00798510VptrCtor *__stdcall Rva0078EE00New(void *argument);
Rva007985A0VptrCtor *__stdcall Rva0078EE80New(void *argument);
Rva00796A60VptrCtor *__stdcall Rva0078E8F0New(void *argument);
Rva00796AF0VptrCtor *__stdcall Rva0078E970New(void *argument);
Rva00793D30VptrCtor *__stdcall Rva0078E9F0New(void *argument);
Rva00793E00VptrCtor *__stdcall Rva0078EA70New(void *argument);
Rva007961D0VptrCtor *__stdcall Rva0078EB00New(void *argument);
Rva00796260VptrCtor *__stdcall Rva0078EB80New(void *argument);
Rva0078FCA0VptrCtor *__stdcall Rva0078EC00New(void *argument);
Rva0078FD30VptrCtor *__stdcall Rva0078EC80New(void *argument);
Rva007996A0VptrCtor *__stdcall Rva0078F300New(void *argument);
Rva00799730VptrCtor *__stdcall Rva0078F380New(void *argument);
Rva00790C40VptrCtor *__stdcall Rva0078F400New(void *argument);
Rva00790CD0VptrCtor *__stdcall Rva0078F480New(void *argument);
void *__stdcall Rva0078ED00New(void *argument);
void *__stdcall Rva0078ED80New(void *argument);
void *__stdcall Rva0078EF00New(void *argument);
void *__stdcall Rva0078EF80New(void *argument);
void *__stdcall Rva0078F000New(void *argument);
void *__stdcall Rva0078F080New(void *argument);

typedef void *(__stdcall *Rva0078F950Factory)(void *argument);

class Rva0078F830Predicate
{
public:
	unsigned char flags(void);
};

struct Rva0078F830Context
{
	char m_gap[12];
	unsigned int m_flags;
};

struct Rva0078F950Record
{
	Rva0078F830Predicate *m_head;
	signed char m_kind;
	char m_gap[19];
	Rva0078F950Factory m_factory;
	char m_gap2[20];
	Rva0078F830Context *m_context;
};

class Rva0078F950Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

class Rva0078F8D0Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

class Rva0078F910Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

#define DECLARE_FACTORY_SELECTOR_OWNER(address) \
	class Rva##address##Owner \
	{ \
	public: \
		void selectFactory(Rva0078F950Record *record); \
		void dispatchFactory(Rva0078F950Record *record); \
	}

DECLARE_FACTORY_SELECTOR_OWNER(0078F630);
DECLARE_FACTORY_SELECTOR_OWNER(0078F670);
DECLARE_FACTORY_SELECTOR_OWNER(0078F6B0);
DECLARE_FACTORY_SELECTOR_OWNER(0078F6F0);

class Rva0078F730Owner
{
public:
	void selectFactory(Rva0078F950Record *record, int first, int second,
		int third);
	void dispatchFactory(Rva0078F950Record *record, int first, int second,
		int third);
};

struct Rva0078F770Secondary
{
	char m_gap[11];
	unsigned char m_flag;
};

class Rva0078F770Owner
{
public:
	void selectFactory(Rva0078F950Record *record,
		Rva0078F770Secondary *secondary, int ignored, int value);
	void dispatchFactory(Rva0078F950Record *record,
		Rva0078F770Secondary *secondary, int ignored, int value);
};

class Rva0078F830Owner
{
public:
	int selectFactory(Rva0078F950Record *record, int first, int second,
		int third);
	int dispatchFactory(Rva0078F950Record *record, int first, int second,
		int third);
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

void Rva0078F8D0Owner::selectFactory(Rva0078F950Record *record)
{
	signed char kind = record->m_kind;

	if (kind & 0x80)
		record->m_factory = (Rva0078F950Factory)Rva0078F280New;
	else
		record->m_factory = (Rva0078F950Factory)Rva0078F200New;

	dispatchFactory(record);
}

void Rva0078F910Owner::selectFactory(Rva0078F950Record *record)
{
	signed char kind = record->m_kind;

	if (kind & 0x80)
		record->m_factory = (Rva0078F950Factory)Rva0078EE80New;
	else
		record->m_factory = (Rva0078F950Factory)Rva0078EE00New;

	dispatchFactory(record);
}

#define DEFINE_FACTORY_SELECTOR(address, negativeFactory, nonnegativeFactory) \
	void Rva##address##Owner::selectFactory(Rva0078F950Record *record) \
	{ \
		signed char kind = record->m_kind; \
		if (kind & 0x80) \
			record->m_factory = (Rva0078F950Factory)negativeFactory; \
		else \
			record->m_factory = (Rva0078F950Factory)nonnegativeFactory; \
		dispatchFactory(record); \
	}

DEFINE_FACTORY_SELECTOR(0078F630, Rva0078EA70New, Rva0078E9F0New)
DEFINE_FACTORY_SELECTOR(0078F670, Rva0078E970New, Rva0078E8F0New)
DEFINE_FACTORY_SELECTOR(0078F6B0, Rva0078EC80New, Rva0078EC00New)
DEFINE_FACTORY_SELECTOR(0078F6F0, Rva0078EB80New, Rva0078EB00New)

void Rva0078F730Owner::selectFactory(Rva0078F950Record *record, int first,
	int second, int third)
{
	signed char kind = record->m_kind;

	if (kind & 0x80)
		record->m_factory = (Rva0078F950Factory)Rva0078ED80New;
	else
		record->m_factory = (Rva0078F950Factory)Rva0078ED00New;

	dispatchFactory(record, first, second, third);
}

void Rva0078F770Owner::selectFactory(Rva0078F950Record *record,
	Rva0078F770Secondary *secondary, int ignored, int value)
{
	signed char kind = record->m_kind;

	if (kind & 0x80)
	{
		if (secondary->m_flag)
			record->m_factory = (Rva0078F950Factory)Rva0078F080New;
		else
			record->m_factory = (Rva0078F950Factory)Rva0078F000New;
	}
	else if (secondary->m_flag)
		record->m_factory = (Rva0078F950Factory)Rva0078EF80New;
	else
		record->m_factory = (Rva0078F950Factory)Rva0078EF00New;

	dispatchFactory(record, secondary, ignored, value);
}

int Rva0078F830Owner::selectFactory(Rva0078F950Record *record, int first,
	int second, int third)
{
	unsigned int flags = record->m_context->m_flags;

	if (flags & 0x10)
	{
		if (record->m_kind & 0x80)
			record->m_factory = (Rva0078F950Factory)Rva0078F480New;
		else
			record->m_factory = (Rva0078F950Factory)Rva0078F400New;
	}
	else if (flags & 8)
	{
		if ((record->m_kind & 0x80) && (record->m_head == 0 ||
			!(record->m_head->flags() & 0x20)))
			record->m_factory = (Rva0078F950Factory)Rva0078F380New;
		else
			record->m_factory = (Rva0078F950Factory)Rva0078F300New;
	}
	else
	{
		return 0;
	}

	return dispatchFactory(record, first, second, third);
}
