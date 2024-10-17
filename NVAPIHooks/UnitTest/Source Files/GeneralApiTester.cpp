// Copyright 2024 Anthony Alexander

#include <pch_UnitTest.h>

#include <ApiTunnel.h>
#include <ApiError.h>
#include <CppUnitTest.h>
#include <GeneralApi.h>
#include <hippomocks.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(GeneralApiTester)
		{
		public:
			TEST_METHOD_CLEANUP(Teardown)
			{
				m_mocks.reset();
			}

			TEST_METHOD(Initialize_OnSuccess_Returns)
			{
				// Arrange
				m_mocks.ExpectCallFunc(ApiTunnel::InitializeApi).Return(NvAPI_Status::NVAPI_OK);

				// Act
				GeneralApi::Initialize();

				// Assert
				m_mocks.VerifyAll();
			}

			TEST_METHOD(Initialize_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::InitializeApi).Return(NvAPI_Status::NVAPI_ERROR);

				// Act
				auto act = []() -> void { GeneralApi::Initialize(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			MockRepository m_mocks;
		};
	}
}
