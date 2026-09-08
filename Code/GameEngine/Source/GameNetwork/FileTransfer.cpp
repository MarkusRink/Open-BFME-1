// cl: /DNDEBUG /MD /GX

// The _art and _pic preview path builders are BFME additions with no ZH
// counterpart; their names follow the format strings they build.

extern "C" {
	int doFileTransfer(void *filename, void *ls, int mask);
}

// Builds "%s\\map.ini" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
// Builds "%s\\map.str" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
// Builds "%s\\solo.ini" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
// Builds "%s\\assetusage.txt" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
// Retail's name, from the ZH reference where this is the file-scope static that
// DoAnyMapTransfers drives. It pushes the file out in chunks, reporting through
// MapTransferLoadScreen with the "MapTransfer:Preparing", "MapTransfer:Sending",
// "MapTransfer:Recieving" and "MapTransfer:Done" state strings, and calls
// processTimeout while it waits. Ghidra sizes it 811, three short of its ret.
__declspec(naked) int doFileTransfer(void *filename, void *ls, int mask)
{
	__asm {
		push 0FFFFFFFFh
		push 1044868h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 3Ch
		push ebx
		push ebp
		push esi
		push edi
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		__emit 08Bh
		__emit 02Dh
		__emit 06Ch
		__emit 049h
		__emit 02Fh
		__emit 001h   // mov ebp, dword ptr [0x12f496c]
		xor ebx, ebx
		cmp ecx, ebx
		mov dword ptr [esp+54h], ebx
		je L00_66CE9D
		mov eax, dword ptr [ecx]
		call dword ptr [eax+68h]
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
L00_66CE9D:
		mov edi, dword ptr [esp+60h]
		cmp edi, ebx
		je L01_66D131
		lea ecx,  [esp+5Ch]
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 063h
		__emit 035h
		__emit 09Ch
		__emit 0FFh   // call 0x30418
		__emit 08Bh
		__emit 035h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x1359544]
		call esi
		push 258h
		mov ecx, ebp
		mov dword ptr [esp+2Ch], eax
		__emit 0E8h
		__emit 0ECh
		__emit 093h
		__emit 09Ch
		__emit 0FFh   // call 0x362B9
		push ebx
		mov ecx, ebp
		__emit 0E8h
		__emit 037h
		__emit 08Eh
		__emit 09Ah
		__emit 0FFh   // call 0x15D0C
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+18h], ebx
		mov byte ptr [esp+12h], 0h
		call dword ptr [edx+10h]
		test al, al
		je L02_66CF1B
		push 1F4h
		__emit 0FFh
		__emit 015h
		__emit 030h
		__emit 08Fh
		__emit 035h
		__emit 001h   // call dword ptr [0x1358f30]
		push edi
		push ecx
		lea eax,  [esp+64h]
		mov dword ptr [esp+2Ch], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 056h
		__emit 0ACh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+5Ch]
		mov dword ptr [esp+18h], eax
		jmp L03_66CF20
L02_66CF1B:
		mov byte ptr [esp+12h], 1h
L03_66CF20:
		xor eax, eax
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+30h], eax
		mov dword ptr [esp+34h], eax
		mov dword ptr [esp+38h], eax
		mov dword ptr [esp+3Ch], eax
		mov dword ptr [esp+40h], eax
		mov dword ptr [esp+44h], eax
		mov dword ptr [esp+48h], eax
		call esi
		mov esi, 1h
		mov dword ptr [esp+14h], eax
		mov dword ptr [esp+1Ch], esi
		jmp L04_66CF60
L21_66CF53:
		mov esi, dword ptr [esp+1Ch]
		mov edi, dword ptr [esp+60h]
		jmp L04_66CF60
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L04_66CF60:
		mov al, byte ptr [esp+12h]
		test al, al
		jne L05_66CFA6
		mov eax, 1h
		mov ecx, esi
		shl eax, cl
		and eax, edi
		je L06_66CF97
		mov ecx, dword ptr [esp+18h]
		push ecx
		push eax
		push ecx
		lea edx,  [esp+68h]
		mov dword ptr [esp+30h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 0D4h
		__emit 0ABh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+58h]
L06_66CF97:
		inc esi
		cmp esi, 8h
		mov dword ptr [esp+1Ch], esi
		jne L05_66CFA6
		mov byte ptr [esp+12h], 1h
