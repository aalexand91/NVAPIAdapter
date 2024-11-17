// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

		/// <summary>Determines the full GPU name as an ASCII string such as "Quadro FX 1400".</summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="name">Caches the GPU name.</param>
		/// <returns>NVAPI status code for determining the GPU name./returns>
		HOOKS_API NvAPI_Status GetFullName(NvPhysicalGpuHandle gpuHandle, char* name);

		/// <summary>
		/// Determines the GPU bus type, for example: PCI, PCIe, etc.
		/// </summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="busType">Caches the GPU bus type.</param>
		/// <returns>NVAPI status code for determining the GPU bus type.</returns>
		HOOKS_API NvAPI_Status GetBusType(NvPhysicalGpuHandle gpuHandle, NV_GPU_BUS_TYPE* busType);

		/// <summary>
		/// Determines the GPU system type, for example: Laptop
		/// </summary>
		/// <param name="gpuHandle"><Single physical GPU handle./param>
		/// <param name="systemType">Caches the GPU system type.</param>
		/// <returns>NVAPI status code for determining the GPU system type.</returns>
		HOOKS_API NvAPI_Status GetSystemType(NvPhysicalGpuHandle gpuHandle, NV_SYSTEM_TYPE* systemType);

		/// <summary>Determines the GPU PCI identifiers.</summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="internalDeviceId">Caches the internal PCI device identifier.</param>
		/// <param name="subsystemId">Caches the subsystem PCI device identifier.</param>
		/// <param name="revisionId">Caches the device-specific revision identifier.</param>
		/// <param name="externalDeviceId">Caches the external PCI device identifier.</param>
		/// <returns>NVAPI status code for determining the GPU PCI identifiers.</returns>
		HOOKS_API NvAPI_Status GetPciIdentifiers(NvPhysicalGpuHandle gpuHandle, unsigned long* internalDeviceId,
			unsigned long* subsystemId, unsigned long* revisionId, unsigned long* externalDeviceId);

		/// <summary>
		/// Determines the physical frame buffer size in KB. Does not include any system RAM.
		/// </summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="bufferSize">Caches the physical frame buffer size.</param>
		/// <returns>NVAPI status code for determining the GPU physical frame buffer size.</returns>
		HOOKS_API NvAPI_Status GetPhysicalFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* bufferSize);

		/// <summary>
		/// Determines the virtual frame buffer size in KB. Includes both physical and any RAM dedicated for the GPU.
		/// </summary>
		/// <param name="gpuHandle">Single physical GPU handle.</param>
		/// <param name="bufferSize">Caches the virtual frame buffer size.</param>
		/// <returns>NVAPI status code for determining the GPU virtual frame buffer size.</returns>
		HOOKS_API NvAPI_Status GetVirtualFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* bufferSize);
	}
}
