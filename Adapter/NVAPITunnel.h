#pragma once

#include "Export.h"
#include <nvapi.h>

namespace Adapter
{
	/// <summary>
	/// Wrapper to invoke the NVAPI library while also providing static functions that can be mocked by unit tests.
	/// </summary>
	namespace NVAPITunnel
	{
		/// <summary>
		/// Initializes the NVAPI library. Must be called before attempting to use library.
		/// </summary>
		/// <returns>
		/// The status of the NVAPI library upon initializing.
		/// </returns>
		ADAPTER_API NvAPI_Status Initialize();

		/// <summary>
		/// Unloads the NVAPI library. Should be called before closing the application using the library.
		/// </summary>
		/// <returns>
		/// The status of the NVAPI library upon unloading.
		/// </returns>
		ADAPTER_API NvAPI_Status Unload();

		/// <summary>
		/// Determines the full name of the graphics card.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="name">Stores the full name of the graphics card.</param>
		/// <returns>
		/// The status of the NVAPI library upon attempting to get the full name of the graphics card.
		/// </returns>
		ADAPTER_API NvAPI_Status GetFullName(const NvPhysicalGpuHandle physicalHandler, char* name);

		/// <summary>
		/// Determines the GPU type (integrated, discete, or unknown).
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="gpuType">Stores the GPU type of the graphics card.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the GPU type.</returns>
		ADAPTER_API NvAPI_Status GetGpuType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_TYPE* gpuType);
	}
}