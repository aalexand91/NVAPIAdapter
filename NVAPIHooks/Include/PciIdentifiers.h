#pragma once

namespace NVAPIHooks
{
	struct PciIdentifiers 
	{
		unsigned long m_deviceId{ 0ul };
		unsigned long m_subSystemId{ 0ul };
		unsigned long m_revisionId{ 0ul };
		unsigned long m_externalDeviceId{ 0ul };
	};
}
