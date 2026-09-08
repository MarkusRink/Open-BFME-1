// ?helper@Rva00894120Vector@@QAEXPAX00@Z
// partial score=0.85 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /Oy

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

struct BfmeStringPool3AF0
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct Rva00892640Item
{
	Rva00892640Item();
	Rva00892640Item &operator=(const Rva00892640Item &other);
	~Rva00892640Item();

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

class BfmeG1045
{
public:
	BfmeG1045 *bfmeGo1045G(BfmeG1045 *other);

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

Rva00892640Item::Rva00892640Item()
{
	m_handle = &g_bfmeDefaultString1284;
	++m_handle->m_refs;
	m_extra = 0;
}

Rva00892640Item &Rva00892640Item::operator=(
	const Rva00892640Item &other)
{
	reinterpret_cast<BfmeG1045 *>(this)->bfmeGo1045G(
		reinterpret_cast<BfmeG1045 *>(const_cast<Rva00892640Item *>(&other)));
	return *this;
}

Rva00892640Item::~Rva00892640Item()
{
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		g_bfmeStringPool1284->m_destroy(old);
}

extern Rva00892640Item *Rva008926D0CopyItems(
	Rva00892640Item *first, Rva00892640Item *last,
	Rva00892640Item *dest);
extern Rva00892640Item *Rva00892730CopyItems(
	Rva00892640Item *first, Rva00892640Item *last,
	Rva00892640Item *dest);

class Gen_uw_00893e70
{
public:
	void resize(int new_capacity);

protected:
	unsigned m_count;
	int m_capacity;
	Rva00892640Item *m_items;
};

class Rva00894120Vector : public Gen_uw_00893e70
{
public:
	void helper(void *, void *, void *);
};

// ?helper@Rva00894120Vector@@QAEXPAX00@Z
void Rva00894120Vector::helper(void *first_arg, void *last_arg,
	void *insert_arg)
{
	Rva00892640Item *last = *static_cast<Rva00892640Item **>(last_arg);
	Rva00892640Item *first = *static_cast<Rva00892640Item **>(first_arg);
	int count = (int)(last - first);
	if (count == 0)
		return;

	int capacity = m_capacity;
	int new_count = m_count + count;
	if (new_count < capacity)
	{
		Rva00892640Item *old_end = m_items + m_count;
		Rva00892640Item *insert =
		*static_cast<Rva00892640Item **>(insert_arg);
		if (insert != old_end)
		{
			Rva00892730CopyItems(insert, old_end, insert + count);
		}
		Rva008926D0CopyItems(first, last, insert);

		Rva00892640Item empty;
		m_items[new_count] = empty;
		m_count = new_count;
		return;
	}

	int new_capacity = (int)(m_capacity * 2.0);
	if (new_capacity < new_count)
		new_capacity = new_count;

	Rva00892640Item *insert =
		*static_cast<Rva00892640Item **>(insert_arg);
	int offset = (int)(insert - m_items);
	resize(new_capacity);
	insert = m_items + offset;
	helper(first_arg, last_arg, &insert);
}
