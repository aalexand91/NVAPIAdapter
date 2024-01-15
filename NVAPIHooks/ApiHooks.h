#pragma once

#include "ApiExport.h"
#include <memory>
#include <nvapi.h>

namespace NVAPIHooks
{
	/// <summary>Determines the specific error that occurred with the API.</summary>
	/// <param name="apiStatus">Status of the last executed API function.</param>
	/// <param name="message">Caches the API error message.</param>
	/// <returns>The status of the API upon determining the last API error.</returns>
	HOOKS_API NvAPI_Status GetErrorMessage(const NvAPI_Status apiStatus, char* message);

	/// <summary>Determines the full name of the Nvidia GPU.</summary>
	/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
	/// <param name="buffer">Caches the GPU name as an ASCII string.</param>
	/// <returns>The status of the API upon determining the name of the GPU.</returns>
	HOOKS_API NvAPI_Status GetName(NvPhysicalGpuHandle gpuHandle, char* buffer);

	/// <summary>Initializes the NVAPI library. Must be called before invoking any other API functions.</summary>
	/// <returns>The status of the API when attempting to initialilze it.</returns>
	HOOKS_API NvAPI_Status InitializeApi();

	/// <summary>Unloads the NVAPI library.</summary>
	/// <returns>The status of the API when attempting to unload it.</returns>
	HOOKS_API NvAPI_Status UnloadApi();

	/// <summary>
	/// Determines the number of physical GPUs installed in the system and provides an API handler for each.
	/// </summary>
	/// <param name="physicalGpuHandles">Caches each physical GPU handler.</param>
	/// <param name="numberOfGpus">Caches the number of GPUs installed in the system.</param>
	/// <returns>The status of the API upon determining the number of GPUs installed in the system.</returns>
	HOOKS_API NvAPI_Status GetPhysicalGpuHandles(std::unique_ptr<NvPhysicalGpuHandle>& physicalGpuHandles, unsigned long* numberOfGpus);
}