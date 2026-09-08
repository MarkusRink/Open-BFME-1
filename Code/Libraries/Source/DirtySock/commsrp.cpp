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
	int CommSRPListen(void *ref, const char *text);
	int CommSRPConnect(void *ref, const char *text);
	int Rva00815680(void *ref, void *packet);
	int Rva00815AB0(void *ref, void *packet);
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void Rva00816910(void *ref);
	void *Rva007FD2D0(int family, int type, int protocol);
	void Rva008154F0(void *ref, void *socket);
	int Rva007FD510(void *socket, const void *address, int length);
	int Rva007FDE80(void *socket, int flags, int interval, void *ref, void *callback);
	void Rva007FD3F0(void *socket);
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
int CommSRPListen(void *ref, const char *text)
{
	int result;
	int bindPort;
	int peerPort;
	unsigned int address;
	char bindAddress[0x10];
	void *socket;
	unsigned int temp;

	if (*(int *)((char *)ref + 0x90) != 0 || *(int *)((char *)ref + 0x7C) != 0) {
		return -2;
	}
	*(unsigned short *)&bindAddress[0] = 2;
	*(unsigned short *)&bindAddress[2] = 0;
	*(unsigned int *)&bindAddress[4] = 0;
	*(unsigned int *)&bindAddress[8] = 0;
	*(unsigned int *)&bindAddress[12] = 0;
	if ((Rva007FFDD0(&address, &bindPort, &peerPort, text) & 2) == 0) {
		return -3;
	}
	bindAddress[2] = (unsigned char)(bindPort >> 8);
	bindAddress[3] = (unsigned char)bindPort;
	Rva00816910(ref);
	socket = Rva007FD2D0(2, 2, 0);
	Rva008154F0(ref, socket);
	if (*(void **)((char *)ref + 0x7C) == 0) {
		return -4;
	}
	result = Rva007FD510(*(void **)((char *)ref + 0x7C), bindAddress, 0x10);
	if (result < 0) {
		Rva007FE780Printf("CommSRPListen: Error %d binding socket\\n", result);
		Rva007FD3F0(*(void **)((char *)ref + 0x7C));
		Rva008154F0(ref, 0);
		return -5;
	}
	Rva007FDE80(*(void **)((char *)ref + 0x7C), 2, 0x64, ref, (void *)0x00C15B50);
	if (address != 0) {
		if (peerPort == 0) {
			peerPort = bindPort + 1;
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
	}
	*(int *)((char *)ref + 0x90) = 2;
	return 0;
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
