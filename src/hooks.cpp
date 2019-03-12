#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "hooks.h"
#include "Memory.h"
//#include "Memory_DummyDeviceMethod.h"

extern IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// The original WndProc used by the game window.
WNDPROC game_wndproc = NULL;

FORCEINLINE void draw_interface() {
	ImGui::Text("Hello world from the Steam Overlay!");

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("FPS", nullptr, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	ImGui::End();
}

LRESULT STDMETHODCALLTYPE hookedWndProc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param);

	return CallWindowProc(hooks.originalWndProc, window, message_type, w_param, l_param);
};

static LRESULT STDMETHODCALLTYPE hookedPresent(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region) {
	
	static bool is_initialised = false;

	if (!is_initialised) {

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA("Valve001", NULL));
		ImGui_ImplDX9_Init(device);

		hooks.originalWndProc = reinterpret_cast<WNDPROC>(
			SetWindowLongPtr(FindWindowA("Valve001", NULL), GWLP_WNDPROC, LONG_PTR(hookedWndProc))
			);
		is_initialised = true;
	}
	else {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		draw_interface();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	return hooks.originalPresent(device, src, dest, wnd_override, dirty_region);
}

static LRESULT STDMETHODCALLTYPE hookedReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto result = hooks.originalReset(device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return hooks.originalReset(device, params);
}

#ifdef _MEMORY_DD_METHOD_H_
Hooks::Hooks() {
	originalPresent = **reinterpret_cast<decltype(&originalPresent)*>(memory_DD.present);
	**reinterpret_cast<void***>(memory_DD.present) = reinterpret_cast<void*>(&hookedPresent);

	originalReset = **reinterpret_cast<decltype(&originalReset)*>(memory_DD.reset);
	**reinterpret_cast<void***>(memory_DD.reset) = reinterpret_cast<void*>(&hookedReset);
}
#else
Hooks::Hooks() {
	originalPresent = **reinterpret_cast<decltype(&originalPresent)*>(memory.present);
	**reinterpret_cast<void***>(memory.present) = reinterpret_cast<void*>(&hookedPresent);

	originalReset = **reinterpret_cast<decltype(&originalReset)*>(memory.reset);
	**reinterpret_cast<void***>(memory.reset) = reinterpret_cast<void*>(&hookedReset);
}
#endif



