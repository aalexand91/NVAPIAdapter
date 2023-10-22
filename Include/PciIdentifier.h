#pragma once

namespace Adapter
{
	/// <summary>Provides PCI identifiers associated with GPU.</summary>
	struct PciIdentifier
	{
		unsigned long m_internalId{ 0ul };
		unsigned long m_subsystemId{ 0ul };
		unsigned long m_revisionId{ 0ul };
		unsigned long m_externalId{ 0ul };

		PciIdentifier() = default;
	};
}