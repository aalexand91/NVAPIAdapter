#pragma once

#include <PhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Test adapter for the native PhysicalGpu class that can be mocked by unit tests.</summary>
	interface class IPhysicalGpuAdapter
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();
	};

	/// <summary>.NET adapter for the native PhysicalGpu class.</summary>
	ref class RealPhysicalGpu : IPhysicalGpuAdapter
	{
	public:
		static IPhysicalGpuAdapter^ CreateInstance(NVAPIHooks::IPhysicalGpu* physicalGpu) { return gcnew RealPhysicalGpu(physicalGpu); }
		RealPhysicalGpu(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) {}
		~RealPhysicalGpu();

		virtual System::String^ GetName();

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu{ nullptr };
	};
}