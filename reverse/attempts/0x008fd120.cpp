// ?Set_Render_Device@WW3D@@SA?AW4WW3DErrorType@@HHHHH_N00@Z
// partial score=0.94 date=2026-09-08
// Authentic WW3D wrapper semantics. This matches the entire call setup and target;
// only the final bool-to-enum normalization differs: retail `test al; setne al`,
// while MSVC emits either `movzx eax,al` or `neg/sbb/neg` for this return type.
WW3DErrorType WW3D::Set_Render_Device(int dev, int width, int height, int bits,
	int windowed, bool resize_window, bool reset_device, bool restore_assets)
{
	bool success = DX8Wrapper::Set_Render_Device(dev, width, height, bits, windowed,
		resize_window, reset_device, restore_assets);
	if (success) {
		return WW3D_ERROR_GENERIC;
	} else {
		return WW3D_ERROR_OK;
	}
}
