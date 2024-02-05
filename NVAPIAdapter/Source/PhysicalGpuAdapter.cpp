#include "pch.h"

#include <PhysicalGpuAdapter.h>

using namespace System;

namespace NVAPIAdapter
{
	RealPhysicalGpu::~RealPhysicalGpu()
	{
		if (!m_physicalGpu) return;
		delete m_physicalGpu;
		m_physicalGpu = nullptr;
	}

	String^ RealPhysicalGpu::GetName() 
	{ 
		return gcnew String(m_physicalGpu->GetName().c_str()); 
	}

	String^ RealPhysicalGpu::GetSystemType() 
	{ 
		return gcnew String(m_physicalGpu->GetSystemType().c_str()); 
	}

	String^ RealPhysicalGpu::GetGpuType() 
	{
		return gcnew String(m_physicalGpu->GetGpuType().c_str());
	}

	PciIdentifier^ RealPhysicalGpu::GetPciIdentifiers()
	{
		auto ids = m_physicalGpu->GetPciIdentifiers();
		auto identifier = gcnew PciIdentifier();
		identifier->DeviceId = ids.m_deviceId;
		identifier->SubsystemId = ids.m_subSystemId;
		identifier->RevisionId = ids.m_revisionId;
		identifier->ExternalDeviceId = ids.m_externalDeviceId;
		return identifier;
	}

	unsigned long RealPhysicalGpu::GetBusId() 
	{
		return m_physicalGpu->GetGpuBusId();
	}

	String^ RealPhysicalGpu::GetVideoBiosVersion()
{
		return gcnew String(m_physicalGpu->GetVbiosVersion().c_str());
	}

	unsigned long RealPhysicalGpu::GetPhysicalFrameBufferSizeInKb()
	{
		return m_physicalGpu->GetPhysicalFrameBufferSize();
	}

	unsigned long RealPhysicalGpu::GetVirtualFrameBufferSizeInKb()
	{
		return m_physicalGpu->GetVirtualFrameBufferSize();
	}
}