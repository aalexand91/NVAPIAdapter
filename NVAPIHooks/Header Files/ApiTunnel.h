// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	namespace ApiTunnel
	{
		/// <summary>Initializes the NVAPI library.</summary>
		/// <returns>NVAPI status code for initializing the library.</returns>
		HOOKS_API NvAPI_Status InitializeApi();

		/// <summary>
		/// Determines the API error message from the current API status and caches it into the given message buffer.
		/// </summary>
		/// <param name="currentStatus">The current NVAPI status.</param>
		/// <param name="message">Caches the respective NVAPI error message.</param>
		/// <returns>NVAPI status code for determining the current API error message.</returns>
		HOOKS_API NvAPI_Status GetApiErrorMessage(const NvAPI_Status currentStatus, char* message);

		/// <summary>Unloads the NVAPI library.</summary>
		/// <returns>NVAPI status code for unloading the library.</returns>
		HOOKS_API NvAPI_Status UnloadApi();
	}
}
