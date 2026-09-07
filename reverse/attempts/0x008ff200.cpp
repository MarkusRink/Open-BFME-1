// q4-hidden-return-refholder
// partial score=0.75 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc
// Scratch reconstruction for the unresolved hidden-return/refholder body at
// retail RVA 0x008FF200.  The by-value parameter and inline lifetime model
// reproduce 141/141 bytes except for the entry EH-state placement.

class BfmePrototypeFF
{
public:
	void Release_Ref(void);
};

class BfmeHandleFF
{
public:
	BfmeHandleFF(void) : m_ptr(0) {}
	BfmeHandleFF(void *prototype);
	~BfmeHandleFF(void)
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}

	BfmePrototypeFF *m_ptr;
};

void *__cdecl Find_Prototype_FF(BfmeHandleFF *slot,
	BfmePrototypeFF *prototype);

BfmeHandleFF __cdecl probeLookup008FF200(BfmeHandleFF prototype)
{
	if (prototype.m_ptr == 0)
		return BfmeHandleFF();

	void *found = Find_Prototype_FF(&prototype, prototype.m_ptr);
	return BfmeHandleFF(found);
}
