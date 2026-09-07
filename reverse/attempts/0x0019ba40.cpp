// ?append@Rva0019BE80TeamRec@@QAEHPBVDict@@@Z
// partial score=0.98 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc- /Oy- /Ob1 /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad

#include <new>

class Dict
{
public:
	Dict() { construct(0); }
	Dict(const Dict &other)
		: m_data(other.m_data)
	{
		if (m_data)
			++*(short *)m_data;
	}
	~Dict() { releaseForAppend(); }
	void construct(int count);
	void clearForAppend();
	void assignFrom(const Dict *other);

private:
	void releaseForAppend();
	void *m_data;
};

#pragma comment(linker, "/alternatename:?assignFrom@Dict@@QAEXPBV1@@Z=?j_00045566@@YAXXZ")
#pragma comment(linker, "/alternatename:?construct@Dict@@QAEXH@Z=?j_00002ecd@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearForAppend@Dict@@QAEXXZ=?j_00033f46@@YAXXZ")
#pragma comment(linker, "/alternatename:?releaseForAppend@Dict@@AAEXXZ=?j_00014475@@YAXXZ")

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	__forceinline void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			new (_M_finish) Type(value);
			++_M_finish;
		}
		else
		{
			int framePad[2];
			framePad[0] = framePad[0];
			__false_type &tag = *reinterpret_cast<__false_type *>((char *)&framePad + 0x1f);
			insertOverflowForAppend(_M_finish, value, tag, 1, true);
		}
	}

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

protected:
	void insertOverflowForAppend(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
};

#pragma comment(linker, "/alternatename:?insertOverflowForAppend@?$vector@UGen_t_0019a890_p16cd@@V?$allocator@UGen_t_0019a890_p16cd@@@_STL@@@_STL@@IAEXPAUGen_t_0019a890_p16cd@@ABU3@ABU__false_type@2@I_N@Z=?j_00012332@@YAXXZ")
}

struct Gen_t_0019a890_p16cd
{
	short next;
	short previous;
	short reserved;
	short free;
	int generation;
	Dict dict;

	Gen_t_0019a890_p16cd()
		: next(0), previous(0), reserved(0), free(0), generation(0), dict()
	{
	}

	__forceinline Gen_t_0019a890_p16cd(const Gen_t_0019a890_p16cd &other)
		: next(other.next), previous(other.previous), reserved(other.reserved),
		  free(other.free), generation(other.generation), dict(other.dict)
	{
	}
};

class Rva0019BE80TeamRec
{
public:
	int append(const Dict *dict);

private:
	char m_prefix[0xc];
	_STL::vector<Gen_t_0019a890_p16cd,
		_STL::allocator<Gen_t_0019a890_p16cd> > m_teams;
	short m_numActive;
	short m_freeHead;

	public:
	void updateTeam(int index);
};

#pragma comment(linker, "/alternatename:?updateTeam@Rva0019BE80TeamRec@@QAEXH@Z=?j_000026ee@@YAXXZ")

int Rva0019BE80TeamRec::append(const Dict *dict)
{
	if (m_freeHead == 0)
	{
		int index = (int)(m_teams._M_finish - m_teams._M_start);
		Gen_t_0019a890_p16cd team;
		m_teams.push_back(team);
		m_freeHead = (short)index;
	}

	int index = m_freeHead;
	Gen_t_0019a890_p16cd *team = m_teams._M_start + index;
	team->dict.clearForAppend();
	if (dict)
		team->dict.assignFrom(dict);
	updateTeam(index);
	m_freeHead = team->next;
	m_teams._M_start[m_teams._M_start[0].previous].next = (short)index;
	team->previous = m_teams._M_start[0].previous;
	team->next = 0;
	m_teams._M_start[0].previous = (short)index;
	++m_numActive;
	return index;
}
