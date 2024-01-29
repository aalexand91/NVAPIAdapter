#include "pch.h"

#include <NvidiaGpu.h>

using namespace System;

namespace NVAPIAdapter
{
	String^ NvidiaGpu::GetName() { return m_physicalGpu->GetName(); }

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

	PciIdentifier^ NvidiaGpu::GetPciIdentifiers() { return m_physicalGpu->GetPciIdentifiers(); }
}