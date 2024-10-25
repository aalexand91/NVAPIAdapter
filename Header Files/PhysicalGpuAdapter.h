// Copyright 2024 Anthony Alexander

#pragma once

#include <IPhysicalGpu.h>
#include <memory>

namespace NVAPIAdapter
{
	/// <summary>Wraps the native physical GPU code into a testable adapter.</summary>
	interface class IPhysicalGpuAdapter
	{
		unsigned long GetCoreCount();
	};

	ref class PhysicalGpuAdapter : IPhysicalGpuAdapter
	{
	public:
		PhysicalGpuAdapter(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) { }
		virtual unsigned long GetCoreCount() { return m_physicalGpu->GetCoreCount(); }

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu = nullptr;
	};
}
