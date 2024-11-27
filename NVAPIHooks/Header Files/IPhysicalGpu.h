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

#include <string>

namespace NVAPIHooks
{
	class IPhysicalGpu
	{
	public:
		IPhysicalGpu() = default;
		~IPhysicalGpu() = default;
		IPhysicalGpu(const IPhysicalGpu&) = delete;
		IPhysicalGpu(IPhysicalGpu&&) = delete;
		IPhysicalGpu& operator = (const IPhysicalGpu&) = delete;
		IPhysicalGpu& operator = (IPhysicalGpu&&) = delete;

		/// <returns>Number of cores defined for the GPU.</returns>
		virtual unsigned long GetCoreCount() = 0;

		/// <returns>The name of the GPU.</returns>
		virtual std::string GetFullName() = 0;

		/// <returns>The GPU bus type such as PCIe.</returns>
		virtual std::string GetBusType() = 0;

		/// <returns>The GPU system type such as Laptop or Desktop.</returns>
		virtual std::string GetSystemType() = 0;

		/// <returns>The PCI internal identifier value.</returns>
		virtual unsigned long GetPciInternalId() = 0;

		/// <returns>The PCI external identifier value.</returns>
		virtual unsigned long GetPciExternalId() = 0;

		/// <returns>The PCI revision identifier value.</returns>
		virtual unsigned long GetPciRevisionId() = 0;

		/// <returns>The PCI subsystem identifier value.</returns>
		virtual unsigned long GetPciSubsystemId() = 0;

		/// <returns>The physical frame buffer size in KB. Excludes any dedicated RAM.</returns>
		virtual unsigned long GetPhysicalFrameBufferSize() = 0;

		/// <returns>The virtual frame buffer size in KB. Includes both physical and any dedicated RAM.</returns>
		virtual unsigned long GetVirtualFrameBufferSize() = 0;

		/// <returns>
		/// The video BIOS string in the form of xx.xx.xx.xx.yy where the xx numbers are 
		/// the video BIOS version and the yy numbers are the manufacturer's version.
		/// </returns>
		virtual std::string GetVbiosVersion() = 0;

		/// <returns>Size of the GPU memory bus width.</returns>
		virtual unsigned long GetRamBusWidth() = 0;

		/// <returns>The current GPU performance state.</returns>
		virtual std::string GetPerformanceState() = 0;

		/// <returns>The current GPU core temperature in Celsius.</returns>
		virtual int GetGpuCoreTempInCelsius() = 0;
	};
}
