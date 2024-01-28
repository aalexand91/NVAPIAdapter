#pragma once

#include "GpuSystemType.h"
#include "PhysicalGpuAdapter.h"

namespace NVAPIAdapter
{
	/// <summary>Interfaces with the Nvidia GPU.</summary>
	public interface class INvidiaGpu 
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();

		/// <returns>The type of system the GPU is installed in.</returns>
		GpuSystemType GetSystemType();
	};

	public ref class NvidiaGpu sealed : INvidiaGpu
	{
	public:
		static INvidiaGpu^ CreateInstance(IPhysicalGpuAdapter^ physicalGpu) { return gcnew NvidiaGpu(physicalGpu); }

		virtual System::String^ GetName();
		virtual GpuSystemType GetSystemType();

	internal:
		NvidiaGpu(IPhysicalGpuAdapter^ physicalGpu) : m_physicalGpu(physicalGpu) {}

	private:
		IPhysicalGpuAdapter^ m_physicalGpu;
	};
}