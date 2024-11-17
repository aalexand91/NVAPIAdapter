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

#include <NvidiaGpu.h>

using namespace System;

namespace NVAPIAdapter
{
	INvidiaGpu^ NvidiaGpu::CreateInstance(IPhysicalGpuAdapter^ physicalGpuAdapter)
	{
		return gcnew NvidiaGpu(physicalGpuAdapter);
	}

	UInt32 NvidiaGpu::CoreCount::get()
	{
		return m_physicalGpu->GetCoreCount();
	}

	String^ NvidiaGpu::Name::get() 
	{
		return m_physicalGpu->GetFullName();
	}

	String^ NvidiaGpu::BusType::get()
	{
		return m_physicalGpu->GetBusType();
	}

	String^ NvidiaGpu::SystemType::get()
	{
		return m_physicalGpu->GetSystemType();
	}

	IPciIdentifier^ NvidiaGpu::GetPciIdentifier()
	{
		const auto internalId = m_physicalGpu->GetPciInternalId();
		const auto externalId = m_physicalGpu->GetPciExternalId();
		const auto revisionId = m_physicalGpu->GetPciRevisionId();
		const auto subsystemId = m_physicalGpu->GetPciSubsystemId();
		return gcnew PciIdentifier(internalId, externalId, revisionId, subsystemId);
	}

	UInt32 NvidiaGpu::PhysicalFrameBufferSizeInKb::get()
	{
		return m_physicalGpu->GetPhysicalFrameBufferSizeInKb();
	}

	UInt32 NvidiaGpu::VirtualFrameBufferSizeInKb::get()
	{
		return m_physicalGpu->GetVirtualFrameBufferSizeInKb();
	}
}