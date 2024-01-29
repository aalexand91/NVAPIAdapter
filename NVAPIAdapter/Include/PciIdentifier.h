#pragma once

namespace NVAPIAdapter
{
	/// <summary>The PCI identifiers of the associated GPU.</summary>
	public ref struct PciIdentifier
	{
	public:
		/// <summary>The internal PCI device indentifier.</summary>
		unsigned int DeviceId;

		/// <summary>The internal PCI subsystem identifier.</summary>
		unsigned int SubsystemId;

		/// <summary>The PCI device-specific revision identifier.</summary>
		unsigned int RevisionId;

		/// <summary>The external PCI device identifier.</summary>
		unsigned int ExternalDeviceId;

		virtual System::String^ ToString() override;
	};
}