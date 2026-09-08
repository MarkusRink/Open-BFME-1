// ?Rva007397E0Forward@@YAEPAXIII@Z
// partial score=0.98 date=2026-09-08
// Retail 0x007397E0 walks a RenderObjClass tree and sets emissive material color.
// The local declarations keep the BFME vtable and ref-count layouts explicit.

class VertexMaterialClass
{
public:
	virtual void Delete_This(void);
	int m_refs;

	void Add_Ref(void)
	{
		++m_refs;
	}

	void Set_Emissive(float red, float green, float blue);

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	int m_refs;
	int m_vector_vtable;
	VertexMaterialClass **m_vector;
	int m_vector_max;
	int m_vector_flags;
	int m_active_count;

	int Vertex_Material_Count(void) const
	{
		return m_active_count;
	}

	VertexMaterialClass *Get_Vertex_Material(int index)
	{
		if (m_vector[index])
			m_vector[index]->Add_Ref();
		return m_vector[index];
	}

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual int Get_Num_Sub_Objects(void) const;
	virtual void v28(void);
	virtual void *Get_Sub_Object(int index) const;
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual void v66(void);
	virtual void v67(void);
	virtual void v68(void);
	virtual void v69(void);
	virtual void v70(void);
	virtual void v71(void);
	virtual void v72(void);
	virtual void v73(void);
	virtual void v74(void);
	virtual void v75(void);
	virtual void v76(void);
	virtual void v77(void);
	virtual void v78(void);
	virtual void v79(void);
	virtual void v80(void);
	virtual void v81(void);
	virtual void v82(void);
	virtual void v83(void);
	virtual MaterialInfoClass *Get_Material_Info(void);

	int m_refs;

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

typedef bool (*EmissiveForward)(void *, unsigned int, unsigned int, unsigned int);
extern bool Rva007397E0Thunk(void *, volatile unsigned int, volatile unsigned int, volatile unsigned int);

unsigned char Rva007397E0Forward(register void *object, volatile unsigned int red, volatile unsigned int green, volatile unsigned int blue)
{
	RenderObjClass *robj = (RenderObjClass *)object;
	if (!robj)
		return false;

	register unsigned char result = 0;
	MaterialInfoClass *material_info = robj->Get_Material_Info();
	if (material_info)
	{
		for (int index = 0; index < material_info->Vertex_Material_Count(); ++index)
		{
			VertexMaterialClass *material = material_info->Get_Vertex_Material(index);
			if (material)
			{
				material->Set_Emissive(*(float *)&red, *(float *)&green, *(float *)&blue);
				material->Release_Ref();
				result = true;
			}
		}
		material_info->Release_Ref();
		return result;
	}

	int count = robj->Get_Num_Sub_Objects();
	for (int index = 0; index < count; ++index)
	{
		void *sub_object;
		EmissiveForward forward = Rva007397E0Thunk;
		const bool child = forward(sub_object = robj->Get_Sub_Object(index), red, green, blue);
		if (result || child)
			result = 1;
		if (sub_object)
			((RenderObjClass *)sub_object)->Release_Ref();
	}
	return result;
}
