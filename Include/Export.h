// Provide defintion of when to export or import from the .dll.

#pragma once
#ifdef EXPORT_API
	#define ADAPTER_API _declspec(dllexport)
#else
	#define ADAPTER_API _declspec(dllimport)
#endif
