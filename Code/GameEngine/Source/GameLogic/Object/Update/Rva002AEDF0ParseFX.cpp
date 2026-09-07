// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The module view retains only the parsed per-phase FX vectors at +0x8C.

#include <vector>

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	static int scanIndexList(const char *token, const char *const *list);
};

class FXParticleSystem
{
public:
	class TerrainCollisionEventFXLookupShim
	{
	public:
		const FXList *lookup(const char *name) const;
	};
};

extern FXParticleSystem::TerrainCollisionEventFXLookupShim *g_glob12F144C;
extern const char *const Rva002AEDF0PhaseNames[];

class Rva002AEDF0ModuleData
{
public:
	unsigned char m_unreconstructed_00[0x8c];
	_STL::vector<const FXList *> m_fxs[8];
};

// ?d_002aedf0@@YAXXZ
void Rva002AEDF0ParseFX(INI *ini, void *instance, void *, const void *)
{
	Rva002AEDF0ModuleData *self = (Rva002AEDF0ModuleData *)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), Rva002AEDF0PhaseNames);
	for (const char *token = ini->getNextToken(); token != 0; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = g_glob12F144C->lookup(token);
		self->m_fxs[phase].push_back(fxl);
	}
}
