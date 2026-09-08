// ?Compute_Ram_Size@MeshMatDescClass@@QAEHXZ
// partial score=0.94 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeThingNH
{
public:
	int bfmeSizeNH(void);

	void Add_Ref(void)
	{
		++m_refs;
	}

	void Release_Ref(void)
	{
		if (--m_refs == 0) {
			void (**vtable)(BfmeThingNH *) = reinterpret_cast<void (**)(BfmeThingNH *)>(this);
			vtable[0](this);
		}
	}

	private:
	void *m_vtable;
	int m_refs;
};

template <class T>
class BfmeBuffer
{
public:
	T **Array(void) const
	{
		return *reinterpret_cast<T ** const *>(reinterpret_cast<const char *>(this) + 8);
	}

	int Count(void) const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x10);
	}
};

class MeshMatDescClass
{
public:
	int Compute_Ram_Size(void);

private:
	int m_pass_count;
	int m_vertex_count;
	int m_poly_count;
	BfmeBuffer<unsigned> *m_uv[8];
	int m_uv_source[4][2];
	BfmeBuffer<unsigned> *m_color_array[2];
	int m_dcg_source[4];
	int m_dig_source[4];
	BfmeThingNH *m_texture[8];
	unsigned m_shader[4];
	BfmeThingNH *m_material[4];
	BfmeBuffer<BfmeThingNH> *m_texture_array[8];
	BfmeBuffer<BfmeThingNH> *m_material_array[4];
	BfmeBuffer<BfmeThingNH> *m_shader_array[4];
};

int MeshMatDescClass::Compute_Ram_Size(void)
{
	const char *object = reinterpret_cast<const char *>(this);
	int size = 0xf4;

#define ADD_SHARED_BUFFER_SIZE(offset, element_size) \
	do { \
		const char *buffer = *reinterpret_cast<const char * const *>(object + offset); \
		if (buffer != 0) { \
			size += *reinterpret_cast<const int *>(buffer + 0x10) * element_size; \
		} \
	} while (0)

	ADD_SHARED_BUFFER_SIZE(0x0c, 8);
	ADD_SHARED_BUFFER_SIZE(0x10, 8);
	ADD_SHARED_BUFFER_SIZE(0x14, 8);
	ADD_SHARED_BUFFER_SIZE(0x18, 8);
	ADD_SHARED_BUFFER_SIZE(0x1c, 8);
	ADD_SHARED_BUFFER_SIZE(0x20, 8);
	ADD_SHARED_BUFFER_SIZE(0x24, 8);
	ADD_SHARED_BUFFER_SIZE(0x28, 8);
	ADD_SHARED_BUFFER_SIZE(0x4c, 4);
	ADD_SHARED_BUFFER_SIZE(0x50, 4);

#undef ADD_SHARED_BUFFER_SIZE

	for (int pass = 0; pass < 4; ++pass) {
		if (m_material[pass] != 0) {
			size += m_material[pass]->bfmeSizeNH();
		}

		if (m_texture_array[pass * 2] != 0) {
			size += m_texture_array[pass * 2]->Count() * 4;
		}

		if (m_texture_array[pass * 2 + 1] != 0) {
			size += m_texture_array[pass * 2 + 1]->Count() * 4;
		}

		if (m_material_array[pass] != 0) {
			size += m_material_array[pass]->Count() * 4;

			for (int index = 0; index < m_material_array[pass]->Count(); ++index) {
				BfmeThingNH *material = m_material_array[pass]->Array()[index];
				if (material != 0) {
					material->Add_Ref();
				}
				if (material != 0) {
					size += material->bfmeSizeNH();
					material->Release_Ref();
				}
			}
		}
	}

	return size;
}
