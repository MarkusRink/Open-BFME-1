// ??1AIGroup@@UAE@XZ
// partial score=0.99 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::~AIGroup, retail 0x00151D10, 246 bytes.
//
// The deleting-destructor thunk at 0x00152690 calls this body. The AIGroup
// vtable and the AI::createGroup caller identify the class. The body walks the
// member list, releases the ground path, then destroys the BFME ID vector.

#include <list>
#include <vector>

typedef unsigned int UnsignedInt;

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() {}
};

class Object
{
public:
	void leaveGroup();
};

class Path
{
    friend class AIGroup;

protected:
    virtual ~Path();
};

void operator delete(void *block) throw();

class AIGroup : public BfmeBaseVUQ
{
public:
	virtual ~AIGroup();

private:
	_STL::list<Object *> m_memberList;
	UnsignedInt m_memberListSize;
	float m_speed;
	bool m_dirty;
    UnsignedInt m_id;
    Path *m_groundPath;
    void *m_pathState1C;
    void *m_pathState20;
    void *m_pathState24;
    float m_pathState28;
    void *m_pathState2C;
    void *m_pathState30;
	_STL::vector<UnsignedInt> m_lastRequestedIDList;
};

// ??1AIGroup@@UAE@XZ
AIGroup::~AIGroup()
{
    register AIGroup *self = this;
    register UnsignedInt zero = self->m_memberListSize - self->m_memberListSize;
    std::list<Object *>::iterator i;
    for (i = self->m_memberList.begin(); i != self->m_memberList.end();)
    {
        Object *member = *i;
        if (member != (Object *)zero)
        {
            member->leaveGroup();
            i = self->m_memberList.begin();
        }
        else
        {
            i = self->m_memberList.erase(i);
        }
    }

    register Path *groundPath = self->m_groundPath;
    if (groundPath != (Path *)zero)
    {
        groundPath->Path::~Path();
        self->m_groundPath = (Path *)zero;
        self->m_pathState1C = (void *)zero;
        self->m_pathState20 = (void *)zero;
        self->m_pathState24 = (void *)zero;
        self->m_pathState28 = 10.0f;
        self->m_pathState2C = (void *)zero;
        self->m_pathState30 = (void *)zero;
    }
}
