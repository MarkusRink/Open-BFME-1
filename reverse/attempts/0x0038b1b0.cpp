// ?sendObjectCreated@GameLogic@@QAEXPAVObject@@@Z
// partial score=0.98 date=2026-09-07
// Near-match for GameLogic::sendObjectCreated, retail 0x0038B1B0, 207 bytes.

class Object;
class Drawable;
class ThingTemplate;
class DelayedLuaEventList;

extern int GetGameLogicRandomValue(int low, int high, char *file, int line);

class GameLogic
{
public:
	void sendObjectCreated(Object *obj);
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int index, Object *object, DelayedLuaEventList *events);
};

extern BfmeOwnerBR *g_bfmeOwnerBR;

void GameLogic::sendObjectCreated(Object *obj)
{
	int drawableID = GetGameLogicRandomValue(1, 999, __FILE__, __LINE__);
	int status = 0;
	if ((reinterpret_cast<const unsigned int *>(obj)[0x94 / 4] & 0x400000) != 0)
		status = 0x20;

	const ThingTemplate *thing = reinterpret_cast<const ThingTemplate * const *>(obj)[1];
	if (thing)
		thing = thing;

	Drawable *draw = reinterpret_cast<Drawable *(*)(const ThingTemplate *, int, int)>(0)(thing, status, drawableID);
	(void)draw;

	DelayedLuaEventList events;
	g_bfmeOwnerBR->bfmeGo939B(0xc, obj, &events);
}
