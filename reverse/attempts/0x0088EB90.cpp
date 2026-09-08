// ?DebugReAllocMemory@@YAPAXPAXI@Z
// partial score=0.87 date=2026-09-08
// Probed with /D_INTERNAL: 174 bytes versus retail's 188. The allocator
// control flow matches, but DCRASH_RELEASE expands to a different debug
// call sequence and changes the branch offsets.

#include "_pch.h"

void *DebugReAllocMemory(void *oldPtr, unsigned newSize)
{
  if (!oldPtr)
    return newSize ? DebugAllocMemory(newSize) : 0;

  if (!newSize)
  {
    GlobalFree((HGLOBAL)oldPtr);
    return 0;
  }

  HGLOBAL h = GlobalReAlloc((HGLOBAL)oldPtr, newSize, 0);
  if (!h)
  {
    h = GlobalAlloc(GMEM_FIXED, newSize);
    if (!h)
      DCRASH_RELEASE("Debug mem realloc failed");
    unsigned oldSize = GlobalSize((HGLOBAL)oldPtr);
    memcpy((void *)h, oldPtr, oldSize < newSize ? oldSize : newSize);
    GlobalFree((HGLOBAL)oldPtr);
  }

  return (void *)h;
}