L05_66CFA6:
		mov ebx, 64h
		mov byte ptr [esp+13h], 1h
		mov dword ptr [esp+20h], ebx
		mov esi, 1h
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L13_66CFC0:
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 094h
		__emit 0C4h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov ecx, eax
		__emit 0E8h
		__emit 0F8h
		__emit 0A9h
		__emit 09Bh
		__emit 0FFh   // call 0x279CB
		test al, al
		je L07_66D07A
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 079h
		__emit 0C4h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov cl, byte ptr [eax+9h]
		test cl, cl
		jne L07_66D07A
		push ecx
		lea edx,  [esp+60h]
		mov dword ptr [esp+28h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 05Dh
		__emit 0ABh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov eax, dword ptr [ecx]
		push esi
		call dword ptr [eax+60h]
		mov edi, eax
		cmp ebx, edi
		mov dword ptr [esp+24h], edi
		lea eax,  [esp+20h]
		jl L08_66D021
		lea eax,  [esp+24h]
L08_66D021:
		mov ebx, dword ptr [eax]
		cmp edi, dword ptr [esp+esi*4+2Ch]
		mov dword ptr [esp+20h], ebx
		je L07_66D07A
		test edi, edi
		__emit 08Bh
		__emit 00Dh
		__emit 07Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f147c]
		mov edx, dword ptr [ecx]
		push ecx
		mov dword ptr [esp+28h], esp
		mov eax, esp
		push 0h
		jne L09_66D04E
		push 111A318h
		push eax
		call dword ptr [edx+28h]
		push edi
		jmp L10_66D064
L09_66D04E:
		cmp edi, 64h
		jge L11_66D05A
		push 111A2FCh
		jmp L12_66D05F
L11_66D05A:
		push 111A2E8h
L12_66D05F:
		push eax
		call dword ptr [edx+28h]
		push edi
L10_66D064:
		mov ecx, ebp
		push esi
		__emit 0E8h
		__emit 0FDh
		__emit 060h
		__emit 09Bh
		__emit 0FFh   // call 0x23169
		mov dword ptr [esp+esi*4+2Ch], edi
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esp+14h], eax
L07_66D07A:
		inc esi
		cmp esi, 8h
		jl L13_66CFC0
		cmp ebx, 64h
		__emit 08Bh
		__emit 00Dh
		__emit 07Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f147c]
		mov edx, dword ptr [ecx]
		push ecx
		mov eax, esp
		mov dword ptr [esp+28h], esp
		push 0h
		jge L14_66D0B6
		test ebx, ebx
		mov byte ptr [esp+1Bh], 0h
		jne L15_66D0AF
		push 111A318h
		push eax
		call dword ptr [edx+28h]
		push ebx
		jmp L16_66D0C0
L15_66D0AF:
		push 111A2D0h
		jmp L17_66D0BB
L14_66D0B6:
		push 111A2E8h
L17_66D0BB:
		push eax
		call dword ptr [edx+28h]
		push ebx
L16_66D0C0:
		mov ecx, ebp
		push 0h
		__emit 0E8h
		__emit 0A0h
		__emit 060h
		__emit 09Bh
		__emit 0FFh   // call 0x23169
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		test ebx, ebx
		je L18_66D0E1
		mov ecx, dword ptr [esp+14h]
		add ecx, 7530h
		cmp eax, ecx
		jmp L19_66D0ED
L18_66D0E1:
		mov edx, dword ptr [esp+14h]
		add edx, 1D4C0h
		cmp eax, edx
L19_66D0ED:
		jg L20_66D160
		mov ecx, dword ptr [esp+28h]
		lea edx,  [ecx+927C0h]
		cmp eax, edx
		ja L20_66D160
		sub ecx, eax
		add ecx, 927C0h
		mov eax, 10624DD3h
		mul ecx
		shr edx, 6h
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 0A2h
		__emit 091h
		__emit 09Ch
		__emit 0FFh   // call 0x362B9
		push ebx
		mov ecx, ebp
		__emit 0E8h
		__emit 0EDh
		__emit 08Bh
		__emit 09Ah
		__emit 0FFh   // call 0x15D0C
		mov al, byte ptr [esp+13h]
		test al, al
		je L21_66CF53
L23_66D12B:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
L01_66D131:
		test ecx, ecx
		je L22_66D13A
		mov eax, dword ptr [ecx]
		call dword ptr [eax+6Ch]
L22_66D13A:
		lea ecx,  [esp+5Ch]
		mov dword ptr [esp+54h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0F5h
		__emit 0A7h
		__emit 021h
		__emit 000h   // call 0x887940
		mov al, 1h
		mov ecx, dword ptr [esp+4Ch]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 48h
		ret
L20_66D160:
		mov al, byte ptr [esp+13h]
		test al, al
		jne L23_66D12B
		lea ecx,  [esp+5Ch]
		mov dword ptr [esp+54h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0C7h
		__emit 0A7h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+4Ch]
		pop edi
		pop esi
		pop ebp
		xor al, al
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 48h
		ret
	}
}

// The part of a path after the last separator. First of the three helpers
// GetPreviewFromMap calls, matching the ZH reference's
// GetBaseFileFromFile(GetFileFromPath(path)) nesting. BFME's version tests for
// '.' as well as '\\', which the reference does not.
// A filename with its extension removed: reverseFind('.'), then copy the prefix
// through getBufferForRead. Second of GetPreviewFromMap's three calls.
// A path with its filename removed: reverseFind('\\'), then copy the prefix
// through getBufferForRead. Third of GetPreviewFromMap's three calls.
