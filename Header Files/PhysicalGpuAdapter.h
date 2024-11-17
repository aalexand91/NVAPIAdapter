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

#include <IPhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Wraps the native physical GPU code into a testable adapter.</summary>
	interface class IPhysicalGpuAdapter
	{
		unsigned long GetCoreCount();
		System::String^ GetFullName();
		System::String^ GetBusType();
		System::String^ GetSystemType();
		unsigned long GetPciInternalId();
		unsigned long GetPciExternalId();
		unsigned long GetPciRevisionId();
		unsigned long GetPciSubsystemId();
		unsigned long GetPhysicalFrameBufferSizeInKb();
		unsigned long GetVirtualFrameBufferSizeInKb();
	};

	ref class PhysicalGpuAdapter : IPhysicalGpuAdapter
	{
	public:
		PhysicalGpuAdapter(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) { }
		~PhysicalGpuAdapter() { delete m_physicalGpu; m_physicalGpu = nullptr; }
		virtual unsigned long GetCoreCount() { return m_physicalGpu->GetCoreCount(); }
		virtual System::String^ GetFullName() { return gcnew System::String(m_physicalGpu->GetFullName().c_str()); }
		virtual System::String^ GetBusType() { return gcnew System::String(m_physicalGpu->GetBusType().c_str()); }
		virtual System::String^ GetSystemType() { return gcnew System::String(m_physicalGpu->GetSystemType().c_str()); }
		virtual unsigned long GetPciInternalId() { return m_physicalGpu->GetPciInternalId(); }
		virtual unsigned long GetPciExternalId() { return m_physicalGpu->GetPciExternalId(); }
		virtual unsigned long GetPciRevisionId() { return m_physicalGpu->GetPciRevisionId(); }
		virtual unsigned long GetPciSubsystemId() { return m_physicalGpu->GetPciSubsystemId(); }
		virtual unsigned long GetPhysicalFrameBufferSizeInKb() { return m_physicalGpu->GetPhysicalFrameBufferSize(); }
		virtual unsigned long GetVirtualFrameBufferSizeInKb() { return m_physicalGpu->GetVirtualFrameBufferSize(); }

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu = nullptr;
	};
}
