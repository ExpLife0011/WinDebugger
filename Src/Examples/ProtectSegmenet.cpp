// Ӧ�ó��������Ч�μĴ��������쳣

#include <cstdio>

int main(int argc, char *argv[])
{
	printf("modify data segment register.\n");

	__asm
	{
		mov bx, 25
		mov ds, bx
	}

	printf("never run to here.\n");

	return 0;
}
