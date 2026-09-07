// ?bfmeProvideObjective@BfmeAptScreenObjectives@@QAEXPBDPAX_N@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

#include <stdio.h>
#include <string.h>

struct Gen_0052B440GameLogic
{
	unsigned char m_unmodelled[0x10C];
	int m_gameMode;
};

class Gen_0052B440
{
public:
	void bfmeProvide(const char *selector, void *value, bool setting);

private:
	unsigned char m_unmodelled[0x258];
	void **m_playersBegin;
	void **m_playersEnd;
	void **m_playersLimit;
	int m_screenType;
};

class CampaignManager
{
public:
	unsigned char isMissionObjectiveComplete(int index);
	unsigned char isMissionObjectiveIndexed(int index);
};

extern CampaignManager *TheCampaignManager;
extern int bfmeFindNthPred(int index);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeGameLogicObjectiveState
{
	unsigned char m_unmodelled[0x10C];
	int m_gameMode;
};

class BfmeAptScreenObjectives
{
public:
	void bfmeProvideObjective(const char *selector, void *value, bool setting);

private:
	unsigned char m_unmodelled[0x264];
	int m_screenType;
};

enum
{
	BFME_NUM_OF_PLAYERS = 0,
	BFME_IN_SKIRMISH = 1,
	BFME_PLAYER_STATUS = 1,
	BFME_GAME_SKIRMISH = 2
};

// The Objectives/PlayerStatus constructor at 0x0052C660 binds ILT 0x00025B08
// for the two-entry { NumOfPlayers, InSkirmish } provider table.  Its retail
// method spelling is not exposed, so the class and method remain surrogates.
// ?bfmeProvide@Gen_0052B440@@QAEXPBDPAX_N@Z
void Gen_0052B440::bfmeProvide(const char *selector, void *value, bool setting)
{
	char *output = (char *)value;
	output[0] = '0';
	output[1] = '\0';

	switch ((int)selector)
	{
	case BFME_NUM_OF_PLAYERS:
		if (!setting && m_screenType == BFME_PLAYER_STATUS)
			sprintf(output, "%d", m_playersEnd - m_playersBegin);
		break;

	case BFME_IN_SKIRMISH:
		if (!setting)
		{
			Gen_0052B440GameLogic *gameLogic =
				*(Gen_0052B440GameLogic **)0x012F0898;
			strcpy(output,
				gameLogic && gameLogic->m_gameMode == BFME_GAME_SKIRMISH ? "1" : "0");
		}
		break;
	}
}

// ?bfmeProvideObjective@BfmeAptScreenObjectives@@QAEXPBDPAX_N@Z
void BfmeAptScreenObjectives::bfmeProvideObjective(
	const char *selector, void *value, bool setting)
{
	char *output = (char *)value;
	int index = (int)selector;
	*(unsigned short *)output = *(unsigned short *)0x01106D6C;
	output[2] = *(char *)0x01106D6E;

	if (m_screenType != 0)
		return;
	if (index < 0)
		return;
	if (index >= 9)
		return;
	if (setting)
		return;
	if ((*(BfmeGameLogicObjectiveState **)0x012F0898)->m_gameMode == 7)
		return;

	_ReadWriteBarrier();
	int objective = bfmeFindNthPred(index);
	if (objective < 0)
		return;

	output[0] = TheCampaignManager->isMissionObjectiveComplete(objective) ? '1' : '0';
	output[1] = TheCampaignManager->isMissionObjectiveIndexed(objective) ? '1' : '0';
	output[2] = 0;
}
