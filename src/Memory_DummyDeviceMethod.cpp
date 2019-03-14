#include "Memory_DummyDeviceMethod.h"

Memory_DummyDevice::Memory_DummyDevice() : d3d9(nullptr), d3d9Device(nullptr)
{
	tempWindow = new Window("TempWindow");

	LPDIRECT3D9 d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
		throw ERROR;

	D3DDISPLAYMODE displayMode;
	if(FAILED(d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
	{
		d3d9->Release();
		throw ERROR;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed			= TRUE;
	d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat	= displayMode.Format;

	if (FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tempWindow->windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT , &d3dpp, &d3d9Device)))
	{
		d3d9->Release();
		throw ERROR;
	}

}

//bool Memory_DummyDevice::GetVTable(void** vTable) noexcept
//{
//	if (!vTable)
//		return false;
//
//	IDirect3D9* pD3D;
//	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
//	if (!pD3D)
//		return false;	
//
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	d3dpp.SwapEffect	= D3DSWAPEFFECT_DISCARD;
//	d3dpp.hDeviceWindow = GetForegroundWindow();
//	d3dpp.Windowed		= TRUE;
//
//	IDirect3DDevice9* pDummyDevice = nullptr;
//
//	HRESULT hr = pD3D->CreateDevice(
//		D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		d3dpp.hDeviceWindow,
//		D3DCREATE_HARDWARE_VERTEXPROCESSING,
//		&d3dpp, &pDummyDevice);
//
//	vTable = *reinterpret_cast<void***>(pDummyDevice);
//
//	return true;
//}

std::vector<UINT> Memory_DummyDevice::VTable() const
{
	UINT vtbl[VTableElements];

	memcpy(	vtbl,
			*reinterpret_cast<UINT**>(d3d9Device),
			VTableElements * sizeof(UINT));

	return std::vector<UINT>(vtbl, vtbl + sizeof(vtbl) / sizeof(vtbl[0]));
}

Memory_DummyDevice::~Memory_DummyDevice()
{
	if (d3d9Device)
		d3d9Device->Release();
	
	if (d3d9)
		d3d9->Release();
}