#include <pch.h>

#include <NVAPITunnel.h>

namespace Adapter
{
	NvAPI_Status NVAPITunnel::Initialize()
	{
		return NvAPI_Initialize();
	}

	NvAPI_Status NVAPITunnel::Unload()
	{
		return NvAPI_Unload();
	}

	NvAPI_Status NVAPITunnel::GetStatusErrorMessage(const NvAPI_Status status, char* message)
	{
		return NvAPI_GetErrorMessage(status, message);
	}

	NvAPI_Status NVAPITunnel::GetFullName(const NvPhysicalGpuHandle physicalHandler, char* name)
	{
		return NvAPI_GPU_GetFullName(physicalHandler, name);
	}

	NvAPI_Status NVAPITunnel::GetGpuType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_TYPE* gpuType)
	{
		return NvAPI_GPU_GetGPUType(physicalHandler, gpuType);
	}

	NvAPI_Status NVAPITunnel::GetPciIdentifiers(const NvPhysicalGpuHandle physicalHandler, PciIdentifier& pciIdentifier)
	{
		return NvAPI_GPU_GetPCIIdentifiers(physicalHandler, &pciIdentifier.m_internalId, &pciIdentifier.m_subsystemId, &pciIdentifier.m_revisionId, &pciIdentifier.m_externalId);
	}

	NvAPI_Status NVAPITunnel::GetBusType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_BUS_TYPE* busType) 
	{
		return NvAPI_GPU_GetBusType(physicalHandler, busType);
	}

	NvAPI_Status NVAPITunnel::GetBusId(const NvPhysicalGpuHandle physicalHandler, unsigned long* id)
	{
		return NvAPI_GPU_GetBusId(physicalHandler, id);
	}

	NvAPI_Status NVAPITunnel::GetVBiosVersion(const NvPhysicalGpuHandle physicalHandler, char* biosVersion)
	{
		return NvAPI_GPU_GetVbiosVersionString(physicalHandler, biosVersion);
	}

	NvAPI_Status NVAPITunnel::GetPhysicalFrameBufferSize(const NvPhysicalGpuHandle physicalHandler, unsigned long* bufferSize)
	{
		return NvAPI_GPU_GetPhysicalFrameBufferSize(physicalHandler, bufferSize);
	}

	NvAPI_Status NVAPITunnel::GetVirtualFrameBufferSize(const NvPhysicalGpuHandle physicalHandler, unsigned long* bufferSize)
	{
		return NvAPI_GPU_GetVirtualFrameBufferSize(physicalHandler, bufferSize);
	}

	NvAPI_Status NVAPITunnel::GetGpuCoreCount(const NvPhysicalGpuHandle physicalHandler, unsigned long* coreCount)
	{
		return NvAPI_GPU_GetGpuCoreCount(physicalHandler, coreCount);
	}

	NvAPI_Status NVAPITunnel::GetThermalSettings(const NvPhysicalGpuHandle physicalHandler, const NV_THERMAL_TARGET targetSensor, NV_GPU_THERMAL_SETTINGS* thermalSettings)
	{
		const auto sensorIndex = static_cast<unsigned long>(targetSensor);
		return NvAPI_GPU_GetThermalSettings(physicalHandler, sensorIndex, thermalSettings);
	}
}