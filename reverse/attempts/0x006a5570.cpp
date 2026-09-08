// ?d_006a5570@@YAXXZ
// partial score=0.95 date=2026-09-08
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?processHandleStates@MilesAudioManager@@QAEXXZ
// The update body scans the Miles handle-state table and releases entries
// whose low-level handle has stopped.  The table starts at +0xB44 and each
// entry occupies 0x40 bytes in the BFME manager layout.

extern "C" __declspec(dllimport) int __stdcall bfmeStatusDXD(void *handle);
typedef unsigned char Bool;
typedef int (__stdcall *StatusFunction)(void *);

struct MilesHandleState
{
	unsigned char m_active;
	unsigned char m_pad01[3];
	void *m_handle;
	unsigned char m_pad08[4];
	unsigned char m_ready;
	unsigned char m_pad0d[0x33];
};

class MilesAudioManager
{
public:
	virtual void vtableSlot();
	void processHandleStates();

private:
	char m_pad004[0xB44 - 4];
	MilesHandleState *m_handleStates;
	int m_handleStateCount;

	void releaseHandleState(MilesHandleState *state);
};

#pragma comment(linker, "/alternatename:?releaseHandleState@MilesAudioManager@@AAEXPAUMilesHandleState@@@Z=?j_0003b741@@YAXXZ")

void MilesAudioManager::processHandleStates()
{
	int i = 0;
	if (m_handleStateCount > 0)
	{
		StatusFunction status = (StatusFunction)&bfmeStatusDXD;
		int offset = 0;
		do
		{
			if (!((unsigned char *)m_handleStates)[offset] &&
				((unsigned char *)m_handleStates)[offset + 0x0C])
			{
				void *handle = *(void **)((unsigned char *)m_handleStates + offset + 4);
				if (handle)
				{
					bool shouldRelease = status(handle) != 4;
					if (shouldRelease)
						releaseHandleState((MilesHandleState *)((unsigned char *)m_handleStates + offset));
				}
			}
			++i;
			offset += 0x40;
		} while (i < m_handleStateCount);
	}
}
