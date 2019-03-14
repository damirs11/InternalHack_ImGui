#pragma once

#ifndef _MEMORY_DD_METHOD_H_
#define _MEMORY_DD_METHOD_H_
#endif

#include <stdexcept>
#include <Windows.h>
#include <Psapi.h>

#include "Window.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

class Memory_DummyDevice final{
public:
	Memory_DummyDevice();

	static const int VTableElements = 119;

	std::vector<UINT> VTable() const;
protected:
	~Memory_DummyDevice();
private:
	Window* tempWindow;
	IDirect3D9* d3d9;
	IDirect3DDevice9* d3d9Device;
};

extern Memory_DummyDevice memory_DD;