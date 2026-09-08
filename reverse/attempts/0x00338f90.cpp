// ?bfmeWantsFA@BfmeHostFA@@QAE_NXZ
// partial score=0.85 date=2026-09-08
extern void *TheScriptDebugWindowDLL;
extern bool g_bfmeDebugAFA;
extern bool g_bfmeDebugBFA;

class BfmeHostFA
{
public:
	bool bfmeWantsFA();

	unsigned char m_bfmeHeadFA[0x17638];
	bool m_bfmeFlagFA;
};

bool BfmeHostFA::bfmeWantsFA()
{
	return (m_bfmeFlagFA && TheScriptDebugWindowDLL != 0 && g_bfmeDebugAFA == false)
		|| (!m_bfmeFlagFA && TheScriptDebugWindowDLL != 0 && g_bfmeDebugBFA == false);
}
