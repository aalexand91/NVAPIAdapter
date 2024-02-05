#pragma once

#include "ApiExport.h"
#include <memory>
#include <nvapi.h>

namespace NVAPIHooks
{
	/// <summary>
	/// Directly invokes the NVAPI library. Each function is static so that they can be mocked by unit tests.
	/// </summary>
	namespace ApiTunnel
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

		/// <summary>Determines the number of physical GPUs installed in the system and provides an API handler for each.</summary>
		/// <param name="physicalGpuHandles">Caches each physical GPU handler.</param>
		/// <param name="numberOfGpus">Caches the number of GPUs installed in the system.</param>
		/// <returns>The status of the API upon determining the number of GPUs installed in the system.</returns>
		HOOKS_API NvAPI_Status GetPhysicalGpuHandles(NvPhysicalGpuHandle* physicalGpuHandles, unsigned long* numberOfGpus);

		/// <summary>Determines the type of the system the GPU is installed in.</summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="systemType">Caches the system type detected.</param>
		/// <returns>The status of the API upon determining the system type.</returns>
		HOOKS_API NvAPI_Status GetSystemType(NvPhysicalGpuHandle gpuHandle, NV_SYSTEM_TYPE* systemType);

		/// <summary>Determines if the GPU is an intergrated or discrete type.</summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="gpuType">Caches the GPU type.</param>
		/// <returns>The status of the API upon determining the system type.</returns>
		HOOKS_API NvAPI_Status GetGpuType(NvPhysicalGpuHandle gpuHandle, NV_GPU_TYPE* gpuType);

		/// <summary>Determines the PCI identifiers associated with the GPU.</summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="deviceId">Caches the internal PCI device ID for the GPU.</param>
		/// <param name="subSystemId">Caches the internal PCI subsystem ID for the GPU.</param>
		/// <param name="revisionId">Caches the device-specific revision ID for the GPU.</param>
		/// <param name="externalDeviceId">Cahces the external device ID for the GPU.</param>
		/// <returns>The status of the API upon determining the PCI identifiers.</returns>
		HOOKS_API NvAPI_Status GetPciIdentifiers(
			NvPhysicalGpuHandle gpuHandle, 
			unsigned long* deviceId,
			unsigned long* subSystemId,
			unsigned long* revisionId,
			unsigned long* externalDeviceId);

		/// <summary>Determins the bus ID associated with the GPU.</summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="busId">Caches the GPU bus ID.</param>
		/// <returns>The status of the API upon determining the bus ID.</returns>
		HOOKS_API NvAPI_Status GetGpuBusId(NvPhysicalGpuHandle gpuHandle, unsigned long* busId);

		/// <summary>
		/// Determines the video BIOS version of the GPU in the form of xx.xx.xx.xx.yy where 
		/// xx.xx.xx.xx is the revision number as major.minor.maintenance.build and 
		/// yy is OEM (original equipment manufacturer's) number.
		/// </summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="biosVersion">Caches the video BIOS version.</param>
		/// <returns>The status of the API upon determining the video BIOS version.</returns>
		HOOKS_API NvAPI_Status GetVbiosVersion(NvPhysicalGpuHandle gpuHandle, char* biosVersion);

		/// <summary>
		/// Determines the physical size of the framebuffer in KB. Does not include any RAM dedicated for use by the GPU.
		/// </summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="size">Caches the framebuffer size in KB.</param>
		/// <returns>The status of the API upon determining the physical framebuffer size.</returns>
		HOOKS_API NvAPI_Status GetPhysicalFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* size);

		/// <summary>
		/// Determines the virtual size of the framebuffer in KB. This includes both the physical size and RAM dedicated for use by the GPU.
		/// </summary>
		/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
		/// <param name="size">Caches the framebuffer size in KB</param>
		/// <returns>The status of the API upon determining the virtual framebuffer size.</returns>
		HOOKS_API NvAPI_Status GetVirtualFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* size);
	}
}