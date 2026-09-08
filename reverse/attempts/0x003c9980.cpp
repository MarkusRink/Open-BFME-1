// ?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.3 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: LivingWorldRegion::parseNamedSubBlock, retail 0x003C9980, 241
// bytes. LivingWorldRegion's constructor and BfmeThingDCG dispatch are named
// by the existing LivingWorldRegion source and matched helper rows.

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class BfmeOtherDCG;

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);
};

class LivingWorldRegion : public BfmeThingDCG
{
public:
	LivingWorldRegion(const AsciiString &name);
	void bfmeGoDCG(BfmeOtherDCG *other);

private:
	unsigned char m_data[0xF0];
};

namespace _STL
{
struct __true_type
{
};
}

class LivingWorldRegionStore
{
public:
	char m_head[0x30];
	LivingWorldRegion **m_start;
	LivingWorldRegion **m_finish;
	LivingWorldRegion **m_endOfStorage;

	void _M_insert_overflow(LivingWorldRegion **position,
		LivingWorldRegion *const &value, const _STL::__true_type &tag,
		unsigned int fillLength, bool atEnd);
};

class LivingWorldRegionManager
{
public:
	static void parseNamedSubBlock(INI *ini, void *instance, void *, const void *);
};

// ?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z
void LivingWorldRegionManager::parseNamedSubBlock(
	INI *ini, void *instance, void *, const void *)
{
	const char *token = ini->getNextToken();
	LivingWorldRegion *region;

	{
		AsciiString name(token);
		region = new LivingWorldRegion(name);
	}

	region->bfmeGoDCG(reinterpret_cast<BfmeOtherDCG *>(ini));

	LivingWorldRegionStore *store =
		reinterpret_cast<LivingWorldRegionStore *>(instance);
	if (store->m_finish != store->m_endOfStorage)
	{
		*store->m_finish = region;
		++store->m_finish;
	}
	else
	{
		store->_M_insert_overflow(store->m_finish, region,
			_STL::__true_type(), 1, true);
	}
}
