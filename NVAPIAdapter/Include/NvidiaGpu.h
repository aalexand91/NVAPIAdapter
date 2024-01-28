#pragma once

#include "PhysicalGpuAdapter.h"

namespace NVAPIAdapter
{
	/// <summary>Interfaces with the Nvidia GPU.</summary>
	public interface class INvidiaGpu 
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();
	};

	public ref class NvidiaGpu sealed : INvidiaGpu
	{
	public:
		static INvidiaGpu^ CreateInstance(IPhysicalGpuAdapter^ physicalGpu) { return gcnew NvidiaGpu(physicalGpu); }

		virtual System::String^ GetName();

	internal:
		NvidiaGpu(IPhysicalGpuAdapter^ physicalGpu) : m_physicalGpu(physicalGpu) {}

	private:
		IPhysicalGpuAdapter^ m_physicalGpu;
	};
}