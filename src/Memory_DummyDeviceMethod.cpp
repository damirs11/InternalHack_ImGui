#include "Memory_DummyDeviceMethod.h"

Memory_DummyDevice::Memory_DummyDevice()
{
	try
	{
		if (!GetVTable(vTable)) {
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

bool Memory_DummyDevice::GetVTable(void** vTable) noexcept
{
	if (!vTable)
		return false;

	IDirect3D9* pD3D;
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;	

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect	= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow();
	d3dpp.Windowed		= TRUE;

	IDirect3DDevice9* pDummyDevice = nullptr;

	HRESULT hr = pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pDummyDevice);

	vTable = *reinterpret_cast<void***>(pDummyDevice);

	return true;
}
