// ?nextParam@@YAPADPAD0@Z
// partial score=0.94 date=2026-09-07
#include <string.h>

#define g_nextParamSource (*(char **)0x012ED264)

typedef char *(__cdecl *StrpbrkFunction)(const char *, const char *);

char *nextParam(char *newSource, char *seps)
{
	char *source = newSource;
	if (source)
	{
		g_nextParamSource = source;
	}
	else
	{
		source = g_nextParamSource;
	}

	if (!source)
	{
		return 0;
	}

	char *first = source;
	if (first)
	{
		StrpbrkFunction find = *(StrpbrkFunction *)0x013594C4;
		char *firstSep = find(first, seps);
		char firstChar[2] = { 0, 0 };
		if (firstSep == first)
		{
			firstChar[0] = *first;
			while (*first == firstChar[0])
			{
				first++;
			}
		}

		char *end;
		if (firstChar[0])
		{
			end = find(first, firstChar);
		}
		else
		{
			end = find(first, seps);
		}

		if (end)
		{
			source = end + 1;
			*(volatile char *)end = 0;
			g_nextParamSource = source;
			if (!*source)
			{
				g_nextParamSource = 0;
			}
		}
		else
		{
			g_nextParamSource = 0;
		}

		if (first && !*first)
		{
			first = 0;
		}
	}

	return first;
}
