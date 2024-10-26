// Copyright 2024 Anthony Alexander

#include <NvidiaGpu.h>

using namespace System;

namespace NVAPIAdapter
{
	INvidiaGpu^ NvidiaGpu::CreateInstance(IPhysicalGpuAdapter^ physicalGpuAdapter)
	{
		return gcnew NvidiaGpu(physicalGpuAdapter);
	}

	UInt32 NvidiaGpu::CoreCount::get()
	{
		return m_physicalGpu->GetCoreCount();
	}

	String^ NvidiaGpu::Name::get() 
	{
		return m_physicalGpu->GetFullName();
	}
}