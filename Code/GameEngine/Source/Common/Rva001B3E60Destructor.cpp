// cl: /DNDEBUG /MD /EHsc /O2 /vd2
//
// The body at 0x001B3E60 restores the 0x0109CE94, 0x0109CE80, and 0x0109CE68
// virtual tables, destroys the member at +0x20 through the pinned 0x000309F4
// destructor, and restores the base table at 0x01073744.  The secondary base
// owns a four-slot base and a five-slot virtual base.  Its final methods and
// the 0x7C-byte nonvirtual layout make MSVC emit the retail vtordisp update.
// The surrounding class name is not recovered, so this source keeps the
// address-derived Rva001B3E60 name.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Rva001B3E60VBase
{
public:
	virtual void vslot00() { }
	virtual void vslot04() { }
	virtual void vslot08() { }
	virtual void vslot0C() { }
	virtual void vslot10() { }
};

class Rva001B3E60SecondBaseCore
{
public:
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
};

class Rva001B3E60SecondBase
	: public Rva001B3E60SecondBaseCore
	, virtual public Rva001B3E60VBase
{
};

class ClearanceTestingSlowDeathBehaviorModuleDataMember
{
public:
	~ClearanceTestingSlowDeathBehaviorModuleDataMember();
};

class Rva001B3E60
	: public BfmeBaseVUQ
	, public Rva001B3E60SecondBase
{
public:
	~Rva001B3E60();

	virtual void vslot00() { }
	virtual void vslot04() { }
	virtual void vslot08() { }
	virtual void vslot0C() { }
	virtual void vslot10() { }

private:
	unsigned char m_pad0C[0x14];
	ClearanceTestingSlowDeathBehaviorModuleDataMember m_member;
	unsigned char m_tail[0x5C];
};

// @??1Rva001B3E60@@UAE@XZ 0x001B3E60
Rva001B3E60::~Rva001B3E60()
{
}
