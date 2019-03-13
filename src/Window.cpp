#include "Window.h"

Window::Window(std::string windowClassName)	 : temp_window(nullptr), window_class_name(windowClassName)
{
	ZeroMemory(&window_class, sizeof(WNDCLASSEX));

	window_class.cbSize			= sizeof(WNDCLASSEX);
	window_class.style			= CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc	= DefWindowProc;
	window_class.lpszMenuName	= window_class_name.c_str();

	window_class.hInstance		= GetModuleHandle(nullptr);
	if (window_class.hInstance == nullptr)
		throw ERROR;

	if (!RegisterClassEx(&window_class))
		throw ERROR;

	temp_window = CreateWindow(
		window_class.lpszClassName,
		"Temporal Window",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		100, 100,
		NULL,
		NULL,
		window_class.hInstance,
		NULL
	);
	if(temp_window == nullptr)
		throw ERROR;
}
