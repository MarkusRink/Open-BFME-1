// cl: /DNDEBUG /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWSaveLoad /I Code/Libraries/Source/WWVegas/WW3D2 /I Code/Libraries/Include

#include "rendobj.h"

class BfmeAnimationHolder
{
public:
	void applyScalePayload(float scale);

private:
	unsigned char m_beforeReceivers[8];
	RenderObjClass *m_primary;
	RenderObjClass *m_secondary;
	unsigned char m_beforeScale[0x60];
	float m_scale;
};

// ?applyScalePayload@BfmeAnimationHolder@@QAEXM@Z
void BfmeAnimationHolder::applyScalePayload(float scale)
{
	RenderObjClass *primary = m_primary;
	if (primary == 0)
		return;

	m_scale = scale;
	Matrix3D transform(primary->Get_Transform());
	const float factor = scale / m_primary->Get_ObjectScale();
	transform.Scale(factor);

	m_primary->Set_ObjectScale(scale);
	m_primary->Set_Transform(transform);
	if (m_secondary != 0)
	{
		m_secondary->Set_ObjectScale(scale);
		m_secondary->Set_Transform(transform);
	}
}
