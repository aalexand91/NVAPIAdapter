// Provide defintion of when to export or import from the .dll.

#pragma once
#ifdef EXPORT_GRAPHICS_CARD_API
	#define GRAPHICS_CARD_API _declspec(dllexport)
#else
	#define GRAPHICS_CARD_API _declspec(dllimport)
#endif
