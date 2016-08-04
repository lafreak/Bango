#include "CSocket.h"

char* CSocket::WriteV(char* packet, va_list va)
{
	char* format = va_arg(va, char*);

	for ( ; ; ) {
		switch (*format++) {

		case 'b':
		case 'B':
			*packet++ = va_arg(va, int);
			break;
		case 'w':
		case 'W':
			*(WORD *)packet = va_arg(va, int);
			packet += sizeof(WORD);
			break;
		case 'd':
			*(DWORD *)packet = va_arg(va, DWORD);
			packet += sizeof(DWORD);
			break;
		case 'U':
			*(UINT *)packet = va_arg(va, UINT);
			packet += sizeof(UINT);
			break;
		case 'I':	//	__int64
			*(__int64 *)packet = va_arg(va, __int64);
			packet += sizeof(__int64);
			break;
		case 's':
		case 'S':
			{
				char *str = va_arg(va, char *);
				if (str == 0 || *str == 0) {
					*packet++ = 0;
					break;
				}
				for ( ; (*packet++ = *str++ ) != 0 ; )
					;
			}
			break;
		case 'm':
		case 'M':
			{
				char *ptr = va_arg(va, char *);
				int	size = va_arg(va, int);
				memcpy(packet, ptr, size);
				packet += size;
			}
			break;
		case 0:
		default:
			return packet;
		}
	}

	return packet;
}

char* CSocket::ReadPacket(char* packet, const char* format, ...)
{
	va_list va;
	va_start(va, format);

	char byArgNum = strlen(format);
	for (char i = 0; i < byArgNum; i++)
	{
		switch (format[i])
		{
		case 'b':
			*va_arg(va, char*) = *packet;
			packet++;
			break;
		case 'd':
			*va_arg(va, DWORD*) = *(DWORD*)packet;
			packet += sizeof(DWORD);
			break;
		case 'w':
			*va_arg(va, WORD*) = *(WORD*)packet;
			packet += sizeof(WORD);
			break;
		case 'U':
			*va_arg(va, UINT*) = *(UINT*)packet;
			packet += sizeof(UINT);
			break;
		case 'I':
			*va_arg(va, __int64*) = *(__int64*)packet;
			packet += sizeof(__int64);
			break;
		case 's':
			{
                // ą®ŔÚŔÇ ÁÖĽŇ¸¦ ŔúŔĺÇŃ´Ů.
                char *text = *va_arg(va, char**) = packet;
                //packet += sizeof(char*);

                // ą®ŔÚ´Â şńżöÁŘ´Ů.
                while (*packet++) {}
            }
            break;
		case 0:
		default:
			return packet;
		}
	}

	va_end(va);
	return packet;
}
