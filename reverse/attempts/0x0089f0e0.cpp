// ?Right@EAStringC@@QBE?AV1@H@Z
// partial score=0.9 date=2026-09-07
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

class EAStringC
{
	public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

private:
	StringDataC *m_pData;

	public:
	EAStringC();
	EAStringC(const EAStringC &other) : m_pData(other.m_pData)
	{
		++m_pData->m_uRefCount;
	}
	EAStringC(const StringDataC *data)
	{
		++const_cast<StringDataC *>(data)->m_uRefCount;
		m_pData = const_cast<StringDataC *>(data);
	}
	~EAStringC()
	{
		StringDataC *oldData = m_pData;
		if (--oldData->m_uRefCount == 0)
			g_bfmeAllocVKJ->free(oldData);
	}

	private:
		enum CBPushZero
		{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero push_zero, unsigned int size);

	public:
	EAStringC Right(int count) const;
};

extern EAStringC::StringDataC g_emptyStringData;

EAStringC::EAStringC()
	: m_pData(&g_emptyStringData)
{
	++g_emptyStringData.m_uRefCount;
}

EAStringC EAStringC::Right(int count) const
{
	if (count <= 0)
		return EAStringC();

	int remaining = (int)m_pData->m_uSize - count;
	if (remaining <= 0)
		return EAStringC(*this);

	EAStringC result(m_pData);
	result.ChangeBuffer(count, (unsigned int)remaining, count, CB_PUSH_ZERO,
		count);
	return result;
}
