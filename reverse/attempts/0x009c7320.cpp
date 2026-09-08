// ?bfmeBlendRowsFB@@YAXPBEPAEHHHHPBT__m128i@@@Z
// partial score=0.70 date=2026-09-08
#include <emmintrin.h>

extern "C" const __m128i g_bfmeRoundFB;

void bfmeBlendRowsFB(const unsigned char *src, unsigned char *dst, int srcPitch,
	int unused, int rows, int dstPitch, const __m128i *w)
{
	__m128i w0 = w[0];
	__m128i w1 = w[1];
	__m128i zero = _mm_setzero_si128();

	do
	{
		_mm_storeu_si128((__m128i *)dst,
			_mm_srai_epi16(
				_mm_add_epi16(
					_mm_add_epi16(
						_mm_mullo_epi16(_mm_unpacklo_epi8(_mm_loadu_si128((const __m128i *)src), zero), w0),
						_mm_mullo_epi16(_mm_unpacklo_epi8(_mm_loadu_si128((const __m128i *)(src + srcPitch)), zero), w1)),
					g_bfmeRoundFB),
				7));

		src += srcPitch;
		dst += dstPitch;
	}
	while (--rows);
}
