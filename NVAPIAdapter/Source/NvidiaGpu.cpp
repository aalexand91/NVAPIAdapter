#include "pch.h"

#include <NvidiaGpu.h>

using namespace System;

namespace NVAPIAdapter
{
	String^ NvidiaGpu::GetName() 
	{ 
		return m_physicalGpu->GetName(); 
	}

	GpuSystemType NvidiaGpu::GetSystemType()
	{
		GpuSystemType systemType;
		if (Enum::TryParse(m_physicalGpu->GetSystemType(), systemType)) return systemType;
		return GpuSystemType::Unknown;
	}

	GpuType NvidiaGpu::GetGpuType()
	{
		GpuType gpuType;
		if (Enum::TryParse(m_physicalGpu->GetGpuType(), gpuType)) return gpuType;
		return GpuType::Unknown;
	}

	PciIdentifier^ NvidiaGpu::GetPciIdentifiers() 
	{ 
		return m_physicalGpu->GetPciIdentifiers(); 
	}

	unsigned long NvidiaGpu::GetBusId() 
	{ 
		return m_physicalGpu->GetBusId(); 
	}

	String^ NvidiaGpu::GetVideoBiosVersion()
	{
		return m_physicalGpu->GetVideoBiosVersion();
	}

	unsigned long NvidiaGpu::GetPhysicalFrameBufferSizeInKb()
	{
		return m_physicalGpu->GetPhysicalFrameBufferSizeInKb();
	}

	unsigned long NvidiaGpu::GetVirtualFrameBufferSizeInKb()
	{
		return m_physicalGpu->GetVirtualFrameBufferSizeInKb();
	}
}