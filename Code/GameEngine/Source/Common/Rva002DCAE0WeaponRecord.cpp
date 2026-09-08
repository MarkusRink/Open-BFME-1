// cl: /O2 /Ob0

// Slot 5 of the 12-entry weapon-record vtable installed by
// Rva002DCBA0's matched constructor.  The retail code accepts an
// address-like record and a Thing, looks up the record's object id, and
// lets the resolved module handle the Thing when the record flags allow it.
// The address-derived names below intentionally avoid claiming a stronger
// semantic identity than the vtable and call evidence establish.

enum KindOfType
{
    // Retail pushes 0x8d; the compact BFME KindOf shim has no recovered
    // semantic name for this value, so keep the exact value explicit.
    RvaKindOfTypeRetail8D = 0x8d
};

class Thing
{
public:
    bool isKindOf(KindOfType kind) const;

    unsigned char m_gap00[0x98];
    unsigned char m_flags98;
};

class Object
{
public:
    unsigned char m_gap00[0x1fc];
    class Rva002DCAE0Module *m_module;
};

class Rva002DCAE0Module
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual bool slot33(Thing *thing, int mode) = 0;
    virtual void slot34(Thing *thing) = 0;
};

class GameLogic
{
public:
    Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;

class __declspec(novtable) Rva002DCBA0
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void rva002DCAE0Slot5(void *record, Thing *thing);
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;

    unsigned char m_gap04[0x54];
    unsigned char m_flag58;
    unsigned char m_flag59;

};

extern void j_000229fd(void);

class Rva002DC8B0Call
{
public:
    void apply(Object *found, Thing *thing);
};

void Rva002DCBA0::rva002DCAE0Slot5(void *record, Thing *thing)
{
    if (record == 0)
        return;

    Thing *thingForRecord;
    Object *found;

    found = TheBfmeGameLogic->findObjectByID(
        *(int *)((unsigned char *)record + 8));

    if (found == 0)
        return;

    thingForRecord = thing;
    if (thingForRecord == 0)
        return;

    if (!thingForRecord->isKindOf(RvaKindOfTypeRetail8D) &&
        (thingForRecord->m_flags98 & 4) == 0)
        return;

    Rva002DCAE0Module *module = found->m_module;
    if (m_flag58 && module != 0 && module->slot33(thingForRecord, 1))
    {
        module->slot34(thingForRecord);
        return;
    }

    if (m_flag59)
    {
        typedef void (Rva002DC8B0Call::*Function)(Object *, Thing *);
        union
        {
            void (*raw)(void);
            Function member;
        } fn;
        fn.raw = j_000229fd;
        (reinterpret_cast<Rva002DC8B0Call *>(this)->*fn.member)(found,
            thingForRecord);
    }
}
