// ?Get_QuatVector@TimeCodedMotionChannelClass@@QAE?AVQuaternion@@M@Z
// partial score=0.90 date=2026-09-08
Quaternion TimeCodedMotionChannelClass::Get_QuatVector(float32 frame)
{
	assert(VectorLen == 4);
	Quaternion q;
	uint32 tc0 = (uint32)(int)frame;
	uint32 pidx;
	if (tc0 < (Data[CachedIdx] & 0x7FFFFFFF))
	{
		int rightIdx = (int)NumTimeCodes - 2;
		int leftIdx = 0;
		int idx;
		uint32 time;
		for (;;)
		{
			int mid = (leftIdx + rightIdx) / 2;
			idx = mid * (int)PacketSize;
			time = Data[idx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;
			if (tc0 < time) { rightIdx = mid; continue; }
			time = Data[idx + PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;
			if (tc0 < time) { pidx = idx; break; }
			if (leftIdx ^ mid) { leftIdx = mid; continue; }
			leftIdx++;
		}
	}
	else
	{
		pidx = CachedIdx;
	}
	uint32 p2idx;
	if (pidx == ((NumTimeCodes - 1) * PacketSize))
	{
		float32 *vec = (float32 *)&Data[pidx + 1];
		return Quaternion(vec[0], vec[1], vec[2], vec[3]);
	}
	p2idx = pidx + PacketSize;
	uint32 time = Data[p2idx];
	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG)
	{
		float32 *vec = (float32 *)&Data[pidx + 1];
		return Quaternion(vec[0], vec[1], vec[2], vec[3]);
	}
	float32 time1 = (Data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 ratio = (frame - time1) / (time2 - time1);
	float32 *frame1 = (float32 *)&Data[pidx + 1];
	float32 *frame2 = (float32 *)&Data[p2idx + 1];
	Fast_Slerp(q, *(Quaternion *)frame1, *(Quaternion *)frame2, ratio);
	return q;
}
