// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Clean C++ recovery of Add_Rigid_Mesh_To_Container.
//
// The retail MeshModel/DX8FVF ABI differs from the shared BFME headers in
// this body: SortLevel is at MeshModel+0x1c, sorting is at container+0xec,
// and the rigid container is 0x100 bytes.  These TU-local declarations keep
// those independently observed offsets while retaining the real list and
// virtual callees.  The inline derived constructor is important: retail
// inlines its base construction here and then installs the rigid vtable.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp

#include "multilist.h"

class MeshModelClass
{
public:
	enum FlagsType { SORT = 0x10 };

	char m_prefix[0x18];
	int Flags;
	char SortLevel;

	int Get_Flag(FlagsType flag) { return Flags & flag; }
	int Get_Sort_Level(void) const { return SortLevel; }
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	DX8FVFCategoryContainer(unsigned FVF,bool sorting);
	virtual ~DX8FVFCategoryContainer();
	virtual void Render(void);
	virtual void Add_Mesh(MeshModelClass *mmc);
	virtual void Log(bool only_visible);
	virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);
	bool Is_Sorting(void) const { return sorting; }

	unsigned char m_padding[0xe4];
	bool sorting;
	unsigned char m_tail[3];
};

class DX8RigidFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
	DX8RigidFVFCategoryContainer(unsigned FVF,bool sorting_)
		:
		DX8FVFCategoryContainer(FVF,sorting_),
		vertex_buffer(0),
		used_vertices(0),
		delayed_matpass_head(0),
		delayed_matpass_tail(0)
	{
	}

	virtual void Render(void);
	virtual void Add_Mesh(MeshModelClass *mmc);
	virtual void Log(bool only_visible);
	virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);

	void *vertex_buffer;
	int used_vertices;
	void *delayed_matpass_head;
	void *delayed_matpass_tail;
};

class WW3D
{
public:
	static bool IsSortingEnabled;
	static bool Is_Sorting_Enabled(void) { return IsSortingEnabled; }
};

typedef MultiListClass<DX8FVFCategoryContainer> FVFCategoryList;
typedef MultiListIterator<DX8FVFCategoryContainer> FVFCategoryListIterator;

__declspec(noinline) void Add_Rigid_Mesh_To_Container(FVFCategoryList *container_list,unsigned fvf,MeshModelClass *mmc)
{
	WWASSERT(container_list);
	DX8FVFCategoryContainer *container = 0;
	bool sorting=((!!mmc->Get_Flag(MeshModelClass::SORT)) && WW3D::Is_Sorting_Enabled() && (mmc->Get_Sort_Level() == 0));

	FVFCategoryListIterator it(container_list);
	while (!it.Is_Done()) {
		container = it.Peek_Obj();
		if (sorting==container->Is_Sorting() && container->Check_If_Mesh_Fits(mmc)) {
			container->Add_Mesh(mmc);
			return;
		}
		it.Next();
	}

	container=W3DNEW DX8RigidFVFCategoryContainer(fvf,sorting);
	container_list->Add_Tail(container);
	container->Add_Mesh(mmc);
}
