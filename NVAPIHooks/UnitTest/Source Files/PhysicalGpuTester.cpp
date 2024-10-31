// Copyright 2024 Anthony Alexander

#include <pch_UnitTest.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <PhysicalGpu.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(PhysicalGpuTester)
		{
		public:
			TEST_METHOD_CLEANUP(CleanUpTest)
			{
				m_mocks.reset();
			}

			TEST_METHOD(GetCoreCount_WhenCalled_ReturnsIt)
			{
				// Arrange
				const auto expected = 12ul;
				m_mocks.OnCallFunc(ApiTunnel::GetGpuCoreCount)
					.With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long* coreCount) -> NvAPI_Status
						{
							*coreCount = expected;
							return NvAPI_Status::NVAPI_OK;
						});

				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				const auto actual = physicalGpu->GetCoreCount();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetCoreCount_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuCoreCount).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetCoreCount(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetFullName_OnSuccess_ReturnsName)
			{
				// Arrange
				const std::string expected = "FakeGpu";
				m_mocks.OnCallFunc(ApiTunnel::GetFullName)
					.With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, char* name) -> NvAPI_Status
						{
							sprintf_s(name, sizeof(expected), expected.c_str());
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetFullName();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetFullName_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetFullName).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> std::string { return physicalGpu->GetFullName(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			NvPhysicalGpuHandle m_fakeGpuHandle{ (NvPhysicalGpuHandle)1 };
			MockRepository m_mocks;
		};
	}
}