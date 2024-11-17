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

#include <pch.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <PhysicalGpu.h>

namespace NVAPIHooks
{
	unsigned long PhysicalGpu::GetCoreCount()
	{
		unsigned long coreCount = 0ul;
		const auto status = ApiTunnel::GetGpuCoreCount(m_physicalGpuHandle, &coreCount);
		if (status == NvAPI_Status::NVAPI_OK) return coreCount;
		throw ApiError("Failed to get GPU core count.", status);
	}

	std::string PhysicalGpu::GetFullName()
	{
		char name[NVAPI_SHORT_STRING_MAX] = "\0";
		const auto status = ApiTunnel::GetFullName(m_physicalGpuHandle, name);
		if (status == NvAPI_Status::NVAPI_OK) return std::string(name);
		throw ApiError("Failed to get GPU name.", status);
	}

	std::string PhysicalGpu::GetBusType()
	{
		NV_GPU_BUS_TYPE busType = NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_UNDEFINED;
		const auto status = ApiTunnel::GetBusType(m_physicalGpuHandle, &busType);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to get GPU bus type.", status);

		const auto pair = m_busTypeMap.find(busType);

		// Return a different value from Undefined so that it is clear 
		// that a new GPU type should be added to the map.
		return pair == m_busTypeMap.end() ? "Unknown" : pair->second;
	}

	std::string PhysicalGpu::GetSystemType()
	{
		NV_SYSTEM_TYPE systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_UNKNOWN;
		const auto status = ApiTunnel::GetSystemType(m_physicalGpuHandle, &systemType);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to get GPU system type.", status);
		
		switch (systemType)
		{
		case NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_LAPTOP: return "Laptop";
		case NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_DESKTOP: return "Desktop";
		default: return "Unknown";
		}
	}

	unsigned long PhysicalGpu::GetPciIdentifier(const PciIdentifierType idType)
	{
		unsigned long internalId, subsystemId, revisionId, externalId;
		const auto status = ApiTunnel::GetPciIdentifiers(m_physicalGpuHandle, &internalId, &subsystemId, &revisionId, &externalId);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to determine PCI identifiers.", status);

		switch (idType)
		{
		case PciIdentifierType::INTERNAL: return internalId;
		case PciIdentifierType::EXTERNAL: return externalId;
		case PciIdentifierType::REVISION: return revisionId;
		case PciIdentifierType::SUBSYSTEM: return subsystemId;
		default: throw std::invalid_argument("Unknown PCI identifier type provided.");
		}
	}

	unsigned long PhysicalGpu::GetPciInternalId()
	{
		return GetPciIdentifier(PciIdentifierType::INTERNAL);
	}

	unsigned long PhysicalGpu::GetPciExternalId()
	{
		return GetPciIdentifier(PciIdentifierType::EXTERNAL);
	}

	unsigned long PhysicalGpu::GetPciRevisionId()
	{
		return GetPciIdentifier(PciIdentifierType::REVISION);
	}

	unsigned long PhysicalGpu::GetPciSubsystemId()
	{
		return GetPciIdentifier(PciIdentifierType::SUBSYSTEM);
	}

	unsigned long PhysicalGpu::GetPhysicalFrameBufferSize()
	{
		unsigned long bufferSize = 0ul;
		const auto status = ApiTunnel::GetPhysicalFrameBufferSize(m_physicalGpuHandle, &bufferSize);
		if (status == NvAPI_Status::NVAPI_OK) return bufferSize;
		throw ApiError("Failed to determine GPU physical frame buffer size.", status);
	}

	unsigned long PhysicalGpu::GetVirtualFrameBufferSize()
	{
		unsigned long bufferSize = 0ul;
		const auto status = ApiTunnel::GetVirtualFrameBufferSize(m_physicalGpuHandle, &bufferSize);
		if (status == NvAPI_Status::NVAPI_OK) return bufferSize;
		throw ApiError("Failed to determine GPU virtual frame buffer size.", status);
	}
}