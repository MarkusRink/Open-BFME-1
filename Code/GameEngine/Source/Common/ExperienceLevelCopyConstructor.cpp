// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME retail 0x00381B60.  The STLport node construction at 0x00381C30
// passes its 0xD8-byte value at node+8 to this copy constructor through ILT
// 0x00027084.  The same value layout is established by ExperienceLevel's
// matched default constructor, destructor, parser field table 0x010EAB48,
// and list copy/range-insert specializations.

#define _STLP_NO_EXCEPTIONS 1
#include <string.h>
#include <vector>

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

class Overridable
{
protected:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

private:
	AsciiString m_name;
	AsciiString m_secondName;
	Int m_shadowType;
	Real m_minOpacity;
	Real m_maxOpacity;
	Real m_opacityThrobTime;
	UnsignedInt m_color;
	Bool m_onlyVisibleToOwningPlayer;
	UnsignedInt m_unmodelled20;
	UnsignedInt m_unmodelled24;
	UnsignedInt m_unmodelled28;
	UnsignedInt m_unmodelled2c;
};

struct ModelConditionFlags
{
	ModelConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	UnsignedInt m_bits[10];
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

struct LevelUpFXInfo
{
	const void *fx;
	AsciiString boneName;
};

typedef std::vector<AsciiString> AsciiStringVector;
typedef std::vector<LevelUpFXInfo> LevelUpFXVector;

class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel(const ExperienceLevel &that);
	~ExperienceLevel();
	ExperienceLevel &operator=(const ExperienceLevel &that);

private:
	AsciiString m_name;
	Int m_requiredExperience;
	Int m_experienceAward;
	Int m_experienceAwardOwnGuysDie;
	AsciiStringVector m_targetNames;
	AsciiStringVector m_attributeModifiers;
	LevelUpFXVector m_levelUpFx;
	Int m_levelUpOCL;
	AsciiStringVector m_upgrades;
	ModelConditionFlags m_modelConditionState;
	RadiusDecalTemplate m_selectionDecal;
	Bool m_showLevelUpTint;
	RGBColor m_levelUpTintColor;
	Int m_levelUpTintPreColorTime;
	Int m_levelUpTintPostColorTime;
	Int m_levelUpTintSustainColorTime;
	Real m_levelUpTintFrequency;
	Real m_levelUpTintAmplitude;
	Int m_rank;
	Bool m_informUpdateModule;
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
	Int m_emotionType;
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xD8 ? 1 : -1];

// The retail constructor first establishes every owning subobject, then uses
// ExperienceLevel::operator= at 0x00381690 to copy the complete value.  The
// scalar fields intentionally have no initializer: the assignment is their
// first write, exactly as in retail.
// Retail FuncInfo 0x0120BB24 has seven unwind states.  Its actions destroy,
// in construction order, Overridable, m_name, the four vectors, and
// m_selectionDecal; the compiled typed constructor produces the same state
// map and the same seven cleanup targets.
ExperienceLevel::ExperienceLevel(const ExperienceLevel &that)
	: m_name(),
	  m_targetNames(),
	  m_attributeModifiers(),
	  m_levelUpFx(),
	  m_upgrades(),
	  m_modelConditionState(),
	  m_selectionDecal()
{
	*this = that;
}
