#pragma once

namespace GraphicsCards 
{
	class IGraphicsCard
	{
	public:
		IGraphicsCard() = default;
		virtual ~IGraphicsCard() = default;

		// Delete copy constructors to prevent unwanted memory allocation and passing by value.

		IGraphicsCard(const IGraphicsCard&) = delete;
		IGraphicsCard(IGraphicsCard&&) = delete;
		IGraphicsCard& operator = (const IGraphicsCard&) = delete;
		IGraphicsCard& operator = (IGraphicsCard&&) = delete;

		/// <returns>The full name of the GPU as a string of ASCII characters.</returns>
		virtual char* GetFullName() = 0;
	};
}