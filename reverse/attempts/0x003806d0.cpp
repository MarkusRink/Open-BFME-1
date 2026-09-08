// ?rva003806D0@ExperienceLevelSystem@@QAEPAVExperienceLevel@@PAVExperienceLevelCollection@@ABVAsciiString@@@Z
// partial score=0.78 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc- /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// ExperienceLevelSystem's next-level selector, retail 0x003806D0.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class BfmeSubBOB
{
public:
	BfmeSubBOB *bfmeFindBOB();

	void *m_vtable;
	BfmeSubBOB *m_nested;
};

class GameLogicPortraitShim
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};

extern GameLogicPortraitShim *TheBfmeGameLogic;

class ExperienceLevel
{
	public:
	void *m_vtable;
	BfmeSubBOB *m_redirect;
	unsigned char m_unmodelled_008[8];
	Int m_requiredExperience;
	unsigned char m_unmodelled_014[0xbd];
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
};

struct ExperienceLevelNode
{
	ExperienceLevelNode *m_next;
	ExperienceLevelNode *m_previous;
	ExperienceLevel m_value;
};

class ExperienceLevelCollection
{
	public:
	ExperienceLevelNode *m_sentinel;
};

class ExperienceLevelSystem
{
public:
	ExperienceLevel *findLevel(const AsciiString &name);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *levels, const AsciiString &name);
};

// ?rva003806D0@ExperienceLevelSystem@@QAEPAVExperienceLevel@@PAVExperienceLevelCollection@@ABVAsciiString@@@Z
ExperienceLevel *ExperienceLevelSystem::rva003806D0(
	ExperienceLevelCollection *levels, const AsciiString &name)
{
	ExperienceLevel *current = findLevel(name);
	Int currentRequiredExperience = 0;
	if (current != 0)
		currentRequiredExperience = current->m_requiredExperience;

	ExperienceLevelNode *sentinel = levels->m_sentinel;
	ExperienceLevelNode *node = sentinel->m_next;
	Int nextRequiredExperience = 0x7fffffff;
	ExperienceLevel *next = 0;
	if (node != sentinel)
	{
		do
		{
			ExperienceLevel *level = &node->m_value;
			ExperienceLevel *selected = level;
			if (level->m_redirect != 0)
		{
				BfmeSubBOB *nested = level->m_redirect->m_nested;
				if (nested != 0)
					selected = (ExperienceLevel *)nested->bfmeFindBOB();

				else
					selected = (ExperienceLevel *)level->m_redirect;
			}

			if (selected != 0)
			{
				Bool permitted;
				if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
					permitted = !selected->m_singlePlayerOnly;
				else
					permitted = !selected->m_multiPlayerOnly;

				if (permitted &&
					selected->m_requiredExperience > currentRequiredExperience &&
					selected->m_requiredExperience < nextRequiredExperience)
				{
					nextRequiredExperience = selected->m_requiredExperience;
					next = selected;
				}
			}

			node = node->m_next;
		} while (node != sentinel);
	}
	return next;
}
