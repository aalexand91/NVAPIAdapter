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

#include <PciIdentifier.h>
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

		/// <summary>The GPU busy type, such as PCIe.</summary>
		property System::String^ BusType
		{
			System::String^ get();
		}

		/// <summary>The GPU system type, such as Desktop or Laptop.</summary>
		property System::String^ SystemType
		{
			System::String^ get();
		}

		/// <returns>The GPU PCI internal, external, revision, and subsystem IDs via the IPciIdentifier object.</returns>
		IPciIdentifier^ GetPciIdentifier();
	};

	ref class NvidiaGpu : INvidiaGpu
	{
	public:
		/// <returns>Instance unit tests can fake.</returns>
		static INvidiaGpu^ CreateInstance(IPhysicalGpuAdapter^ physicalGpuAdapter);

		virtual property System::UInt32 CoreCount { System::UInt32 get(); }
		virtual property System::String^ Name { System::String^ get(); }
		virtual property System::String^ SystemType { System::String^ get(); }
		virtual property System::String^ BusType { System::String^ get(); }
		virtual IPciIdentifier^ GetPciIdentifier();

	private:
		IPhysicalGpuAdapter^ m_physicalGpu;

		NvidiaGpu(IPhysicalGpuAdapter^ physicalGpuAdapter) : m_physicalGpu(physicalGpuAdapter) {}
	};
}