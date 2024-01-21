#include "pch.h"

#include "NvidiaGpu.h"

using namespace System;

namespace NVAPIAdapter
{
	String^ NvidiaGpu::GetName() { return m_physicalGpu->GetName(); }
}