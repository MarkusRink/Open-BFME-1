// cl: /DNDEBUG /MD /EHsc
// ScriptEngine slot 16 resolves a canonical team name through TheTeamFactory.

class AsciiString
{
public:
	AsciiString(void) : m_text(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString(void);

private:
	char *m_text;
};

class TeamPrototype;
class ScriptEngine;

class BFMEScriptEngineFlagLookup
{
	friend class ScriptEngine;
	private:
	AsciiString canonicalFlagName(const AsciiString &name);
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);
};

extern TeamFactory *TheTeamFactory;

class ScriptEngine
{
public:
	TeamPrototype *getTeamPrototypeNamed(AsciiString name);
};

// ?getTeamPrototypeNamed@ScriptEngine@@QAEPAVTeamPrototype@@VAsciiString@@@Z
TeamPrototype *ScriptEngine::getTeamPrototypeNamed(AsciiString name)
{
	AsciiString canonical =
		((BFMEScriptEngineFlagLookup *)this)->canonicalFlagName(name);
	return TheTeamFactory->findTeamPrototype(canonical, name);
}
