// ?End_Render@WW3D@@SA?AW4WW3DErrorType@@_N@Z
// partial score=0.95 date=2026-09-08
// Authentic upstream body. With the active WW3D headers this matches 62/65 bytes;
// the sole residue is the final enum ABI return: retail `mov al,1; ret`, MSVC emits
// `mov eax,1; ret`. All calls, globals, branches, and the 65-byte boundary match.
WW3DErrorType WW3D::End_Render(bool flip_frame)
{
	if (!IsInitted) {
		return WW3D_ERROR_GENERIC;
	}

	SortingRendererClass::Flush();
	IsRendering = false;
	DX8Wrapper::End_Scene(flip_frame);
	FrameCount++;
	Debug_Statistics::End_Statistics();
	Activate_Snapshot(false);
	DX8Wrapper::Invalidate_Cached_Render_States();
	return WW3D_ERROR_GENERIC;
}
