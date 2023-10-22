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
}