// ?d_00284700@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count );
extern "C" void *__cdecl memset( void *destination, int value,
	unsigned int size );

struct BannerCarrierStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class BannerCarrierString
{
public:
	BannerCarrierStringData *m_data;

	int compareNoCase( const BannerCarrierString &that ) const
	{
		const int length = that.m_data ? that.m_data->m_length : 0;
		const char *data = that.m_data ? that.m_data->m_text
			: (const char *)0x0107388b;
		const int thisLength = m_data ? m_data->m_length : 0;
		const char *thisData = m_data ? m_data->m_text
			: (const char *)0x0107388b;
		int difference = _memicmp( thisData, data,
			thisLength < length ? thisLength : length );
		if (difference != 0)
			return difference;
		return thisLength - length;
	}
};

struct BannerCarrierObjectPayload
{
	BannerCarrierString m_templateName;
	unsigned int m_fields[9];
};

class BannerCarrierObjectName
{
public:
	BannerCarrierString m_name;
	unsigned int m_unknown;
	BannerCarrierObjectPayload m_payload;
	BannerCarrierString m_objectTemplateName;
};

class BannerCarrierUpgrade
{
};

class BannerCarrierUpdateModuleDataBase
{
public:
	virtual ~BannerCarrierUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x14];
};

class BannerCarrierUpdateModuleData : public BannerCarrierUpdateModuleDataBase
{
public:
	virtual ~BannerCarrierUpdateModuleData();
	void findObjectName( BannerCarrierObjectPayload &result,
		const BannerCarrierString *name );

private:
	std::vector<BannerCarrierObjectName *> m_objectNames;
	std::vector<BannerCarrierUpgrade *> m_upgrades;
	BannerCarrierString m_bannerMorphFX;
	BannerCarrierString m_unitSpawnFX;
	unsigned char m_replenishNearbyHorde;
	unsigned char m_replenishAllNearbyHordes;
	unsigned char m_padding[2];
	float m_scanHordeDistance;
};

// ?findObjectName@BannerCarrierUpdateModuleData@@QBEXPAVBannerCarrierObjectPayload@@PBVBannerCarrierString@@@Z
void BannerCarrierUpdateModuleData::findObjectName(
	BannerCarrierObjectPayload &result, const BannerCarrierString *name )
{
	for (unsigned int i = 0; i < m_objectNames.size(); ++i)
	{
		if (m_objectNames[i]->m_name.compareNoCase( *name ) == 0)
		{
			BannerCarrierObjectPayload &output = result;
			output = m_objectNames[i]->m_payload;
			return;
		}
	}

	memset( &result, 0, sizeof( result ) );
	result.m_fields[4] |= 0x4000;
}
