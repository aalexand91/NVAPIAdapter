// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <Export.h>
#include <IPhysicalGpu.h>
#include <nvapi.h>
#include <PciIdentifierTypes.h>
#include <unordered_map>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		class PhysicalGpuTester;
	}

	class PhysicalGpu : public IPhysicalGpu
	{
		friend class UnitTest::PhysicalGpuTester;

	public:
		/// <summary>Interfaces with the specific GPU with the given physical GPU handle.</summary>
		PhysicalGpu(NvPhysicalGpuHandle physicalGpuHandle) : m_physicalGpuHandle(physicalGpuHandle) {}

		/// <summary>Resets the physical GPU handle so that it cannot be used after destruction.</summary>
		virtual ~PhysicalGpu() { m_physicalGpuHandle = NVAPI_DEFAULT_HANDLE; }

		HOOKS_API unsigned long GetCoreCount() override;
		HOOKS_API std::string GetFullName() override;
		HOOKS_API std::string GetBusType() override;
		HOOKS_API std::string GetSystemType() override;
		HOOKS_API unsigned long GetPciInternalId() override;
		HOOKS_API unsigned long GetPciExternalId() override;
		HOOKS_API unsigned long GetPciRevisionId() override;
		HOOKS_API unsigned long GetPciSubsystemId() override;

	private:
		NvPhysicalGpuHandle m_physicalGpuHandle{ NVAPI_DEFAULT_HANDLE };

		const std::unordered_map<NV_GPU_BUS_TYPE, std::string> m_busTypeMap =
		{
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_PCI, "PCI"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_AGP, "AGP"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_PCI_EXPRESS, "PCIe"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_FPCI, "FPCI"},
			{NV_GPU_BUS_TYPE::NVAPI_GPU_BUS_TYPE_AXI, "AXI"},
		};

		[[nodiscard]] HOOKS_API unsigned long GetPciIdentifier(const PciIdentifierType idType);
	};
}
