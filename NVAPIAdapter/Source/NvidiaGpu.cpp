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
}