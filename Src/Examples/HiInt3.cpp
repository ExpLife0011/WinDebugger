// �ڴ����в���ϵ�ָ��
//

#include <cstdio>
#include <Windows.h>


int main(int argc, char *argv[])
{
	printf("before int 3.\n");

	// manual breakpoint
	__asm INT 3;
	printf("Hello INT 3!\n");
	
	__asm
	{
		mov eax, eax
		_emit 0xcd         // int 3ָ��
		_emit 0x03		   // ie: 0x013717DC ��(λ�� Example_HiInt3_d.exe ��)�������쳣: 0xC0000005: ��ȡλ�� 0xFFF48B9D ʱ�������ʳ�ͻ��
		nop
		nop
	}

	// or use windows API
	DebugBreak();

	return 0;
}
