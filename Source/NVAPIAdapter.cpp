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
		const auto status = NVAPITunnel::Initialize();
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
		char name[ms_asciiBufferSize] = "\0";
		const auto status = NVAPITunnel::GetFullName(m_physicalHandler, name);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return name;
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
		const auto status = NVAPITunnel::GetGpuType(m_physicalHandler, &gpuType);
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
		const auto status = NVAPITunnel::GetPciIdentifiers(m_physicalHandler, identifier);
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
		const auto status = NVAPITunnel::GetBusType(m_physicalHandler, &busType);
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
		const auto status = NVAPITunnel::GetBusId(m_physicalHandler, &id);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return id;
		}
		const std::string message = "Failed to get GPU bus ID. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	std::string NVAPIAdapter::GetVbiosVersion()
	{
		AssertApiInitialized();
		char biosVersion[ms_asciiBufferSize] = "\0";
		const auto status = NVAPITunnel::GetVBiosVersion(m_physicalHandler, biosVersion);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return biosVersion;
		}
		const std::string message = "Failed to get VBIOS version. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	unsigned long NVAPIAdapter::GetPhysicalFrameBufferSizeInKb()
	{
		const bool includeVirtualSize = false;
		return GetFrameBufferSize(includeVirtualSize);
	}

	unsigned long NVAPIAdapter::GetFrameBufferSize(const bool includeVirtualSize)
	{
		AssertApiInitialized();
		unsigned long bufferSize = 0ul;
		const auto status = includeVirtualSize
			? NVAPITunnel::GetVirtualFrameBufferSize(m_physicalHandler, &bufferSize)
			: NVAPITunnel::GetPhysicalFrameBufferSize(m_physicalHandler, &bufferSize);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return bufferSize;
		}
		const std::string context = includeVirtualSize ? "virtual" : "physical";
		const std::string message = "Failed to get " + context + " frame buffer size. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	unsigned long NVAPIAdapter::GetVirtualFrameBufferSizeInKb()
	{
		const bool includeVirtualSize = true;
		return GetFrameBufferSize(includeVirtualSize);
	}

	unsigned int NVAPIAdapter::GetGpuCoreCount()
	{
		AssertApiInitialized();
		unsigned long coreCount = 0ul;
		const auto status = NVAPITunnel::GetGpuCoreCount(m_physicalHandler, &coreCount);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return static_cast<unsigned int>(coreCount);
		}
		const std::string message = "Failed to get GPU core count. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	int NVAPIAdapter::GetGpuCoreTemp()
	{
		AssertApiInitialized();
		NV_GPU_THERMAL_SETTINGS thermalSettings;
		const auto status = NVAPITunnel::GetThermalSettings(m_physicalHandler, NV_THERMAL_TARGET::NVAPI_THERMAL_TARGET_GPU, &thermalSettings);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return thermalSettings.sensor[0].currentTemp;
		}
		const std::string message = "Failed to get GPU core temperature. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}

	int NVAPIAdapter::GetGpuMemoryTemp()
	{
		AssertApiInitialized();
		NV_GPU_THERMAL_SETTINGS thermalSettings;
		const auto status = NVAPITunnel::GetThermalSettings(m_physicalHandler, NV_THERMAL_TARGET::NVAPI_THERMAL_TARGET_MEMORY, &thermalSettings);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return thermalSettings.sensor[0].currentTemp;
		}
		const std::string message = "Failed to get GPU memory temperature. " + NVAPIStatusInterpreter::GetStatusMessage(status);
		throw NVAPIError(message);
	}
}

