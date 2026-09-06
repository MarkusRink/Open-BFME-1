// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: two INI real parsers claimed from the gap after
// parsePositiveNonZeroReal (retail 0x00852C10 and 0x00852CA0 144 B each).
// Both read the next token with BFME's inline getNextToken (imported strtok on
// the separator set at +0x414 and INIException(3 "Expected additional data
// after '%s'" seps) when the line is exhausted) scan it with INI::scanReal
// store it and then throw INIException(3 msg (double)value) when the sign is
// wrong: Zero Hour's parseNonNegativeReal rejects values below zero and the
// BFME-only parseNonPositiveReal rejects values above zero.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) char *__cdecl strtok( char *s, const char *delim );

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	static Real scanReal( const char *token );
	static void parseNonNegativeReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseNonPositiveReal( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
};

extern const Real BfmeZeroRange;

// ?parseNonNegativeReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseNonNegativeReal( INI *ini, void *, void *store, const void * )
{
	const char *seps = ini->m_seps;
	const char *token = strtok( 0, seps );
	if( !token )
		throw INIException( 3, "Expected additional data after '%s'", seps );
	Real value = INI::scanReal( token );
	*(Real *)store = value;
	if( value < BfmeZeroRange )
		throw INIException( 3, "invalid Real value %1.7f -- expected >= 0", value );
}

// ?parseNonPositiveReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseNonPositiveReal( INI *ini, void *, void *store, const void * )
{
	const char *seps = ini->m_seps;
	const char *token = strtok( 0, seps );
	if( !token )
		throw INIException( 3, "Expected additional data after '%s'", seps );
	Real value = INI::scanReal( token );
	*(Real *)store = value;
	if( value > BfmeZeroRange )
		throw INIException( 3, "invalid Real value %1.7f -- expected <= 0", value );
}
