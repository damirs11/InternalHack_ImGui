#pragma once

#include <string>
#include <Windows.h>
#include <utility>

class Window
{
public:
	Window(std::string windowClassName);
	HWND windowHandle() const;

protected:
	~Window();

private:
	WNDCLASSEX window_class;
	HWND temp_window;
	std::string window_class_name;
};