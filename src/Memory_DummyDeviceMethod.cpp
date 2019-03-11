#include "Memory_DummyDeviceMethod.h"

Memory_DummyDevice::Memory_DummyDevice()
{
	try
	{
		if (!GetD3D9Device(vTable, sizeof(vTable))) {
			MessageBox(NULL, "GetD3D9Device return false", "GetD3D9Device", MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		present = reinterpret_cast<ptrdiff_t>(vTable[17]);
		reset	= reinterpret_cast<ptrdiff_t>(vTable[16]);
	}
	catch (const std::runtime_error& e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}
	
		

}

bool Memory_DummyDevice::GetD3D9Device(void** pTable, size_t Size) noexcept
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "Kiero";
	windowClass.hIconSm = NULL;

	RegisterClassEx(&windowClass);

	HWND window = CreateWindow(windowClass.lpszClassName, "Kiero DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

	HMODULE libD3D9;
	libD3D9 = GetModuleHandle("d3d9.dll");
	if (!libD3D9)
		return false;

	void* Direct3DCreate9;
	Direct3DCreate9 = GetProcAddress(libD3D9, "Direct3DCreate9");

	if (!pTable)
		return false;

	IDirect3D9* pD3D;
	pD3D =  ( ( LPDIRECT3D9(__stdcall*)(uint32_t) ) (Direct3DCreate9) ) (D3D_SDK_VERSION);
	if (!pD3D)
		return false;

	D3DDISPLAYMODE displayMode;
	if (pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode) < 0)
		return false;
	

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = 0;
	d3dpp.BackBufferHeight = 0;
	d3dpp.BackBufferFormat = displayMode.Format;
	d3dpp.BackBufferCount = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = NULL;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = window;
	d3dpp.Windowed = 1;
	d3dpp.EnableAutoDepthStencil = 0;
	d3dpp.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	d3dpp.Flags = NULL;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = 0;

	IDirect3DDevice9* pDummyDevice = nullptr;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &d3dpp, &pDummyDevice)))
	{
		pD3D->Release();
		return false;
	}
	
	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();

	return true;
}
