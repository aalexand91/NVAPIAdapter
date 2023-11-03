#include <pch.h>

#include <NVAPIAdapter.h>
#include <NVAPIError.h>
#include <NvApiStatusInterpreter.h>
#include <NVAPITunnel.h>

namespace Adapter
{
	void NVAPIAdapter::Initialize()
	{
		if (m_apiInitialized)
		{
			return;
		}
		NvAPI_Status status = NVAPITunnel::Initialize();
		if (status == NvAPI_Status::NVAPI_OK)
		{
			m_apiInitialized = true;
			return;
		}
		std::string message = "Failed to initialize Nvidia API. " + std::string(NVAPIStatusInterpreter::GetStatusMessage(status));
		throw NVAPIError(message);
	}

	void NVAPIAdapter::Unload() 
	{
		if (m_apiInitialized) 
		{
			// Rather than throw an error, just set the initialization flag to the result of the Unload method.
			// This will help determine if future calls should still try to unload the API.
			m_apiInitialized = NVAPITunnel::Unload() != NVAPI_OK;
		}
	}

	std::string NVAPIAdapter::GetName()
	{
		AssertApiInitialized();
		char name[256];	// Size of buffer set to the maximum number of characters in an ASCII string.
		NvAPI_Status status = NVAPITunnel::GetFullName(m_physicalHandler, name);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return std::string(name);
		}
		std::string message = "Failed to get graphics card name. " + std::string(NVAPIStatusInterpreter::GetStatusMessage(status));
		throw NVAPIError(message);
	}

	void NVAPIAdapter::AssertApiInitialized()
	{
		if (m_apiInitialized)
		{
			return;
		}
		throw NVAPIError(NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_API_NOT_INITIALIZED));
	}

	std::string NVAPIAdapter::GetGpuType() 
	{
		AssertApiInitialized();
		NV_GPU_TYPE gpuType = NV_GPU_TYPE::NV_SYSTEM_TYPE_GPU_UNKNOWN;
		NvAPI_Status status = NVAPITunnel::GetGpuType(m_physicalHandler, &gpuType);
		if (status != NvAPI_Status::NVAPI_OK) 
		{
			// Rather than throwing an exception, just return the unknown type since the API could not determine what the GPU type was.
			return "Unknown";
		}
		return gpuType == NV_GPU_TYPE::NV_SYSTEM_TYPE_DGPU ? "Discrete" : "Integrated";
	}

	PciIdentifier NVAPIAdapter::GetPciIdentifiers()
	{
		AssertApiInitialized();
		PciIdentifier identifier;
		NvAPI_Status status = NVAPITunnel::GetPciIdentifiers(m_physicalHandler, identifier);
		if (status == NvAPI_Status::NVAPI_OK) 
		{
			return identifier;
		}
		const std::string message = "Failed to get PCI identifiers. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	std::string NVAPIAdapter::GetBusType()
	{
		AssertApiInitialized();
		NV_GPU_BUS_TYPE busType = NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_UNDEFINED;
		NvAPI_Status status = NVAPITunnel::GetBusType(m_physicalHandler, &busType);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return GetGpuBusType(busType);
		}
		const std::string message = "Failed to get GPU bus type. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	std::string NVAPIAdapter::GetGpuBusType(const NV_GPU_BUS_TYPE busType)
	{
		static const std::unordered_map<NV_GPU_BUS_TYPE, std::string> map
		{
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_AGP, "Accelerated Graphics Port"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_AXI, "Advanced eXtensible Interface"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_PCI, "Peripheral Component Interconnect"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_PCI_EXPRESS, "Peripheral Component Interconnect Express"},
		};

		const auto iterator = map.find(busType);
		return iterator == map.end() ? "Unknown" : iterator->second;
	}

	unsigned long NVAPIAdapter::GetBusId() 
	{
		AssertApiInitialized();
		unsigned long id = 0ul;
		auto status = NVAPITunnel::GetBusId(m_physicalHandler, &id);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return id;
		}
		const std::string message = "Failed to get GPU bus ID. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}
}

