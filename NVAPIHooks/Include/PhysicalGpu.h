#pragma once

#include "ApiExport.h"
#include <memory>
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		// Forward declarated so that unit tests can access private members.
		class PhysicalGpuTester;
	}

	/// <summary>Provides an API to a physical GPU installed on the system.</summary>
	class IPhysicalGpu
	{
		friend UnitTest::PhysicalGpuTester;

	public:
		IPhysicalGpu() = default;
		virtual ~IPhysicalGpu() = default;
		IPhysicalGpu(const IPhysicalGpu&) = delete;
		IPhysicalGpu(IPhysicalGpu&&) = delete;
		IPhysicalGpu& operator = (const IPhysicalGpu&) = delete;
		IPhysicalGpu& operator = (IPhysicalGpu&&) = delete;

		/// <returns>The full name of the GPU.</returns>
		virtual std::string GetName() = 0;
	};

	class PhysicalGpu : public IPhysicalGpu
	{
	public:
		PhysicalGpu(NvPhysicalGpuHandle physicalGpuHandle) : m_physicalGpuHandle(physicalGpuHandle) {}
		virtual ~PhysicalGpu() = default;
		PhysicalGpu(const PhysicalGpu&) = delete;
		PhysicalGpu(PhysicalGpu&&) = delete;
		PhysicalGpu& operator = (const PhysicalGpu&) = delete;
		PhysicalGpu& operator = (PhysicalGpu&&) = delete;

		HOOKS_API std::string GetName() override;

	private:
		static const unsigned ms_asciiStringBufferSize{ 256u };

		NvPhysicalGpuHandle m_physicalGpuHandle{ nullptr };
	};
}
