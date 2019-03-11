#pragma once

#include <d3d9.h>

class Hooks_DummyDevice final{
public:
	Hooks_DummyDevice();
	bool GetD3D9Device(void** pTable, size_t Size);
	void printVTable();
private:
	void** vTable;
};

extern Hooks_DummyDevice Hooks_DD;