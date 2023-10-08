#pragma once

#include <IGraphicsCard.h>
#include <vector>

namespace GraphicsCards
{
	/// <summary>
	/// Finds any physical graphics card installed in the system.
	/// </summary>
	class IGraphicsCardFinder
	{
	public:
		IGraphicsCardFinder() = default;
		virtual ~IGraphicsCardFinder() = default;

		// Delete copy constructors to prevent unwanted memory allocation and passing by value.

		IGraphicsCardFinder(const IGraphicsCardFinder&) = delete;
		IGraphicsCardFinder(IGraphicsCardFinder&&) = delete;
		IGraphicsCardFinder& operator = (const IGraphicsCardFinder&) = delete;
		IGraphicsCardFinder& operator = (IGraphicsCardFinder&&) = delete;

		/// <returns>All graphics cards installed in the system.</returns>
		virtual std::vector<IGraphicsCard*> GetAllGraphicsCards() = 0;
	};
}