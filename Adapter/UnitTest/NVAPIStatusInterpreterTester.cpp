#include "pch.h"

#include "CppUnitTest.h"
#include "hippomocks.h"
#include <NVAPIStatusInterpreter.h>
#include <NVAPITunnel.h>

using namespace Adapter;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdapterUnitTest
{
	TEST_CLASS(NVAPIStatusInterpreterTester)
	{
	public:
		TEST_METHOD(GetStatusMessage_GivenInterpretationSucceeded_ReturnsIt)
		{
			// Arrange
			const NvAPI_Status status = NvAPI_Status::NVAPI_API_NOT_INITIALIZED;
			const std::string expected = "Fake API not initialized message.";
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::GetStatusErrorMessage).With(status, _)
				.Do([&](NvAPI_Status, char* message) -> NvAPI_Status
					{
						strcpy_s(message, 256, expected.c_str());
						return NvAPI_Status::NVAPI_OK;
					});

			// Act
			const std::string actual = NVAPIStatusInterpreter::GetStatusMessage(status);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetStatusMessage_GivenInterpretationFailed_ReturnsFailedMessage)
		{
			// Arrange
			const NvAPI_Status status = NvAPI_Status::NVAPI_API_NOT_INITIALIZED;
			const std::string expected = "Failed to get API status message for status code " + std::to_string(static_cast<int>(status)) + ".";
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::GetStatusErrorMessage).Return(status);

			// Act
			const std::string actual = NVAPIStatusInterpreter::GetStatusMessage(status);

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
