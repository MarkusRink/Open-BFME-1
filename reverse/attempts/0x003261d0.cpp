// ?evaluateTeamIsLedByUnit@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/objectdlink

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int ObjectID;

__forceinline Bool objectIDsEqual(ObjectID first, const ObjectID &second)
{
	return first == second;
}

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

#define HORDE_SLOT(N) virtual void slot##N() = 0

class HordeContainInterface
{
public:
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52);
	virtual Bool isAffectedByLeadership(ObjectID leaderID) = 0;
};

#undef HORDE_SLOT

#define CONTAIN_SLOT(N) virtual void slot##N() = 0

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17); CONTAIN_SLOT(18); CONTAIN_SLOT(19);
	CONTAIN_SLOT(20); CONTAIN_SLOT(21); CONTAIN_SLOT(22); CONTAIN_SLOT(23);
	CONTAIN_SLOT(24); CONTAIN_SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef CONTAIN_SLOT

class BfmeScriptObject
{
public:
	unsigned char m_beforeID[0x74];
	ObjectID m_id;
	unsigned char m_beforeContain[0x1fc - 0x78];
	ContainModuleInterface *m_contain;
	unsigned char m_beforeLeaderID[0x360 - 0x200];
	ObjectID m_leaderID;

	ObjectID getID() const { return m_id; }
	ObjectID getLeaderID() const { return m_leaderID; }
};

class ObjectIdView : public Object
{
public:
	ObjectID getID() const
	{
		return *(const ObjectID *)((const char *)this + 0x74);
	}
};

template <class T> class DlinkIterator
{
public:
	typedef T *(T::*GetNextFunc)() const;

	DlinkIterator(T *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	T *cur() const { return m_cur; }


	public:
	T *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DlinkIterator<Object> iterate_TeamMemberList() const
	{
		return DlinkIterator<Object>(m_memberListHead,
			Object::dlink_next_TeamMemberList);
	}

private:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_memberListHead;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamIsLedByUnit(Parameter *, Parameter *);
};

// ?evaluateTeamIsLedByUnit@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamIsLedByUnit(
	Parameter *pTeamParm, Parameter *pUnitParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	Object *leader = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!theTeam || !leader)
		return false;
	BfmeScriptObject *leaderObject = (BfmeScriptObject *)leader;

	DlinkIterator<Object> iter = theTeam->iterate_TeamMemberList();
	if (iter.m_cur == 0)
		goto no_match;

loop:
	{
		Object *member = iter.cur();
		const BfmeScriptObject *bfmeMember = (const BfmeScriptObject *)member;
		ContainModuleInterface *contain = bfmeMember->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde != 0)
			{
				if (horde->isAffectedByLeadership(leaderObject->getID()))
					return true;
			}
		}

		ObjectID memberLeaderID = bfmeMember->getLeaderID();
		if (objectIDsEqual(memberLeaderID, leaderObject->getID()))
			goto match;

		iter.advance();
		if (iter.m_cur != 0)
			goto loop;
	}

no_match:
	return false;

match:
	return true;
}
