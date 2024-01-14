#pragma once

// Provides preprocessor definitions on how to handle exporting/importing the API between projects.

#ifdef EXPORT_API
	#define HOOKS_API __declspec(dllexport)
#else
	#define HOOKS_API __declspec(dllimport)
#endif