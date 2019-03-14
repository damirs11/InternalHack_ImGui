#pragma once

#include <type_traits>
#include <d3d9.h>

class Hooks final{
public:
	Hooks();
	
	static WNDPROC originalWndProc;
	static std::add_pointer_t<HRESULT STDMETHODCALLTYPE(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> originalPresent;
	static std::add_pointer_t<HRESULT STDMETHODCALLTYPE(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> originalReset;

private:
};

extern Hooks hooks;