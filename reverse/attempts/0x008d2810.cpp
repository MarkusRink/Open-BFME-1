// ?bfmeActivate1236@BfmeNode1236@@QAEXXZ
// partial score=0.72 date=2026-09-08
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
};

class BfmeA1227
{
public:
	void bfmeDump1227(void *value, int index);
};

class BfmeNodeDX
{
public:
	void bfmeEmit1281(int mode, void *tail, int zero);
};

class BfmeFilterWalk1236
{
public:
	void bfmeFilterWalk1236();
	void *m_list;
};

class BfmeNode1236List
{
public:
	void bfmeProcess1236(void *walk, void *owner, int count);
	int m_count;
};

struct BfmeCountedList1236
{
	char m_padding00[8];
	BfmeNode1236List m_ops;
};

struct BfmeChild1236
{
	char m_padding00[0x0c];
	BfmeCountedList1236 *m_list;
	char m_padding10[8];
	int m_count;
	unsigned int m_flags;
	BfmeFilterWalk1236 m_walk20;
	BfmeFilterWalk1236 m_walk24;
	int m_pending;
	int m_limit;
};

class BfmeNode1236
{
public:
	void bfmeActivate1236();

private:
	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x48];
	BfmeChild1236 *m_child;
};

extern volatile unsigned char g_bfmeExtra1282Flags;
extern void *g_bfmeExtra1282;

void BfmeNode1236::bfmeActivate1236()
{
	bool one = true;
	register BfmeNode1236 *self = this;
	unsigned int flags = self->m_flags;
	unsigned int type = flags;
	type &= 0x3f;
	if (type == 0x0d)
		goto check_d;
	goto check_12;

check_d:
	{
		unsigned int bit = flags;
		bit >>= 15;
		if ((((unsigned char)~bit) & one) == 0)
			goto activate;
	}

check_12:
	if (type != 0x12)
		goto type_done;
	{
		unsigned int bit = flags;
		bit >>= 15;
		if ((((unsigned char)~bit) & one) != 0)
			goto type_done;
	}

activate:
	BfmeChild1236 *child = self->m_child;
	unsigned int child_flags = child->m_flags;
	child_flags >>= 25;
	child_flags &= one;
	int zero = 0;
	child->m_pending = zero;
	if (child_flags != zero)
	{
		if (child->m_limit == one)
		{
			child->m_count = 0;
			goto count_done;
		}
		++child->m_count;
		int count = child->m_count;
		if (count == one && child->m_list->m_ops.m_count == one)
		{
			child->m_count = 0;
			goto count_done;
		}
	}

	{
		int count = child->m_count;
		if (count == child->m_list->m_ops.m_count)
		{
			reinterpret_cast<BfmeThingCBC *>(self)->bfmeStepCBC(0);
			goto finish;
		}
	}

count_done:
	{
		int count = child->m_count;
		register BfmeCountedList1236 *list = child->m_list;
		list->m_ops.bfmeProcess1236(&child->m_walk24, self, count);
		if ((child->m_flags & 0x02000000) != 0)
		{
			child->m_pending = -count;
			reinterpret_cast<BfmeA1227 *>((char *)list)->bfmeDump1227(self, count);
			child->m_pending = child->m_count;
		}
	}

	if (((unsigned char *)&child->m_flags)[3] != 0)
	{
		flags = self->m_flags;
		type = flags & 0x3f;
		if (type == 0x12 && !((unsigned char)(~(flags >> 15)) & one) &&
			(g_bfmeExtra1282Flags & 2) == 0)
			reinterpret_cast<BfmeNodeDX *>(self)->bfmeEmit1281(2, g_bfmeExtra1282, one);
	}
	if (((unsigned char *)&child->m_flags)[3] != 0)
		reinterpret_cast<BfmeNodeDX *>(self)->bfmeEmit1281(1, g_bfmeExtra1282, one);

finish:
	child->m_flags &= 0xfeffffff;
	self->m_child->m_walk24.bfmeFilterWalk1236();
	return;

type_done:
	if (type != 0x0e || ((unsigned char)(~(flags >> 15)) & 1))
		return;
	self->m_child->m_walk20.bfmeFilterWalk1236();
}
