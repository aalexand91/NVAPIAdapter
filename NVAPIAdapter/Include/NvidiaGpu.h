#pragma once

#include "PhysicalGpuAdapter.h"

namespace NVAPIAdapter
{
	public interface class INvidiaGpu 
	{
	public:
		System::String^ GetName();
	};

	public ref class NvidiaGpu sealed : INvidiaGpu
	{
	public:
		NvidiaGpu(IPhysicalGpu^ physicalGpu) : m_physicalGpu(physicalGpu) {}

		virtual System::String^ GetName();

	private:
		IPhysicalGpu^ m_physicalGpu;
	};
}