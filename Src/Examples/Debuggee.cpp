// WinDebugger��������
//

#include <cstdio>
#include <Windows.h>


#define VAR_WATCH() printf("nDividend=%d, nDivisor=%d, nResult=%d.\n", nDividend, nDivisor, nResult)

int main(int argc, char *argv[])
{
	int nDividend = 22, nResult = 100;
	int nDivisor = 0;

	__try
	{
		printf("Before div in __try block:");
		VAR_WATCH();

		// nResult = nDividend / nDivisor;
		__asm
		{
			mov eax, nDividend
			cdq
			idiv nDivisor
			mov nResult, eax
		};

		printf("After div in __try block:");
		VAR_WATCH();
	}
	__except (printf("In __except block:"), VAR_WATCH(),
		GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ?
		(nDivisor = 1, printf("Divide Zero exception detected:"), VAR_WATCH(), EXCEPTION_CONTINUE_EXECUTION) // �������쳣����, �������ָ�ִ��
		: EXCEPTION_CONTINUE_SEARCH) // ���������쳣����
	{
		printf("In handler block. Never execute me.\n"); // EXCEPTION_EXECUTE_HANDLER
	}

	getchar(); // pause.
	return 0;
}
