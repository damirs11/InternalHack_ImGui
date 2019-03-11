#pragma once

#include <string_view>
#include <regex>
#include <stdexcept>
#include <Windows.h>
#include <Psapi.h>

class Memory final{
public:
	Memory() noexcept;
	
	std::uintptr_t findPattern(const std::string&, const std::string&) const;

	std::uintptr_t present;
	std::uintptr_t reset;

};

extern Memory memory;
