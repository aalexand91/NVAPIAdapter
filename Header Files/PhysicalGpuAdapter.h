// Copyright 2024 Anthony Alexander

#pragma once

#include <IPhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Wraps the native physical GPU code into a testable adapter.</summary>
	interface class IPhysicalGpuAdapter
	{
		unsigned long GetCoreCount();
		System::String^ GetFullName();
	};

	ref class PhysicalGpuAdapter : IPhysicalGpuAdapter
	{
	public:
		PhysicalGpuAdapter(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) { }
		virtual unsigned long GetCoreCount() { return m_physicalGpu->GetCoreCount(); }
		virtual System::String^ GetFullName() { return gcnew System::String(m_physicalGpu->GetFullName().c_str()); }

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu = nullptr;
	};
}
