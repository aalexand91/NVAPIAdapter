#include <pch.h>
#include "NvApiAdapter.h"
#include "NvApiError.h"
#include "NvidiaGraphicsCard.h"
#include "NvApiStatusInterpreter.h"

namespace GraphicsCards
{
	void NvidiaGraphicsCard::Initialize()
	{
		if (m_apiInitialized)
		{
			return;
		}
		NvAPI_Status status = NvApiAdapter::Initialize();
		if (status == NvAPI_Status::NVAPI_OK)
		{
			m_apiInitialized = true;
			return;
		}
		std::string message = "Failed to initialize Nvidia API. " + std::string(NvApiStatusInterpreter::GetStatusMessage(status));
		throw NvApiError(message);
	}

	std::string NvidiaGraphicsCard::GetName()
	{
		AssertApiInitialized();
		char name[256];	// Size of buffer set to the maximum number of characters in an ASCII string.
		NvAPI_Status status = NvApiAdapter::GetFullName(m_physicalHandler, name);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return std::string(name);
		}
		std::string message = "Failed to get graphics card name. " + std::string(NvApiStatusInterpreter::GetStatusMessage(status));
		throw NvApiError(message);
	}

	void NvidiaGraphicsCard::AssertApiInitialized()
	{
		if (m_apiInitialized)
		{
			return;
		}
		throw NvApiError(NvApiStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_API_NOT_INITIALIZED));
	}

	std::string NvidiaGraphicsCard::GetGpuType() 
	{
		AssertApiInitialized();
		NV_GPU_TYPE gpuType = NV_GPU_TYPE::NV_SYSTEM_TYPE_GPU_UNKNOWN;
		NvAPI_Status status = NvApiAdapter::GetGpuType(m_physicalHandler, &gpuType);
		if (status != NvAPI_Status::NVAPI_OK) 
		{
			// Rather than throwing an exception, just return the unknown type since the API could not determine what the GPU type was.
			return "Unknown";
		}
		return gpuType == NV_GPU_TYPE::NV_SYSTEM_TYPE_DGPU ? "Discrete" : "Integrated";
	}
}

