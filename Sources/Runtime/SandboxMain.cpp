#include <windows.h>

INT APIENTRY wWinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPWSTR,
	_In_ INT
)
{
	return MessageBox(
		nullptr,
		TEXT("Hello, World!"),
		TEXT("Sandbox Engine"),
		0
	);
}