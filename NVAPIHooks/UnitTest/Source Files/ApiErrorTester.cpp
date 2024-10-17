// Copyright 2024 Anthony Alexander

#include <pch_UnitTest.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <CppUnitTest.h>
#include <hippomocks.h>
#include <nvapi.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(ApiErrorTester)
		{
		public:
			TEST_METHOD(GetErrorMessage_WhenCalled_ReturnsIt)
			{
				// Arrange
				const char* contextMessage = "Fake context message.";
				const NvAPI_Status status = NvAPI_Status::NVAPI_ERROR;
				char apiErrorMessage[16] = "Fake API error.";
				MockRepository mocks;
				mocks.OnCallFunc(ApiTunnel::GetApiErrorMessage)
					.Do([&](const NvAPI_Status, char* message) -> NvAPI_Status
						{
							sprintf_s(message, sizeof(apiErrorMessage), apiErrorMessage);
							return NvAPI_Status::NVAPI_OK;
						});

				const std::string expected = "Fake context message. Fake API error.";
				auto apiError = ApiError(contextMessage, status);

				// Act
				const std::string actual = apiError.GetErrorMessage();

				// Assert
				Assert::AreEqual(expected, actual);
			}
		};
	}
}