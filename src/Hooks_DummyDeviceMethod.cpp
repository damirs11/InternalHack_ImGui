
#include "Hooks_DummyDeviceMethod.h"

Hooks_DummyDevice::Hooks_DummyDevice()
{
	Hooks_DummyDevice::vTable = NULL;
}

bool Hooks_DummyDevice::GetD3D9Device(void** pTable, size_t Size)
{
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.SwapEffect	= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow();
	d3dpp.Windowed		= ((GetWindowLong(d3dpp.hDeviceWindow, GWL_STYLE) & WS_POPUP) 
							!= 0) ? FALSE : TRUE;;

	IDirect3DDevice9* pDummyDevice = nullptr;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice)))
	{
		pD3D->Release();
		return false;
	}
	
	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();

	return true;
}
