#pragma once

#ifndef _MEMORY_METHOD_H_
#define _MEMORY_METHOD_H_
#endif

#include <string_view>
#include <regex>
#include <stdexcept>
#include <Windows.h>
#include <Psapi.h>

class Memory final{
public:
	Memory();
	
	std::uintptr_t findPattern(const std::string&, const std::string&) const;

	std::uintptr_t present;
	std::uintptr_t reset;

};

extern Memory memory;
