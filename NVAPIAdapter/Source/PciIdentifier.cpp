#include "pch.h"

#include <PciIdentifier.h>

using namespace System;

namespace NVAPIAdapter
{
	String^ PciIdentifier::ToString()
	{
		return "Device ID: " + DeviceId.ToString()
			+ " Subsystem ID: " + SubsystemId.ToString()
			+ " Revision ID: " + RevisionId.ToString()
			+ " External ID: " + ExternalDeviceId.ToString();
	}
}