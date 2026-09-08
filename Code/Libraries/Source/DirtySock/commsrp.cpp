// cl: /DNDEBUG /MD /GX /Od /GZ /GS

#define _DLL
#include <string.h>

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int CommSRPResolve();
	int CommSRPSend(void *ref, const void *buffer, int length, int flags);
	int CommSRPListen();
	int CommSRPConnect(void *ref, const char *text);
	int Rva00815680(void *ref, void *packet);
	int Rva00815AB0(void *ref, void *packet);
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void Rva00816910(void *ref);
	void *Rva007FD2D0(int family, int type, int protocol);
	void Rva008154F0(void *ref, void *socket);
	int Rva007FD510(void *socket, const void *address, int length);
	int Rva007FDE80(void *socket, int flags, int interval, void *ref, void *callback);
}

int Rva007FE780Printf(const char *format, ...);

// Always fails: "Resolve functionality not supported by CommSRP".
int CommSRPResolve()
{
	Rva007FE780Printf("Resolve functionality not supported by CommSRP\n");
	return -1;
}

// Queues an outbound packet. Reports "CommSRPSend: input queue full" and
// "CommSRP: Oversized packet send (%d bytes)".
int CommSRPSend(void *ref, const void *buffer, int length, int flags)
{
	char *packet;
	int queued;

	if (*(int *)((char *)ref + 0x90) != 3) {
		return -2;
	}
	if ((*(int *)((char *)ref + 0xB8) + *(int *)((char *)ref + 0xB0)) %
	        *(int *)((char *)ref + 0xB4) == *(int *)((char *)ref + 0xBC)) {
		Rva007FE780Printf("CommSRPSend: input queue full\n");
		return 0;
	}
	if (length > *(int *)((char *)ref + 0xB0) - 0x0B) {
		Rva007FE780Printf("CommSRP: Oversized packet send (%d bytes)\n", length);
		return -6;
	}
	if (length == 0) {
		queued = ((*(int *)((char *)ref + 0xB8) + *(int *)((char *)ref + 0xB4) -
		           *(int *)((char *)ref + 0xBC)) % *(int *)((char *)ref + 0xB4)) /
		         *(int *)((char *)ref + 0xB0);
		return queued + 1;
	}
	packet = *(char **)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8);
	*(int *)(packet + 4) = length;
	memcpy(packet + 9, buffer, length);
	if ((flags & 1) != 0) {
		*(unsigned char *)(packet + 8) =
			(unsigned char)*(int *)((char *)ref + 0xCC) + 0x40;
		++*(int *)((char *)ref + 0xCC);
		*(int *)((char *)ref + 0xCC) &= 0x3F;
		queued = Rva00815680(ref, packet);
		if (queued > 0) {
			queued = 1;
		}
	} else {
		*(unsigned char *)(packet + 8) =
			(unsigned char)*(int *)((char *)ref + 0xD4) + 0x80;
		++*(int *)((char *)ref + 0xD4);
		*(int *)((char *)ref + 0xD4) &= 0x3F;
		queued = Rva00815AB0(ref, packet);
	}
	return queued > 0 ? queued : 1;
}

// Binds and listens, logging "CommSRPListen: Error %d binding socket".
__declspec(naked) int CommSRPListen()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		push edi
		lea edi,  [ebp-4Ch]
		mov ecx, 13h
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 0h
		jne L00_816693
		mov ecx, dword ptr [ebp+8h]
		cmp dword ptr [ecx+7Ch], 0h
		je L01_81669D
L00_816693:
		mov eax, 0FFFFFFFEh
		jmp L02_816879
L01_81669D:
		mov word ptr [ebp-40h], 2h
		mov word ptr [ebp-3Eh], 0h
		mov dword ptr [ebp-3Ch], 0h
		mov dword ptr [ebp-38h], 0h
		mov dword ptr [ebp-34h], 0h
		mov edx, dword ptr [ebp+0Ch]
		push edx
		lea eax,  [ebp-1Ch]
		push eax
		lea ecx,  [ebp-10h]
		push ecx
		lea edx,  [ebp-28h]
		push edx
		__emit 0E8h
		__emit 0FDh
		__emit 096h
		__emit 0FEh
		__emit 0FFh   // call 0x7FFDD0
		add esp, 10h
		and eax, 2h
		jne L03_8166E5
		mov eax, 0FFFFFFFDh
		jmp L02_816879
