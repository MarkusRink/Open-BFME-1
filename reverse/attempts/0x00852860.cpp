// ?parseByte@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: INI::parseByte (retail 0x00852860 129 B; a gap claimed through
// its literal).  Zero Hour's body with BFME's inline getNextToken: strtok on
// the INI separator set at +0x414 (imported) and INIException(3 "Expected
// additional data after '%s'" seps) when the line is exhausted; the token
// goes through INI::scanInt and a value outside -128..127 throws the plain
// INI_INVALID_DATA integer (throw-info VA 0x012454C0); otherwise the low
// byte is stored.

typedef int Int;
typedef char Byte;

extern "C" __declspec(dllimport) char *__cdecl strtok( char *s, const char *delim );

enum { INI_INVALID_DATA = 1 };

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
	static Int scanInt( const char *token );
	static void parseByte( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
};

// ?parseByte@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseByte( INI *ini, void *, void *store, const void * )
{
	const char *seps = ini->m_seps;
	const char *token = strtok( 0, seps );
	if( !token )
		throw INIException( 3, "Expected additional data after '%s'", seps );
	Int value = INI::scanInt( token );
	if( value < -128 || value > 127 )
		throw INI_INVALID_DATA;
	*(Byte *)store = (Byte)value;
}
