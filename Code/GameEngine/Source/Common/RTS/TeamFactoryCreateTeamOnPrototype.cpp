// cl: /DNDEBUG /MD /EHsc
//
// The caller at 0x000F7FA0 is TeamPrototype::xfer, and its call to this body
// identifies TeamFactory::createTeamOnPrototype.  The retail body checks the
// singleton flag at prototype+0x18, reuses the instance at +0x274, allocates a
// 0x110-byte Team, and activates its +0x31 and +0x32 flags.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class TeamPrototype;

class Team
{
public:
  Team(TeamPrototype *prototype, UnsignedInt id);

  __forceinline void setActive() {
    if (!m_active) {
      m_created = 1;
      m_active = 1;
    }
  }

private:
  char m_padding[0x31];
  UnsignedByte m_active;
  UnsignedByte m_created;
  char m_tail[0xdd];
};

class TeamPrototype
{
public:
  __forceinline bool getIsSingleton() const {
    return (*(const UnsignedByte *)((const char *)this + 0x18) & 1) != 0;
  }

  __forceinline Team *getFirstItemIn_TeamInstanceList() const {
    return *(Team *const *)((const char *)this + 0x274);
  }
};

class TeamFactory
{
public:
  Team *createTeamOnPrototype(TeamPrototype *prototype);

private:
  char m_padding[0x1c];
  UnsignedInt m_uniqueTeamID;
};

// ?createTeamOnPrototype@TeamFactory@@QAEPAVTeam@@PAVTeamPrototype@@@Z
Team *TeamFactory::createTeamOnPrototype(TeamPrototype *prototype)
{
  if (prototype == 0)
    return 0;

  Team *team = 0;
  if (prototype->getIsSingleton()) {
    team = prototype->getFirstItemIn_TeamInstanceList();
    if (team)
      return team;
  }

  team = new Team(prototype, ++m_uniqueTeamID);
  team->setActive();
  return team;
}
