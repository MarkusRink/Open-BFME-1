// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// DockUpdate::onEnterReached reconstructed from the BFME retail body at 0x002CDDF0.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMask;
typedef bool Bool;
typedef int Int;

class BfmeFlags
{
public:
	Bool test(Int bit) const
	{
		return (m_bits & (1U << bit)) != 0;
	}

	void set(Int bit)
	{
		m_bits |= 1U << bit;
	}

private:
	UnsignedInt m_bits;
};

template <int Bits>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(bit) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (bit))

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);

	unsigned char m_pad[0x130];
	BfmeFlags m_flags;
};

class GameLogic
{
public:
	void deselectObject(Object *object, PlayerMask playerMask, Bool affectClient);
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

extern GameLogic *TheGameLogic;

class DockUpdate
{
public:
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
};

void DockUpdate::onEnterReached(Object *docker)
{
	DockUpdate::onApproachReached(docker);
	GameLogic *logic = TheGameLogic;
	Object *me = *(Object **)((char *)this - 0x18);
	logic->deselectObject(docker, 0xffff, true);
	me->setStatus(MAKE_OBJECT_STATUS_MASK(3));
	me->setStatus(MAKE_OBJECT_STATUS_MASK(59));
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(3));
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(59));

	Object *owner = *(Object **)((char *)this - 0x18);
	if (!owner->m_flags.test(16))
	{
		owner->m_flags.set(16);
		((BfmeOwnerVNI *)owner)->bfmeApply1VNI();
	}
}
