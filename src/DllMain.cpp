#include "Memory.h"
#include "hooks.h"
//#include "Hooks_DummyDeviceMethod.h"

Memory memory;
Hooks hooks;
//Hooks_DummyDevice Hooks_DumDev;

//void STDMETHODCALLTYPE gameoverlayrenderer_imgui_dx9_init() {
//	
//	AllocConsole();
//	freopen("CONOUT$", "w", stdout);
//	std::cout << "originalPresent: "	<< hooks.originalPresent	<< std::endl;
//	std::cout << "originalReset: "		<< hooks.originalReset		<< std::endl;
//	std::cout << "originalWndProc: "	<< hooks.originalWndProc	<< std::endl;
//
//}
//
//BOOL WINAPI DllMain(HINSTANCE dll_instance, DWORD call_reason, LPVOID reserved) {
//	DisableThreadLibraryCalls(dll_instance);
//
//	if (call_reason == DLL_PROCESS_ATTACH)
//		CreateThread(0, 0, LPTHREAD_START_ROUTINE(gameoverlayrenderer_imgui_dx9_init), 0, 0, 0);
//
//	return TRUE;
//}
