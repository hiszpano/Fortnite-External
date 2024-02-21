#include <Windows.h>
#include <iostream>

namespace librarys
{
	HMODULE user32;
	HMODULE win32u;
	bool init()
	{
		HMODULE user32_lib = LoadLibraryA("user32.dll");
		if (!user32_lib) {
			std::cout << "user32_lib\n";
			return false;
		}
		HMODULE win32u_lib = LoadLibraryA("win32u.dll");
		if (!win32u_lib) {
			std::cout << "win32u_lib\n";
			return false;
		}

		user32 = GetModuleHandleA("user32.dll");
		if (!user32) {
			std::cout << "user32.dll\n";
			return false;
		}
		win32u = GetModuleHandleA("win32u.dll");
		if (!win32u) {
			std::cout << "win32u\n";
			return false;
		}
		return true;
	}
}
