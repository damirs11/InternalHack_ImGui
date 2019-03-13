#pragma once

#ifndef _MEMORY_DD_METHOD_H_
#define _MEMORY_DD_METHOD_H_
#endif

#include <string_view>
#include <regex>
#include <stdexcept>
#include <Windows.h>
#include <Psapi.h>

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")


class Memory_DummyDevice final{
public:
	Memory_DummyDevice();

	bool GetD3D9Device(void** pTable, size_t Size) noexcept;
	bool GetVTable(void** vTable) noexcept;

	std::uintptr_t present;
	std::uintptr_t reset;
private:
	void* vTable[119];
};

extern Memory_DummyDevice memory_DD;