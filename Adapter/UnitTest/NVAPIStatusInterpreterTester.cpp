#include "pch.h"
#include "CppUnitTest.h"
#include <NVAPIStatusInterpreter.h>

using namespace Adapter;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdapterUnitTest
{
	TEST_CLASS(NVAPIStatusInterpreterTester)
	{
	public:
		TEST_METHOD(GetStatusMessage_GivenLibraryNotFoundStatus_ReturnsExpectedMessage)
		{
			// Arrange
			const char* expected = "Support library for Nvidia graphics card failed to load.";

			// Act
			const char* actual = NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_LIBRARY_NOT_FOUND);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetStatusMessage_GivenApiNotInitialized_ReturnsExpectedMessage) 
		{
			// Arrange
			const char* expected = "API needs to be initialized before being used.";

			// Act
			const char* actual = NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_API_NOT_INITIALIZED);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetStatusMessage_GivenInvalidArgument_ReturnsExpectedMessage)
		{
			// Arrange
			const char* expected = "Argument provided to API is invalid.";

			// Act
			const char* actual = NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_INVALID_ARGUMENT);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetStatusMessage_GivenDeviceNotFound_ReturnsExpectedMessage)
		{
			// Arrange
			const char* expected = "Nvidia GPU not found. Verify compatible device connection.";

			// Act
			const char* actual = NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_NVIDIA_DEVICE_NOT_FOUND);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetStatusMessage_GivenUnknownStatus_ReturnsGenericMessage)
		{
			// Arrange
			const char* expected = "An error occurred with the Nvidia API. See stack trace for more info.";

			// Act
			const char* actual = NVAPIStatusInterpreter::GetStatusMessage(NvAPI_Status::NVAPI_END_ENUMERATION);

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
