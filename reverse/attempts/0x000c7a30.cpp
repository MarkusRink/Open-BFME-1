// ?bfmeNewMap@BfmePlayerMapState@@QAEXH_N@Z
// partial score=0.85 date=2026-09-08
// Reconstructed from the retail field map and the Player::newMap caller.
// Probe: 345 bytes versus retail's 352. Fields and call graph are aligned,
// but MSVC emits different branch layout and register scheduling in the
// multiplayer count selection and non-multiplayer fallback.

typedef int Int;
typedef bool Bool;

class Player
{
public:
    char m_padding[0x2c];
    void *m_mapState;
};

class PlayerList
{
public:
    int countPlayers(Bool includeObservers);
    Player *getNthPlayer(Int index);
};

class GameLogic
{
public:
    Bool isInMultiplayerOrSkirmishGame();
};

class BfmeGlobalState
{
public:
    char m_padding[0xe70];
    int m_valueE70;
    int m_valueE74;
    int m_valueE78;
    int m_valueE7C;
    int m_valueE80;
    int m_valueE84;
    int m_valueE88;
    int m_valueE8C;
    int m_valueE90;
    int m_valueE94;
    int m_valueE98;
    int m_valueE9C;
    int m_valueEA0;
    int m_valueEA4;
    int m_valueEA8;
    int m_valueEAC;
};

class BfmeMapAdjustment
{
public:
    Bool apply();
};

extern PlayerList * volatile ThePlayers;
extern GameLogic *TheBfmeGameLogic;
extern BfmeGlobalState *TheWritableGlobalData;
extern BfmeMapAdjustment *TheBfmeMapAdjustment;

class BfmePlayerMapState
{
public:
    int m_value00;
    int m_value04;
    int m_value08;
    int m_field;
    int m_value10;
    int m_value14;

    void bfmeNewMap(Int field, Bool flag);
};

void BfmePlayerMapState::bfmeNewMap(Int field, Bool flag)
{
    if (field < 0 || field >= 0x20)
        return;
    if (!ThePlayers)
        return;
    if (!TheBfmeGameLogic)
        return;

    m_field = field;
    if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
    {
        int count = ThePlayers->countPlayers(true);
        int x;
        int y;
        if (count >= 7)
        {
            x = TheWritableGlobalData->m_valueEAC;
            y = TheWritableGlobalData->m_valueEA8;
        }
        else if (count >= 5)
        {
            x = TheWritableGlobalData->m_valueEA4;
            y = TheWritableGlobalData->m_valueEA0;
        }
        else
        {
            if (count == 4)
            {
                x = TheWritableGlobalData->m_valueE9C;
                y = TheWritableGlobalData->m_valueE98;
            }
            else if (count == 3)
            {
                x = TheWritableGlobalData->m_valueE94;
                y = TheWritableGlobalData->m_valueE90;
            }
            else
            {
                x = TheWritableGlobalData->m_valueE8C;
                y = TheWritableGlobalData->m_valueE88;
            }
        }

        if (flag)
            m_value04 = x;
        else
            m_value04 = y;
        m_value04 += m_value14 * x;
        m_value04 += m_value10 * y;
        return;
    }

    Player *player = ThePlayers->getNthPlayer(m_field);
    if (!player)
        return;

    if (player->m_mapState)
    {
        m_value04 = flag ? TheWritableGlobalData->m_valueE84
                         : TheWritableGlobalData->m_valueE80;
        return;
    }

    m_value04 = flag ? TheWritableGlobalData->m_valueE74
                     : TheWritableGlobalData->m_valueE70;
    if (TheBfmeMapAdjustment)
        m_value04 += TheBfmeMapAdjustment->apply();
}
