#pragma once

#include <PhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Test adapter for the native PhysicalGpu class that can be mocked by unit tests.</summary>
	public interface class IPhysicalGpu
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();
	};

	/// <summary>
	/// .NET adapter for the PhysicalGpu.
	/// </summary>
	public ref class RealPhysicalGpu : IPhysicalGpu
	{
	public:
		RealPhysicalGpu(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) {}
		~RealPhysicalGpu();

		virtual System::String^ GetName();

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu{ nullptr };
	};
}