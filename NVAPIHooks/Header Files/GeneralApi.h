// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>

namespace NVAPIHooks
{
	/// <summary>
	/// Provides an API to simply interface with the NVAPI library.
	/// </summary>
	namespace GeneralApi
	{
		/// <summary>
		/// Initializes the NVAPI library. Must be called before interfacing with other API functions.
		/// </summary>
		HOOKS_API void Initialize();
	}
}