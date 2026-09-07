// ?applyAttributeModifier@HordeContainInterface@@QAEXABVAsciiString@@PAVRva2225E0Filter@@H@Z
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: HordeContain::applyAttributeModifier, retail 0x00239AF0.
// The HordeContain interface vtable at 0x010AED58 uses this body at slot 108.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;

class AsciiString
{
public:
	void *m_data;
};

class NameKeyGenerator
{
public:
	UnsignedInt nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierDefinition
{
public:
	char m_unused[0xc];
	UnsignedInt m_flags;
};

class AttributeModifierDefinitionStore
{
public:
	AttributeModifierDefinition *findDefinition(UnsignedInt key);
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class AttributeModifierPoolUpdate
{
public:
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
};

class Object
{
public:
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate(void) const;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

struct BfmeMemberIndexNode;

class BfmeRvaA760CountOwner
{
public:
	Int getCount(void);

	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

typedef _STL::list<Object *> BfmeMemberList;
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(UnsignedInt key)
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};

extern GameLogic *TheGameLogic;

#define BFME_SLOT(N) virtual Int bfmeSlot##N(void) = 0

class BfmeHordeContainBase
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64);
	virtual BfmeMemberList *getMemberList(void) = 0;
};

#undef BFME_SLOT

class BfmeHordeContainFields
{
};

#define BFME_HORDE_SLOT(N)

class HordeContainInterface
{
public:
	BFME_HORDE_SLOT(00); BFME_HORDE_SLOT(01); BFME_HORDE_SLOT(02);
	BFME_HORDE_SLOT(03); BFME_HORDE_SLOT(04); BFME_HORDE_SLOT(05);
	BFME_HORDE_SLOT(06); BFME_HORDE_SLOT(07); BFME_HORDE_SLOT(08);
	BFME_HORDE_SLOT(09); BFME_HORDE_SLOT(10); BFME_HORDE_SLOT(11);
	BFME_HORDE_SLOT(12); BFME_HORDE_SLOT(13); BFME_HORDE_SLOT(14);
	BFME_HORDE_SLOT(15); BFME_HORDE_SLOT(16); BFME_HORDE_SLOT(17);
	BFME_HORDE_SLOT(18); BFME_HORDE_SLOT(19); BFME_HORDE_SLOT(20);
	BFME_HORDE_SLOT(21); BFME_HORDE_SLOT(22); BFME_HORDE_SLOT(23);
	BFME_HORDE_SLOT(24); BFME_HORDE_SLOT(25); BFME_HORDE_SLOT(26);
	BFME_HORDE_SLOT(27); BFME_HORDE_SLOT(28); BFME_HORDE_SLOT(29);
	BFME_HORDE_SLOT(30); BFME_HORDE_SLOT(31); BFME_HORDE_SLOT(32);
	BFME_HORDE_SLOT(33); BFME_HORDE_SLOT(34); BFME_HORDE_SLOT(35);
	BFME_HORDE_SLOT(36); BFME_HORDE_SLOT(37); BFME_HORDE_SLOT(38);
	BFME_HORDE_SLOT(39); BFME_HORDE_SLOT(40); BFME_HORDE_SLOT(41);
	BFME_HORDE_SLOT(42); BFME_HORDE_SLOT(43); BFME_HORDE_SLOT(44);
	BFME_HORDE_SLOT(45); BFME_HORDE_SLOT(46); BFME_HORDE_SLOT(47);
	BFME_HORDE_SLOT(48); BFME_HORDE_SLOT(49); BFME_HORDE_SLOT(50);
	BFME_HORDE_SLOT(51); BFME_HORDE_SLOT(52); BFME_HORDE_SLOT(53);
	BFME_HORDE_SLOT(54); BFME_HORDE_SLOT(55); BFME_HORDE_SLOT(56);
	BFME_HORDE_SLOT(57); BFME_HORDE_SLOT(58); BFME_HORDE_SLOT(59);
	BFME_HORDE_SLOT(60); BFME_HORDE_SLOT(61); BFME_HORDE_SLOT(62);
	BFME_HORDE_SLOT(63); BFME_HORDE_SLOT(64); BFME_HORDE_SLOT(65);
	BFME_HORDE_SLOT(66); BFME_HORDE_SLOT(67); BFME_HORDE_SLOT(68);
	BFME_HORDE_SLOT(69); BFME_HORDE_SLOT(70); BFME_HORDE_SLOT(71);
	BFME_HORDE_SLOT(72); BFME_HORDE_SLOT(73); BFME_HORDE_SLOT(74);
	BFME_HORDE_SLOT(75); BFME_HORDE_SLOT(76); BFME_HORDE_SLOT(77);
	BFME_HORDE_SLOT(78); BFME_HORDE_SLOT(79); BFME_HORDE_SLOT(80);
	BFME_HORDE_SLOT(81); BFME_HORDE_SLOT(82); BFME_HORDE_SLOT(83);
	BFME_HORDE_SLOT(84); BFME_HORDE_SLOT(85); BFME_HORDE_SLOT(86);
	BFME_HORDE_SLOT(87); BFME_HORDE_SLOT(88); BFME_HORDE_SLOT(89);
	BFME_HORDE_SLOT(90); BFME_HORDE_SLOT(91); BFME_HORDE_SLOT(92);
	BFME_HORDE_SLOT(93); BFME_HORDE_SLOT(94); BFME_HORDE_SLOT(95);
	BFME_HORDE_SLOT(96); BFME_HORDE_SLOT(97); BFME_HORDE_SLOT(98);
	BFME_HORDE_SLOT(99); BFME_HORDE_SLOT(100); BFME_HORDE_SLOT(101);
	BFME_HORDE_SLOT(102); BFME_HORDE_SLOT(103); BFME_HORDE_SLOT(104);
	BFME_HORDE_SLOT(105); BFME_HORDE_SLOT(106); BFME_HORDE_SLOT(107);
	void applyAttributeModifier(const AsciiString &name,
		Rva2225E0Filter *filter, Int duration);

};

// ?applyAttributeModifier@HordeContainInterface@@QAEXABVAsciiString@@PAVRva2225E0Filter@@H@Z
void HordeContainInterface::applyAttributeModifier(const AsciiString &name,
	Rva2225E0Filter *filter, Int duration)
{
	void *savedThis = this;
	BfmeHordeContainBase *base =
		(BfmeHordeContainBase *)((char *)savedThis - 0xc4);
	BfmeMemberList &members =
		*base->getMemberList();
	BfmeMemberList::iterator node = members.begin();
	{
		BfmeRvaA760CountOwner *countOwner =
			*(BfmeRvaA760CountOwner **)((char *)savedThis - 0xdc);

	const char *nameData = (const char *)name.m_data;
	if (nameData != 0)
		nameData += 8;
	else
		nameData = (const char *)0x0107388b;

	UnsignedInt key = TheNameKeyGenerator->nameToKey(nameData);
	AttributeModifierDefinition *definition =
		TheAttributeModifierDefinitionStore->findDefinition(key);
	if (definition != 0 && (definition->m_flags & 0x40) == 0)
	{
		while (node != members.end())
		{
			Object *object = *node;
			if (filter == 0 ||
				filter->accepts(object, (Player *)
						countOwner->getCount()))
				object->applyAttributeModifier(name, duration);
			++node;
		}

		BfmeMemberIndexNode *memberIndex =
			*(BfmeMemberIndexNode **)((char *)this + 0x30);
		BfmeMemberIndexNode *entry = memberIndex->m_next;
		if (entry != memberIndex)
		{
			do
			{
				Object *object = TheGameLogic->findObjectByID(entry->m_key);
				if (object != 0 &&
					(filter == 0 ||
						filter->accepts(object, (Player *)
								countOwner->getCount())))
					object->applyAttributeModifier(name, duration);
				entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
					(_STL::_Rb_tree_node_base *)entry);
			}
			while (entry != countOwner->m_memberIndex);
		}
	}
	}

	Object *owner = *(Object **)((char *)this - 0xdc);
	AttributeModifierPoolUpdate *pool = owner->findAttributeModifierPoolUpdate();
	if (pool != 0)
		pool->applyAttributeModifier(name, duration);
}
