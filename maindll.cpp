#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets)
{
	DWORD addr = ptr;
	for (int i = 0; i < offsets.size(); i++)
	{
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
	unsigned basePlayer = 0x00195404;
	unsigned ammoOffset = 0x140;
	unsigned healthOffset = 0xEC;

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("Warmode Infinity Ammo Hack\n");
	printf("key [F1] toggle ammo hack\n");
	printf("key [F2] toggle health hack\n");
	printf("key [end] to stop hack\n");

	Sleep(2000);
	FreeConsole();

	DWORD moduleBase = (DWORD)GetModuleHandle("ac_client.exe");

	bool ammoHackCheat = false;
	bool healthCheat = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_F1))
		{
			if (ammoHackCheat == false) ammoHackCheat = true;
			else ammoHackCheat = false;
		}
		if (GetAsyncKeyState(VK_F2))
		{
			if (healthCheat == false) healthCheat = true;
			else healthCheat = false;
		}
		if (GetAsyncKeyState(VK_END))
		{
			fclose(f);
		}

		if (ammoHackCheat == true)
		{
			int* ammo = (int*)GetPointerAddress(moduleBase + basePlayer, { ammoOffset });
			*ammo = 1000;
		}
		if (healthCheat == true)
		{
			int* health = (int*)GetPointerAddress(moduleBase + basePlayer, { healthOffset });
			*health = 1000;
		}
	}

	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}