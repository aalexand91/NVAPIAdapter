#pragma once

#include <Export.h>
#include <nvapi.h>
#include <PciIdentifier.h>

namespace Adapter
{
	/// <summary>
	/// Provides static hooks to the NVAPI library that can be mocked by unit tests.
	/// </summary>
	namespace NVAPITunnel
	{
		/// <summary>Initializes the NVAPI library. Must be called before attempting to use library.</summary>
		/// <returns>The status of the NVAPI library upon initializing.</returns>
		ADAPTER_API NvAPI_Status Initialize();

		/// <summary>Unloads the NVAPI library. Should be called before closing the application using the library.</summary>
		/// <returns>The status of the NVAPI library upon unloading.</returns>
		ADAPTER_API NvAPI_Status Unload();

		/// <summary>Determines the NVAPI status error and caches it into null terminated string.</summary>
		/// <param name="status">NVAPI status to determine the error message.</param>
		/// <param name="messasge">Buffer to cache the message.</param>
		/// <returns>The status of the NVAPI library upon determing the status error.</returns>
		ADAPTER_API NvAPI_Status GetStatusErrorMessage(NvAPI_Status status, char* messasge);

		/// <summary>Determines the full name of the graphics card.</summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="name">Stores the full name of the graphics card.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the full name of the graphics card.</returns>
		ADAPTER_API NvAPI_Status GetFullName(const NvPhysicalGpuHandle physicalHandler, char* name);

		/// <summary>Determines the GPU type (integrated, discete, or unknown).</summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="gpuType">Stores the GPU type of the graphics card.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the GPU type.</returns>
		ADAPTER_API NvAPI_Status GetGpuType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_TYPE* gpuType);

		/// <summary>Determines the PCI identifiers associated with the graphics card.</summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="pciIdentifier">Stores the PCI identifiers.</param>
		/// <returns>The status of the NVAPI library upon attemptiong to get the PCI indentifiers.</returns>
		ADAPTER_API NvAPI_Status GetPciIdentifiers(const NvPhysicalGpuHandle physicalHandler, PciIdentifier& pciIdentifier);

		/// <summary>Determines the GPU bus type of the graphics card.</summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="busType">Stores the bus type.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the bus type.</returns>
		ADAPTER_API NvAPI_Status GetBusType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_BUS_TYPE* busType);

		/// <summary>Determines the ID of the bus associated with the GPU.</summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="id">Stores the bus ID.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the bus ID.</returns>
		ADAPTER_API NvAPI_Status GetBusId(const NvPhysicalGpuHandle physicalHandler, unsigned long* id);

		/// <summary>
		/// Determines the VBIOS version of the graphics card in the form of xx.xx.xx.xx.yy 
		/// where xx numbers represent the BIOS revision and yy is the original manufacturer's revision.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="biosVersion">Stores the VBIOS version.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the VBIOS version.</returns>
		ADAPTER_API NvAPI_Status GetVBiosVersion(const NvPhysicalGpuHandle physicalHandler, char* biosVersion);

		/// <summary>
		/// Determines the physical frame buffer size (excluding any allocated system RAM) of the GPU in KB.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="bufferSize">Stores the physical frame buffer size value.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the physical frame buffer size.</returns>
		ADAPTER_API NvAPI_Status GetPhysicalFrameBufferSize(const NvPhysicalGpuHandle physicalHandler, unsigned long* bufferSize);

		/// <summary>
		/// Determines the physical and virtual buffer size of the GPU in KB.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="bufferSize">Stores the total buffer size of both the physical and virtual memory.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the virtual frame buffer size.</returns>
		ADAPTER_API NvAPI_Status GetVirtualFrameBufferSize(const NvPhysicalGpuHandle physicalHandler, unsigned long* bufferSize);

		/// <summary>
		/// Determines the total number of defined for the GPU.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="coreCount">Stores the total number of GPU cores.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the GPU core count.</returns>
		ADAPTER_API NvAPI_Status GetGpuCoreCount(const NvPhysicalGpuHandle physicalHandler, unsigned long* coreCount);

		/// <summary>
		/// Determines the thermal settings of a particular GPU sensor device.
		/// </summary>
		/// <param name="physicalHandler">NVAPI handler interfacing with the specific graphics card.</param>
		/// <param name="targetSensor">GPU sensor type to obtain the thermal settings of.</param>
		/// <param name="thermalSettings">Stores thermal settings of the GPU sensor device.</param>
		/// <returns>The status of the NVAPI library upon attempting to get the thermal settings of the GPU sensor.</returns>
		ADAPTER_API NvAPI_Status GetThermalSettings(const NvPhysicalGpuHandle physicalHandler, const NV_THERMAL_TARGET targetSensor, NV_GPU_THERMAL_SETTINGS* thermalSettings);
	}
}