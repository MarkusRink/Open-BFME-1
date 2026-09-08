// ??0BfmeSettingsZV@@QAE@XZ
// partial score=0.92 date=2026-09-08
class BfmeVec3ZV
{
public:
	float m_bfmeXZV;
	float m_bfmeYZV;
	float m_bfmeZZV;
};

class BfmeSettingsZV
{
public:
	BfmeSettingsZV();

	float m_bfme00ZV;
	float m_bfme04ZV;
	float m_bfme08ZV;
	float m_bfme0CZV;
	float m_bfme10ZV;
	float m_bfme14ZV;
	float m_bfme18ZV;
	float m_bfme1CZV;
	float m_bfme20ZV;
	float m_bfme24ZV;
	BfmeVec3ZV m_bfme28ZV;
	BfmeVec3ZV m_bfme34ZV;
	BfmeVec3ZV m_bfme40ZV;
	float m_bfme4CZV;
	float m_bfme50ZV;
	float m_bfme54ZV;
};

BfmeSettingsZV::BfmeSettingsZV()
{
	m_bfme34ZV.m_bfmeXZV = 0.5f;
	m_bfme34ZV.m_bfmeYZV = 0.5f;
	m_bfme34ZV.m_bfmeZZV = 0.5f;

	m_bfme40ZV = m_bfme34ZV;
	m_bfme28ZV = m_bfme34ZV;

	m_bfme00ZV = 4.0f;
	m_bfme04ZV = 0.7f;
	m_bfme08ZV = 1.0f;
	m_bfme0CZV = 1.0f;
	m_bfme10ZV = 1.0f;
	m_bfme14ZV = 1.0f;
	m_bfme18ZV = 1.0f;
	m_bfme1CZV = 1.0f;
	m_bfme24ZV = 1.0f;
	m_bfme20ZV = 1.0f;
	m_bfme4CZV = 1.0f;
	m_bfme50ZV = 1.0f;
	m_bfme54ZV = 5.0f;
}
