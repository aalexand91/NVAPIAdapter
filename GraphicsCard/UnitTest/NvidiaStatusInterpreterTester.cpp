#include "pch.h"
#include "CppUnitTest.h"
#include <NvidiaStatusInterpreter.h>

using namespace GraphicsCards;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphicsCardUnitTest
{
	TEST_CLASS(NvidiaStatusInterpreterTester)
	{
	public:
		TEST_METHOD(GetStatusMessage_GivenLibraryNotFoundStatus_ReturnsExpectedMessage)
		{
			// Arrange
			const std::string expected = "Support library for Nvidia graphics card failed to load.";

			// Act
			const std::string actual = NvidiaStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_LIBRARY_NOT_FOUND);

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
