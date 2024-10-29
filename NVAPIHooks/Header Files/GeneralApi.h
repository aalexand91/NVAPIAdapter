// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>
#include <IPhysicalGpu.h>
#include <memory>
#include <vector>

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

		/// <summary>Unloads the NVAPI library.</summary>
		HOOKS_API void Unload();

		/// <returns>All physical GPUs detected by the NVAPI library.</returns>
		HOOKS_API std::vector<IPhysicalGpu*> GetAllPhysicalGpus();
	}
}