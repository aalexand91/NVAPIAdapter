// Copyright 2024 Anthony Alexander

#pragma once

#include <PhysicalGpuAdapter.h>

namespace NVAPIAdapter
{
	/// <summary>Interfaces with the physical GPU.</summary>
	public interface class INvidiaGpu
	{
		/// <summary>Number of cores defined for the GPU.</summary>
		property System::UInt32 CoreCount 
		{
			System::UInt32 get();
		}

		/// <summary>Full name of the GPU. For example: "Quadro FX 1400".</summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};

	ref class NvidiaGpu : INvidiaGpu
	{
	public:
		/// <returns>Instance unit tests can fake.</returns>
		static INvidiaGpu^ CreateInstance(IPhysicalGpuAdapter^ physicalGpuAdapter);

		virtual property System::UInt32 CoreCount { System::UInt32 get(); }
		virtual property System::String^ Name { System::String^ get(); }

	private:
		IPhysicalGpuAdapter^ m_physicalGpu;

		NvidiaGpu(IPhysicalGpuAdapter^ physicalGpuAdapter) : m_physicalGpu(physicalGpuAdapter) {}
	};
}