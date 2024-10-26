// Copyright 2024 Anthony Alexander

#pragma once

#include <string>

namespace NVAPIHooks
{
	class IPhysicalGpu
	{
	public:
		IPhysicalGpu() = default;
		~IPhysicalGpu() = default;
		IPhysicalGpu(IPhysicalGpu&) = delete;
		IPhysicalGpu(IPhysicalGpu&&) = delete;
		IPhysicalGpu& operator = (IPhysicalGpu&) = delete;
		IPhysicalGpu& operator = (IPhysicalGpu&&) = delete;

		/// <returns>Number of cores defined for the GPU.</returns>
		virtual unsigned long GetCoreCount() = 0;

		/// <returns>The name of the GPU.</returns>
		virtual std::string GetFullName() = 0;
	};
}
