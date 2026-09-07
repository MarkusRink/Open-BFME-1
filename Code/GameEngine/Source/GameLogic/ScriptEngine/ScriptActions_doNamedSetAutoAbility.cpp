// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: NAME_SET_AUTO_ABILITY handler at retail RVA 0x002F6D70.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase( const BfmeStringArgBase &other );
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg( const AsciiString &that )
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class Object;

class ScriptEngineByValue
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	virtual Object *getUnitNamedByValue( BfmeAsciiStringArg name ) = 0;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class Module
{
};

class Object
{
public:
	Module *findModule( NameKeyType key ) const;
	const AsciiString &getCommandSetString() const;
};

class CommandButton
{
};

class ControlBar
{
public:
	const CommandButton *findCommandButton( const AsciiString &name );
	const class CommandSet *findCommandSet( const AsciiString &name );
};

class BfmeArgVSJ
{
};

class CommandSet
{
public:
	const CommandButton *getCommandButton( Int index ) const;
};

class AutoAbilityBehavior
{
};

class BfmeOwnVSJ
{
public:
	void bfmeApplyVSJ( BfmeArgVSJ *commandButton, char enabled );
};

extern ScriptEngineByValue *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ControlBar *TheControlBar;

class ScriptActions
{
protected:
	void doNamedSetAutoAbility( const AsciiString &unitName,
		const AsciiString &commandButtonName, Bool enabled );
};

void ScriptActions::doNamedSetAutoAbility(
	const AsciiString &unitName, const AsciiString &commandButtonName, Bool enabled )
{
	Object *object = TheScriptEngine->getUnitNamedByValue( unitName );
	if ( object )
	{
		static NameKeyType autoAbilityBehaviorKey =
			TheNameKeyGenerator->nameToKey( "AutoAbilityBehavior" );
		AutoAbilityBehavior *behavior = (AutoAbilityBehavior *)
			object->findModule( autoAbilityBehaviorKey );
		if ( behavior )
		{
			const CommandButton *commandButton =
				TheControlBar->findCommandButton( commandButtonName );
			if ( commandButton &&
				*(const unsigned char *)((const char *)commandButton + 0x158) )
			{
				const CommandSet *commandSet =
					TheControlBar->findCommandSet( object->getCommandSetString() );
				if ( commandSet )
				{
					for ( Int i = 0; i < 20; ++i )
					{
						if ( commandButton == commandSet->getCommandButton( i ) )
						{
							((BfmeOwnVSJ *)behavior)->bfmeApplyVSJ(
								(BfmeArgVSJ *)commandButton, enabled );
						}
					}
				}
			}
		}
	}
}
