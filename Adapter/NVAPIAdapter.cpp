#include <pch.h>
#include "NVAPIAdapter.h"
#include "NVAPIError.h"
#include "NvApiStatusInterpreter.h"
#include "NVAPITunnel.h"

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
}

