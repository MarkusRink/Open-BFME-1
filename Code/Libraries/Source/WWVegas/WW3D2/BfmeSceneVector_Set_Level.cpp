// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

void * __cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *pointer);

struct BfmeSceneVectorElement
{
	BfmeSceneVectorElement();
	~BfmeSceneVectorElement();
	unsigned char bytes[0x1c];
};

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *next;
};

struct Gen_uw_0002e866
{
	Gen_00943CF0_Node *head;
	~Gen_uw_0002e866();
};

class BfmeSceneVector
{
	void clear(Gen_uw_0002e866 *objects);
	void process(Gen_00943CF0_Node **objects);

	unsigned char unused[0x18];
	BfmeSceneVectorElement *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;

public:
	void Set_Level(unsigned int level);
};

void BfmeSceneVector::Set_Level(unsigned int level)
{
	if (level > 10)
		return;

	unsigned int mask = 1u << level;
	if (mask == level_mask)
		return;

	level_mask = mask;
	int count = 1;
	while (level != 0) {
		--level;
		count = count * 4 + 1;
	}

	Gen_uw_0002e866 objects = {0};
	clear(&objects);
	if (vector)
		delete[] vector;

	vector_max = count;
	vector = new BfmeSceneVectorElement[count];
	process(&objects.head);
}
