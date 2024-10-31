// Copyright 2024 Anthony Alexander

// Preprocessor definitions for exporting/importing library API.

#pragma once

#ifdef EXPORT_API
	#define HOOKS_API __declspec(dllexport)
#else
	#define HOOKS_API __declspec(dllimport)
#endif
