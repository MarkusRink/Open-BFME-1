// ?first@Gen_00943CF0@@AAEXPAXPAPAX11@Z
// partial score=0.9 date=2026-09-08
// Clean reconstruction of the linked-node traversal at retail RVA 0x00943CF0.
// The owning type and the two helper identities are not recovered; their
// address-derived declarations preserve the call boundaries and observed
// pointer flow without inventing a semantic name.

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class Gen_00943CF0
{
	struct Bounds
	{
		float first;
		float second;
		float third;
		float fourth;
	};

	class Value
	{
	public:
		virtual void slot0() = 0;
		virtual void slot1() = 0;
		virtual void slot2() = 0;
		virtual void slot3() = 0;
		virtual void slot4() = 0;
		virtual void slot5() = 0;
		virtual void slot6() = 0;
		virtual void slot7() = 0;
		virtual void slot8() = 0;
		virtual void slot9() = 0;
		virtual void slot10() = 0;
		virtual void slot11() = 0;
		virtual void slot12() = 0;
		virtual void slot13() = 0;
		virtual void slot14() = 0;
		virtual void slot15() = 0;
		virtual void slot16() = 0;
		virtual void slot17() = 0;
		virtual void slot18() = 0;
		virtual void slot19() = 0;
		virtual void slot20() = 0;
		virtual void slot21() = 0;
		virtual void slot22() = 0;
		virtual void slot23() = 0;
		virtual void slot24() = 0;
		virtual void slot25() = 0;
		virtual void slot26() = 0;
		virtual void slot27() = 0;
		virtual void slot28() = 0;
		virtual void slot29() = 0;
		virtual void slot30() = 0;
		virtual void slot31() = 0;
		virtual void slot32() = 0;
		virtual void slot33() = 0;
		virtual void slot34() = 0;
		virtual void slot35() = 0;
		virtual void slot36() = 0;
		virtual void slot37() = 0;
		virtual void slot38() = 0;
		virtual void slot39() = 0;
		virtual void slot40() = 0;
		virtual void slot41() = 0;
		virtual void slot42() = 0;
		virtual void slot43() = 0;
		virtual void slot44() = 0;
		virtual void slot45() = 0;
		virtual void slot46() = 0;
		virtual void slot47() = 0;
		virtual void slot48() = 0;
		virtual void slot49() = 0;
		virtual void slot50() = 0;
		virtual void slot51() = 0;
		virtual void slot52() = 0;
		virtual void slot53() = 0;
		virtual void slot54() = 0;
		virtual void slot55() = 0;
		virtual void slot56() = 0;
		virtual void slot57() = 0;
		virtual void slot58() = 0;
		virtual void slot59() = 0;
		virtual void slot60() = 0;
		virtual void slot61() = 0;
		virtual void slot62() = 0;
		virtual void slot63() = 0;
		virtual void slot64() = 0;
		virtual void slot65() = 0;
		virtual void getBounds(Bounds *bounds) = 0;
		virtual void slot66() = 0;
		virtual void slot67() = 0;
		virtual void slot68() = 0;
		virtual float getRadius() = 0;

		unsigned char padding04[0x20];
		float center_x;
		unsigned char padding28[0x0c];
		float center_y;
	};

	void first(void *value, void **secondOutput, void **firstOutput,
		void **listAddress);
	void second(void *value, void *secondOutput, void *firstOutput,
		void *list);

public:
	void process(Gen_00943CF0_Node **list);
};

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);
};

void Gen_00943CF0::first(void *rawValue, void **secondOutput,
	void **firstOutput, void **listAddress)
{
	Value *value = (Value *)rawValue;
	Bounds bounds;
	float center[3];
	center[0] = value->center_x;
	center[1] = value->center_y;
	value->getBounds(&bounds);
	float extent = value->getRadius() + bounds.fourth;

	*(unsigned int *)secondOutput = ((Gen_009431F0 *)this)->map_x(center[1] - extent);
	*(unsigned int *)firstOutput = ((Gen_009431F0 *)this)->map_y(center[1] - extent);
	unsigned int mask = ((Gen_009431F0 *)this)->map_y(center[1] + extent) ^
		*(unsigned int *)firstOutput;
	mask |= ((Gen_009431F0 *)this)->map_x(center[0] + extent) ^
		*(unsigned int *)secondOutput;
	*(unsigned int *)listAddress = mask;
	if (mask != 0) {
		unsigned int bit = 0;
		if ((mask & 0xff00) != 0) {
			mask >>= 8;
			bit = 8;
		}
		if ((mask & 0xf0) != 0) {
			mask >>= 4;
			bit += 4;
		}
		if ((mask & 0x0c) != 0) {
			mask >>= 2;
			bit += 2;
		}
		if ((mask & 2) != 0)
			++bit;
		unsigned int keep = ~(1u << bit);
		*(unsigned int *)secondOutput &= keep;
		*(unsigned int *)firstOutput &= keep;
	}
}

void Gen_00943CF0::process(Gen_00943CF0_Node **list)
{
	Gen_00943CF0_Node *node = *list;
	while (node != 0) {
		void *value = node->m_value;
		void *firstOutput;
		void *secondOutput;
		first(value, &secondOutput, &firstOutput, (void **)&list);
		second(value, secondOutput, firstOutput, list);
		node = node->m_next;
	}
}
