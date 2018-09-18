// \brief
//		helper functions
//

#include "AppHelper.h"

// string
TCHAR* appStrncpy(TCHAR *Dest, const TCHAR *Src, int32_t MaxLen)
{
	assert(MaxLen > 0);
	_tcsncpy(Dest, Src, MaxLen - 1);
	Dest[MaxLen - 1] = 0;
	return Dest;
}

// console 
void appSetConsoleTitle(const TCHAR *InTitle)
{
	::SetConsoleTitle(InTitle);
}

void appClearConsoleScreen()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get the number of character cells in the current buffer. 
	if (!GetConsoleScreenBufferInfo(OutputHandle, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(OutputHandle,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(OutputHandle, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(OutputHandle,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(OutputHandle, coordScreen);
}

COORD appGetConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(OutputHandle, &csbi);
	return csbi.dwCursorPosition;
}

void appSetConsoleCursorPosition(const COORD &InPos)
{
	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(OutputHandle, InPos);
}

void appSetConsoleTextColor(const TCHAR *InColor)
{
	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!InColor || appStricmp(InColor, TEXT("")) == 0)
	{
		SetConsoleTextAttribute(OutputHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else
	{
		TCHAR String[9];
		appStrncpy(String, InColor, XARRAY_COUNT(String));
		for (TCHAR *S = String; *S; S++)
		{
			*S -= TEXT('0');
		}
		SetConsoleTextAttribute(OutputHandle,
			(String[0] ? FOREGROUND_RED   : 0) |
			(String[1] ? FOREGROUND_GREEN : 0) |
			(String[2] ? FOREGROUND_BLUE  : 0) |
			(String[3] ? FOREGROUND_INTENSITY : 0) |
			(String[4] ? BACKGROUND_RED   : 0) |
			(String[5] ? BACKGROUND_GREEN : 0) |
			(String[6] ? BACKGROUND_BLUE  : 0) |
			(String[7] ? BACKGROUND_INTENSITY : 0)
			);
	}
}

void appConsolePrintf(const TCHAR *InFormat, ...)
{
	va_list args;
	va_start(args, InFormat);
	_vtprintf_p(InFormat, args);
	va_end(args);
}

TCHAR* appGetConsoleLine(TCHAR *OutLine, size_t SizeInCharacters)
{
	assert(OutLine);

	return _getts_s(OutLine, SizeInCharacters);
}
