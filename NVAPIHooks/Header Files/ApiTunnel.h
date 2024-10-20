// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	/// <summary>
	/// Wraps the direct NVAPI library function calls that unit test can easily mock.
	/// </summary>
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

		/// <summary>
		/// Determines the number of cores defined for the GPU and caches it into the given core count buffer.
		/// </summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="coreCount">Caches the number of GPU cores.</param>
		/// <returns>NVAPI status code for determining the number of cores.</returns>
		HOOKS_API NvAPI_Status GetGpuCoreCount(NvPhysicalGpuHandle gpuHandle, unsigned long* coreCount);

		/// <summary>
		/// Determines the number of physical GPUs connected and caches their handles and total detected.
		/// </summary>
		/// <param name="gpuHandles">Caches an array of physical GPU handles.</param>
		/// <param name="totalGpuCount">Caches the total number of physical GPUs detected.</param>
		/// <returns>NVAPI status code for determining the number of physical GPUs.</returns>
		HOOKS_API NvAPI_Status GetPhysicalGpuHandles(NvPhysicalGpuHandle* gpuHandles, unsigned long* totalGpuCount);
	}
}
