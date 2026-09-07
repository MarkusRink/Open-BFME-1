struct Gen009F5040Item;

struct Gen009F5040Node
{
	char m_pad00[4];
	Gen009F5040Item *m_item;
	char m_pad08[0x10];
	Gen009F5040Node **m_previousLink;
	Gen009F5040Node *m_next;
	volatile int m_index;
	int m_result24;
	int m_result28;
	int m_result2c;
};

struct Gen009F5040Item
{
	virtual void *getValue0();
	virtual void *getValue1();
	virtual void *getValue2();
	virtual void *getValue3();
	virtual void *getValue4();
	virtual void *getValue5();
	virtual void *getValue6();
	virtual int getIndex();
};

struct BfmeNode912C
{
	char m_pad00[0xc];
	BfmeNode912C *m_next;
};

class BfmeThing912C
{
public:
	void bfmeDo912C(BfmeNode912C *node);
};

class Gen009F5040
{
public:
	void handle();
	void calculate(Gen009F5040Node *node, int *result28, int *result2c,
		int *result24);
	void remove(Gen009F5040Node *node);

	char m_pad00[0xf0];
	Gen009F5040Node *m_node;
};

#pragma comment(linker, "/alternatename:?calculate@Gen009F5040@@QAEXPAVGen009F5040Node@@PAH11@Z=?d_009f4900@@YAXXZ")
#pragma comment(linker, "/alternatename:?remove@Gen009F5040@@QAEXPAVGen009F5040Node@@@Z=?d_009f4e40@@YAXXZ")

void Gen009F5040::handle()
{
	Gen009F5040Node *node = m_node;
	if (node == 0)
		return;

	while (node != 0) {
		if (node->m_next != 0)
			node->m_next->m_previousLink = node->m_previousLink;
		*node->m_previousLink = node->m_next;
		node->m_previousLink = 0;

		bool shouldProcess = node->m_index != node->m_item->getIndex() + 1;
		if (!shouldProcess) {
			int result28;
			int result2c;
			int result24;
			calculate(node, &result28, &result2c, &result24);
			if (result28 != node->m_result28 || result2c != node->m_result2c ||
				result24 != node->m_result24)
				shouldProcess = true;
		}
		if (shouldProcess) {
			remove(node);
			((BfmeThing912C *)this)->bfmeDo912C((BfmeNode912C *)node);
		}

		node = m_node;
	}
}
