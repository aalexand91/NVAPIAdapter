#pragma once

#include "Export.h"

namespace GraphicsCardsUnitTest 
{
	class NvidiaGraphicsCardTester;
}

namespace GraphicsCards
{
	class NvidiaGraphicsCard
	{
		friend class GraphicsCardsUnitTest::NvidiaGraphicsCardTester;

	public:
		NvidiaGraphicsCard(NvPhysicalGpuHandle physicalHander) : m_physicalHandler(physicalHander) {}
		~NvidiaGraphicsCard() = default;

		NvidiaGraphicsCard(const NvidiaGraphicsCard&) = delete;
		NvidiaGraphicsCard(NvidiaGraphicsCard&&) = delete;
		NvidiaGraphicsCard& operator = (const NvidiaGraphicsCard&) = delete;
		NvidiaGraphicsCard& operator = (NvidiaGraphicsCard&&) = delete;

		/// <summary>Initializes the Nvidia graphics card API library.</summary>
		GRAPHICS_CARD_API void Initialize();

		/// <returns>The full name of the graphics card.</returns>
		/// <example>Quadro FX 1400.</example>
		GRAPHICS_CARD_API std::string GetName();

		/// <returns>The type of GPU installed (integrated, discrete, or unknown).</returns>
		GRAPHICS_CARD_API std::string GetGpuType();

	private:

		/// <summary>
		/// The distinct GPU handler from the NVAPI library that handles interfacing with the specific graphics card.
		/// </summary>
		NvPhysicalGpuHandle m_physicalHandler;

		bool m_apiInitialized{ false };

		void AssertApiInitialized();
	};
}
