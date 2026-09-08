// ?bfmeApplyAAN@BfmeHookAAN@@QAEXXZ
// partial score=0.93 date=2026-09-08
template <int N>
class BitFlags
{
public:
	BitFlags()
	{
		for (int i = 0; i < 10; ++i)
			m_bfmeBitsAAN[i] = 0;
	}

	bool bfmeAnyAAN() const
	{
		for (int i = 0; i < 10; ++i)
			if (m_bfmeBitsAAN[i] != 0)
				return true;

		return false;
	}

	int m_bfmeBitsAAN[10];
};

class Object
{
public:
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear, const BitFlags<320> &set);
};

struct BfmeOwnerAAN
{
	unsigned char m_bfmeHeadAAN[0x70];
	BitFlags<320> m_bfmeClearAAN;
	BitFlags<320> m_bfmeSetAAN;
};

class BfmeHookAAN
{
public:
	void bfmeApplyAAN();
};

void BfmeHookAAN::bfmeApplyAAN()
{
	BfmeOwnerAAN *o = *(BfmeOwnerAAN **)((char *)this - 0xc);
	Object *obj = *(Object **)((char *)this - 8);

	if (o->m_bfmeSetAAN.bfmeAnyAAN())
		obj->clearAndSetModelConditionFlags(BitFlags<320>(), o->m_bfmeSetAAN);

	if (o->m_bfmeClearAAN.bfmeAnyAAN())
		obj->clearAndSetModelConditionFlags(o->m_bfmeClearAAN, BitFlags<320>());
}
