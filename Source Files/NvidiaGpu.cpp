// Copyright 2024 Anthony Alexander

#include <NvidiaGpu.h>

namespace NVAPIAdapter
{
	INvidiaGpu^ NvidiaGpu::CreateInstance(IPhysicalGpuAdapter^ physicalGpuAdapter)
	{
		return gcnew NvidiaGpu(physicalGpuAdapter);
	}

	System::UInt32 NvidiaGpu::CoreCount::get()
	{
		return m_physicalGpu->GetCoreCount();
	}
}