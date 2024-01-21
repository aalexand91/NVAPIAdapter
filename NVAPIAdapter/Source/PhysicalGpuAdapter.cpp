#include "pch.h"

#include "PhysicalGpuAdapter.h"

using namespace System;

namespace NVAPIAdapter
{
	RealPhysicalGpu::~RealPhysicalGpu()
	{
		if (!m_physicalGpu) return;
		delete m_physicalGpu;
		m_physicalGpu = nullptr;
	}

	String^ RealPhysicalGpu::GetName() { return gcnew String(m_physicalGpu->GetName().c_str()); }
}