L03_8166E5:
		mov eax, dword ptr [ebp-10h]
		sar eax, 8h
		mov byte ptr [ebp-3Eh], al
		mov cl, byte ptr [ebp-10h]
		mov byte ptr [ebp-3Dh], cl
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 013h
		__emit 002h
		__emit 000h
		__emit 000h   // call 0x816910
		add esp, 4h
		push 0h
		push 2h
		push 2h
		__emit 0E8h
		__emit 0C5h
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD2D0
		add esp, 0Ch
		mov dword ptr [ebp-48h], eax
		mov eax, dword ptr [ebp-48h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 0D2h
		__emit 0EDh
		__emit 0FFh
		__emit 0FFh   // call 0x8154F0
		add esp, 8h
		mov edx, dword ptr [ebp+8h]
		cmp dword ptr [edx+7Ch], 0h
		jne L04_816734
		mov eax, 0FFFFFFFCh
		jmp L02_816879
L04_816734:
		push 10h
		lea eax,  [ebp-40h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+7Ch]
		push edx
		__emit 0E8h
		__emit 0CAh
		__emit 06Dh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD510
		add esp, 0Ch
		mov dword ptr [ebp-8h], eax
		cmp dword ptr [ebp-8h], 0h
		jge L05_81678A
		mov eax, dword ptr [ebp-8h]
		push eax
		push 12C4CF4h
		__emit 0E8h
		__emit 020h
		__emit 080h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+7Ch]
		push edx
		__emit 0E8h
		__emit 081h
		__emit 06Ch
		__emit 0FEh
		__emit 0FFh   // call 0x7FD3F0
		add esp, 4h
		push 0h
		mov eax, dword ptr [ebp+8h]
		push eax
		__emit 0E8h
		__emit 073h
		__emit 0EDh
		__emit 0FFh
		__emit 0FFh   // call 0x8154F0
		add esp, 8h
		mov eax, 0FFFFFFFBh
		jmp L02_816879
L05_81678A:
		push 0C15B50h
		mov ecx, dword ptr [ebp+8h]
		push ecx
		push 64h
		push 2h
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+7Ch]
		push eax
		__emit 0E8h
		__emit 0DDh
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FDE80
		add esp, 14h
		cmp dword ptr [ebp-28h], 0h
		je L06_81686A
		cmp dword ptr [ebp-1Ch], 0h
		jne L07_8167BF
		mov ecx, dword ptr [ebp-10h]
		add ecx, 1h
		mov dword ptr [ebp-1Ch], ecx
L07_8167BF:
		mov edx, dword ptr [ebp+8h]
		mov word ptr [edx+80h], 2h
		mov eax, dword ptr [ebp+8h]
		mov word ptr [eax+82h], 0h
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+84h], 0h
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+88h], 0h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+8Ch], 0h
		mov ecx, dword ptr [ebp-28h]
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+87h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+86h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+85h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+84h], al
		mov ecx, dword ptr [ebp-1Ch]
		sar ecx, 8h
		mov edx, dword ptr [ebp+8h]
		mov byte ptr [edx+82h], cl
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-1Ch]
		mov byte ptr [eax+83h], cl
L06_81686A:
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+90h], 2h
		xor eax, eax
L02_816879:
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 0A1h
		__emit 068h
		__emit 0C1h
		__emit 000h   // lea edx, [0xc168a1]
		__emit 0E8h
		__emit 09Dh
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 062h
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 4Ch
		cmp ebp, esp
		__emit 0E8h
		__emit 065h
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Connects out, logging "CommSRPConnect: Error %d binding socket".

int CommSRPConnect(void *ref, const char *text)
{
	char socketAddress[0x10];
	int result;
	int peerPort;
	int bindPort;
	unsigned int address;
	void *socket;
	unsigned int temp;

	if (*(int *)((char *)ref + 0x90) != 0 || *(int *)((char *)ref + 0x7C) != 0) {
		return -2;
	}
	if ((Rva007FFDD0(&address, &bindPort, &peerPort, text) & 3) != 3) {
		return -3;
	}
	if (peerPort == 0) {
		peerPort = bindPort;
		++bindPort;
	}
	Rva00816910(ref);
	socket = Rva007FD2D0(2, 2, 0);
	Rva008154F0(ref, socket);
	if (*(void **)((char *)ref + 0x7C) == 0) {
		return -4;
	}
	*(unsigned short *)&socketAddress[0] = 2;
	*(unsigned short *)&socketAddress[2] = 0;
	*(unsigned int *)&socketAddress[4] = 0;
	*(unsigned int *)&socketAddress[8] = 0;
	*(unsigned int *)&socketAddress[12] = 0;
	socketAddress[2] = (unsigned char)(bindPort >> 8);
	socketAddress[3] = (unsigned char)bindPort;
	result = Rva007FD510(*(void **)((char *)ref + 0x7C), socketAddress, 0x10);
	if (result < 0) {
		Rva007FE780Printf("CommSRPConnect: Error %d binding socket\n", result);
		return -5;
	}
	*(unsigned short *)((char *)ref + 0x80) = 2;
	*(unsigned short *)((char *)ref + 0x82) = 0;
	*(unsigned int *)((char *)ref + 0x84) = 0;
	*(unsigned int *)((char *)ref + 0x88) = 0;
	*(unsigned int *)((char *)ref + 0x8C) = 0;
	temp = address;
	*((unsigned char *)ref + 0x87) = (unsigned char)temp; temp >>= 8;
	*((unsigned char *)ref + 0x86) = (unsigned char)temp; temp >>= 8;
	*((unsigned char *)ref + 0x85) = (unsigned char)temp; temp >>= 8;
	*((unsigned char *)ref + 0x84) = (unsigned char)temp;
	*((unsigned char *)ref + 0x82) = (unsigned char)(peerPort >> 8);
	*((unsigned char *)ref + 0x83) = (unsigned char)peerPort;
	Rva007FDE80(*(void **)((char *)ref + 0x7C), 2, 0x64, ref, (void *)0x00C15B50);
	*(int *)((char *)ref + 0x90) = 1;
	return 0;
}
